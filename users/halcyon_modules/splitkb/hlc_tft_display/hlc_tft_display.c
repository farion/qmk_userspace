// Copyright 2024 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "halcyon.h"
#include "hlc_tft_display.h"
#include "wpm.h"

#include "hardware/structs/rosc.h"

// Fonts mono2
#include "graphics/fonts/Retron2000-27.qff.h"
#include "graphics/fonts/Retron2000-underline-27.qff.h"

// Numbers mono2
#include "graphics/numbers/0.qgf.h"
#include "graphics/numbers/1.qgf.h"
#include "graphics/numbers/2.qgf.h"
#include "graphics/numbers/3.qgf.h"
#include "graphics/numbers/4.qgf.h"
#include "graphics/numbers/5.qgf.h"
#include "graphics/numbers/6.qgf.h"
#include "graphics/numbers/7.qgf.h"
#include "graphics/numbers/8.qgf.h"
#include "graphics/numbers/9.qgf.h"
#include "graphics/numbers/undef.qgf.h"

static painter_font_handle_t Retron27;
static painter_font_handle_t Retron27_underline;

static uint8_t lcd_surface_fb[SURFACE_REQUIRED_BUFFER_BYTE_SIZE(135, 240, 16)];

int color_value = 0;

painter_device_t lcd;
painter_device_t lcd_surface;

led_t last_led_usb_state = {0};
layer_state_t last_layer_state = {0};

#define GRID_WIDTH 27
#define GRID_HEIGHT 48
#define CELL_SIZE 4  // Cell size excluding outline
#define OUTLINE_SIZE 1

// Define the probability factor for initial alive cells
#define INITIAL_ALIVE_PROBABILITY 0.2  // 20% chance of being alive

bool grid[GRID_HEIGHT][GRID_WIDTH];  // Current state
bool new_grid[GRID_HEIGHT][GRID_WIDTH];  // Next state
bool changed_grid[GRID_HEIGHT][GRID_WIDTH]; // Tracks changed cells

uint32_t get_random_32bit(void) {
    uint32_t random_value = 0;
    for (int i = 0; i < 32; i++) {
        wait_ms(1);
        random_value = (random_value << 1) | (rosc_hw->randombit & 1);
    }
    return random_value;
}

void init_grid() {
    // Initialize grid with alive cells
    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            grid[y][x] = (rand() < INITIAL_ALIVE_PROBABILITY * RAND_MAX);  // Use probability factor
            changed_grid[y][x] = true;      // Mark all as changed initially
        }
    }
}

void draw_grid() {
    uint8_t hue = 0;  // Hue for alive cells
    uint8_t sat = 0;  // Saturation for alive cells
    uint8_t val_dead = 0;  // Brightness for dead cells

    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            if (changed_grid[y][x]) { // Only update changed cells
                uint16_t left = x * (CELL_SIZE + OUTLINE_SIZE);
                uint16_t top = y * (CELL_SIZE + OUTLINE_SIZE);
                uint16_t right = left + CELL_SIZE + OUTLINE_SIZE;
                uint16_t bottom = top + CELL_SIZE + OUTLINE_SIZE;

                // Draw the outline
                qp_rect(lcd_surface, left, top, right, bottom, hue, sat, val_dead, true);

                // Draw the filled cell inside the outline if it's alive
                if (grid[y][x]) {
                    switch (color_value) {
                    case 0:
                        qp_rect(lcd_surface, left + OUTLINE_SIZE, top + OUTLINE_SIZE, right - OUTLINE_SIZE, bottom - OUTLINE_SIZE, HSV_LAYER_0, true);
                        break;
                    case 1:
                        qp_rect(lcd_surface, left + OUTLINE_SIZE, top + OUTLINE_SIZE, right - OUTLINE_SIZE, bottom - OUTLINE_SIZE, HSV_LAYER_1, true);
                        break;
                    case 2:
                        qp_rect(lcd_surface, left + OUTLINE_SIZE, top + OUTLINE_SIZE, right - OUTLINE_SIZE, bottom - OUTLINE_SIZE, HSV_LAYER_2, true);
                        break;
                    case 3:
                        qp_rect(lcd_surface, left + OUTLINE_SIZE, top + OUTLINE_SIZE, right - OUTLINE_SIZE, bottom - OUTLINE_SIZE, HSV_LAYER_3, true);
                        break;
                    case 4:
                        qp_rect(lcd_surface, left + OUTLINE_SIZE, top + OUTLINE_SIZE, right - OUTLINE_SIZE, bottom - OUTLINE_SIZE, HSV_LAYER_4, true);
                        break;
                    case 5:
                        qp_rect(lcd_surface, left + OUTLINE_SIZE, top + OUTLINE_SIZE, right - OUTLINE_SIZE, bottom - OUTLINE_SIZE, HSV_LAYER_5, true);
                        break;
                    case 6:
                        qp_rect(lcd_surface, left + OUTLINE_SIZE, top + OUTLINE_SIZE, right - OUTLINE_SIZE, bottom - OUTLINE_SIZE, HSV_LAYER_6, true);
                        break;
                    case 7:
                        qp_rect(lcd_surface, left + OUTLINE_SIZE, top + OUTLINE_SIZE, right - OUTLINE_SIZE, bottom - OUTLINE_SIZE, HSV_LAYER_7, true);
                        break;
                    case 8:
                        qp_rect(lcd_surface, left + OUTLINE_SIZE, top + OUTLINE_SIZE, right - OUTLINE_SIZE, bottom - OUTLINE_SIZE, HSV_LAYER_8, true);
                        break;
                    case 9:
                        qp_rect(lcd_surface, left + OUTLINE_SIZE, top + OUTLINE_SIZE, right - OUTLINE_SIZE, bottom - OUTLINE_SIZE, HSV_LAYER_9, true);
                        break;
                    default:
                        qp_rect(lcd_surface, left + OUTLINE_SIZE, top + OUTLINE_SIZE, right - OUTLINE_SIZE, bottom - OUTLINE_SIZE, HSV_LAYER_UNDEF, true);
                    }
                }
            }
        }
    }
}

void update_grid() {
    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            int alive_neighbors = 0;

            // Count alive neighbors
            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    if (dy == 0 && dx == 0) continue;  // Skip the current cell
                    int ny = y + dy;
                    int nx = x + dx;
                    if (ny >= 0 && ny < GRID_HEIGHT && nx >= 0 && nx < GRID_WIDTH) {
                        alive_neighbors += grid[ny][nx];
                    }
                }
            }

            // Apply the rules of the Game of Life
            if (grid[y][x]) {
                // Any live cell with two or three live neighbours survives.
                new_grid[y][x] = (alive_neighbors == 2 || alive_neighbors == 3);
            } else {
                // Any dead cell with exactly three live neighbours becomes a live cell.
                new_grid[y][x] = (alive_neighbors == 3);
            }

            // Track changed cells
            changed_grid[y][x] = (grid[y][x] != new_grid[y][x]);
        }
    }

    // Copy new grid state to current grid
    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            grid[y][x] = new_grid[y][x];
        }
    }
}

void draw_layer_text(uint8_t layer) {
    const char *layer_text = "Default";
    uint8_t hue = 0;
    switch (layer) {
        case 0: layer_text = "Default"; hue = 0; break;
        case 1: layer_text = "Win/Mac"; hue = 0; break;
        case 2: layer_text = "Game";    hue = 172; break;
        case 3: layer_text = "Nav";     hue = 43; break;
        case 4: layer_text = "Special"; hue = 32; break;
        case 5: layer_text = "Fn";      hue = 135; break;
        case 6: layer_text = "Symbols"; hue = 135; break;
        case 7: layer_text = "Sway";    hue = 75; break;
        default: layer_text = "Unknown"; hue = 0;
    }
    // Clear the top area for the text
    qp_rect(lcd_surface, 0, 0, LCD_WIDTH - 1, Retron27->line_height + 10, HSV_BLACK, true);
    qp_drawtext_recolor(lcd_surface, 5, 5, Retron27, layer_text, hue, 255, 255, HSV_BLACK);
}

// Function to add a cluster of cells at a random position
void add_cell_cluster() {
    int cluster_size = 3;  // Size of the cluster (3x3)
    int x = rand() % (GRID_WIDTH - cluster_size);
    int y = rand() % (GRID_HEIGHT - cluster_size);

    for (int dy = 0; dy < cluster_size; dy++) {
        for (int dx = 0; dx < cluster_size; dx++) {
            bool is_alive = rand() % 2; // Randomly choose between 0 and 1
            grid[y + dy][x + dx] = is_alive;  // Set the cell to be alive
            changed_grid[y + dy][x + dx] = true; // Mark the cell as changed
        }
    }
}

void update_display(void) {
    static bool first_run_layer = false;

    if( first_run_layer == false) {
        // Load fonts
        Retron27 = qp_load_font_mem(font_Retron2000_27);
        Retron27_underline = qp_load_font_mem(font_Retron2000_underline_27);
    }

    if(last_layer_state != layer_state || first_run_layer == false) {
        draw_layer_text(get_highest_layer(layer_state|default_layer_state));
        last_layer_state = layer_state;
        first_run_layer = true;
    }

    // CAPS WORD
    int ind_y = Retron27->line_height + 10;
    qp_rect(lcd_surface, 0, ind_y, LCD_WIDTH - 1, ind_y + Retron27->line_height, HSV_BLACK, true);
    if(is_caps_word_on()) {
        qp_drawtext_recolor(lcd_surface, 5, ind_y, Retron27, "CAP" , HSV_BLUE, HSV_BLACK);
    }

    // S C A G
    int scag_y = ind_y + Retron27->line_height + 5;
    qp_rect(lcd_surface, 0, scag_y, LCD_WIDTH - 1, scag_y + Retron27->line_height, HSV_BLACK, true);

    uint8_t mods = get_mods();
    struct {
        char c;
        bool active;
    } scag[4] = {
        {'S', mods & MOD_MASK_SHIFT},
        {'C', mods & MOD_MASK_CTRL},
        {'A', mods & MOD_MASK_ALT},
        {'G', mods & MOD_MASK_GUI}
    };

    int x = 5;
    for (int i = 0; i < 4; i++) {
        char str[2] = {scag[i].c, '\0'};
        uint8_t h = scag[i].active ? 170 : 0;
        uint8_t s = scag[i].active ? 255 : 0;
        uint8_t v = scag[i].active ? 255 : 180;
        qp_drawtext_recolor(lcd_surface, x, scag_y, Retron27, str, h, s, v, HSV_BLACK);
        x += 30;
    }

    // WPM
    static uint32_t last_wpm_update = 0;
    static uint8_t cached_wpm = 0;
    int wpm_y = LCD_HEIGHT - Retron27->line_height - 5;
    if (timer_elapsed32(last_wpm_update) >= 1000) {
        cached_wpm = get_current_wpm();
        if (cached_wpm == 1) {
            cached_wpm = 0;
        }
        last_wpm_update = timer_read32();
    }

    qp_rect(lcd_surface, 0, wpm_y, LCD_WIDTH - 1, wpm_y + Retron27->line_height, HSV_BLACK, true);
    char wpm_str[12];
    snprintf(wpm_str, sizeof(wpm_str), "WPM: %3d", cached_wpm);
    qp_drawtext_recolor(lcd_surface, 5, wpm_y, Retron27, wpm_str, HSV_LAYER_0, HSV_BLACK);
}

// Called from halcyon.c
void module_suspend_power_down_kb(void) {
    qp_power(lcd, false);
}

// Called from halcyon.c
void module_suspend_wakeup_init_kb(void) {
    qp_power(lcd, true);
}

// Called from halcyon.c
bool module_post_init_kb(void) {
    // Turn on backlight
    backlight_enable();

    // Make the devices
    lcd = qp_st7789_make_spi_device(LCD_WIDTH, LCD_HEIGHT, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, LCD_SPI_DIVISOR, LCD_SPI_MODE);
    lcd_surface = qp_make_rgb565_surface(LCD_WIDTH, LCD_HEIGHT, lcd_surface_fb);

    // Initialise the LCD
    qp_init(lcd, LCD_ROTATION);
    qp_set_viewport_offsets(lcd, LCD_OFFSET_X, LCD_OFFSET_Y);
    qp_clear(lcd);
    qp_rect(lcd, 0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1, HSV_BLACK, true);
    qp_power(lcd, true);
    qp_flush(lcd);

    // Initialise the LCD surface
    qp_init(lcd_surface, LCD_ROTATION);
    qp_rect(lcd_surface, 0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1, HSV_BLACK, true);
    qp_surface_draw(lcd_surface, lcd, 0, 0, 0);
    qp_flush(lcd);

    if(!module_post_init_user()) { return false; }

    return true;
}

// Called from halcyon.c
bool display_module_housekeeping_task_kb(bool second_display) {
    if(!display_module_housekeeping_task_user(second_display)) { return false; }

    if(second_display) {
        static uint32_t last_draw = 0;
        static bool second_display_set = false;
        static uint32_t previous_matrix_activity_time = 0;

        if(!second_display_set) {
            srand(get_random_32bit());
            init_grid();
            color_value = rand() % 8;
            second_display_set = true;
        }

        if (timer_elapsed32(last_draw) >= 100) { // Throttle to 10 fps
            draw_grid();
            update_grid();

            if (previous_matrix_activity_time != last_matrix_activity_time()) {
                color_value = rand() % 8;
                add_cell_cluster();
                previous_matrix_activity_time = last_matrix_activity_time();
            }

            last_draw = timer_read32();
        }
    }

    // Update display information (layers, numlock, etc.)
    if(!second_display) {
        update_display();
    }

    // Move surface to lcd
    qp_surface_draw(lcd_surface, lcd, 0, 0, 0);
    qp_flush(lcd);

    return true;
}
