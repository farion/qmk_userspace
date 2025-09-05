// !!! DO NOT ADD #pragma once !!! //


// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT(layer_0_effect)
RGB_MATRIX_EFFECT(layer_1_effect)
RGB_MATRIX_EFFECT(layer_2_effect)
RGB_MATRIX_EFFECT(layer_3_effect)
RGB_MATRIX_EFFECT(layer_4_effect)
RGB_MATRIX_EFFECT(layer_5_effect)
RGB_MATRIX_EFFECT(layer_6_effect)
// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS


#define C_BK {HSV_OFF}
#define C_BL {HSV_BLUE}
#define C_RD {HSV_RED}
#define C_YW {HSV_YELLOW}
#define C_WT {HSV_WHITE}
#define C_GN {HSV_GREEN}
#define C_CY {HSV_CYAN}
#define C_MG {HSV_MAGENTA}
#define C_OR {HSV_ORANGE}


// Color LED adresses
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |   36   |  35  |  34  |  33  |  32  |  31  |                              |  31  | 32   |  33  |  34  |  35  |  36    |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |   30   |  29  |  28  |   27 |  26  |  25  |                              |   25 | 26   |  27  |  28  |  29  |   30   |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |   24   |  23  |   22 |  21  |  20  |  19  |                              |  19  |  20  |  21  |  22  |  23  |  24    |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |   18   |  17  |   16 |  15  |  14  |  13  | 12   | 11   |  |   11 |  12  |  13  |  14  |  15  |  16  |  17  |  18    |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |  10  |  9   |  8   |  7   |  6   |  |   6  |  7   |  8   |  9   |  10  |
//  *                        `----------------------------------'  `----------------------------------'

#define LAYOUT_elora_color(l36,l35,l34,l33,l32,l31,r31,r32,r33,r34,r35,r36, \
                         l30,l29,l28,l27,l26,l25,r25,r26,r27,r28,r29,r30, \
                         l24,l23,l22,l21,l20,l19,r19,r20,r21,r22,r23,r24, \
                         l18,l17,l16,l15,l14,l13,l12,l11, r11,r12,r13,r14,r15,r16,r17,r18, \
                         l10, l9,  l8,  l7,  l6,  r6,  r7,  r8,  r9,  r10, \
                         l5, l4, l3, l2, l1, l0, r0, r1, r2, r3, r4, r5 \
                         ) { \
  {l0, l1, l2, l3, l4, l5, l6, l7, l8, l9, l10, l11, l12, l13, l14, l15, l16, l17, l18, \
  l19, l20, l21, l22, l23, l24, l25, l26, l27, l28, l29, l30, l31, l32, l33, l34, l35, l36}, \
  {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15, r16, r17, r18, \
  r19, r20, r21, r22, r23, r24, r25, r26, r27, r28, r29, r30, r31, r32, r33, r34, r35, r36} \
}

const uint8_t PROGMEM colors[][2][37][3] = {
//        C_BK, C_BK, C_BK, C_BK, C_BK, C_BK,                              C_BK, C_BK, C_BK, C_BK, C_BK, C_BK,
//        C_BK, C_BK, C_BK, C_BK, C_BK, C_BK,                              C_BK, C_BK, C_BK, C_BK, C_BK, C_BK,
//        C_BK, C_BK, C_BK, C_BK, C_BK, C_BK,                              C_BK, C_BK, C_BK, C_BK, C_BK, C_BK,
//        C_BK, C_BK, C_BK, C_BK, C_BK, C_BK, C_BK, C_BK,      C_BK, C_BK, C_BK, C_BK, C_BK, C_BK, C_BK, C_BK,
//                          C_BK, C_BK, C_BK, C_BK, C_BK,      C_BK, C_BK, C_BK, C_BK, C_BK,
//        C_BK, C_BK, C_BK, C_BK, C_BK, C_BK,                              C_BK, C_BK, C_BK, C_BK, C_BK, C_BK

    // default
    [0] = LAYOUT_elora_color(
        C_BL, C_WT, C_WT, C_WT, C_WT, C_WT,                              C_WT, C_WT, C_WT, C_WT, C_WT, C_RD,
        C_BL, C_RD, C_RD, C_RD, C_RD, C_RD,                              C_RD, C_RD, C_RD, C_RD, C_RD, C_BL,
        C_BL, C_RD, C_RD, C_RD, C_OR, C_RD,                              C_RD, C_OR, C_RD, C_RD, C_RD, C_BL,
        C_BL, C_RD, C_RD, C_RD, C_RD, C_RD, C_CY, C_GN,      C_GN, C_CY, C_RD, C_RD, C_RD, C_RD, C_RD, C_RD,
                          C_GN, C_CY, C_BL, C_MG, C_YW,      C_YW, C_MG, C_BL, C_CY, C_GN,
        C_RD, C_RD, C_RD, C_RD, C_RD, C_RD,                              C_RD, C_RD, C_RD, C_RD, C_RD, C_RD
    ),

    // navigation + media
    [1] = LAYOUT_elora_color(
        C_BK, C_BK, C_BK, C_BK, C_BK, C_BK,                              C_BL, C_BK, C_BK, C_BK, C_BK, C_BK,
        C_BK, C_BK, C_BK, C_BK, C_BK, C_BK,                              C_CY, C_CY, C_YW, C_CY, C_BL, C_CY,
        C_BL, C_BK, C_BK, C_GN, C_RD, C_BL,                              C_CY, C_YW, C_YW, C_YW, C_BL, C_CY,
        C_BL, C_BK, C_BK, C_BK, C_OR, C_BL, C_BK, C_BK,      C_BK, C_BK, C_BL, C_BL, C_GN, C_BL, C_RD, C_MG,
                          C_BK, C_BK, C_BK, C_BK, C_YW,      C_YW, C_BK, C_BK, C_BK, C_BK,
        C_YW, C_YW, C_YW, C_YW, C_YW, C_YW,                              C_YW, C_YW, C_YW, C_YW, C_YW, C_YW
    ),


    // umlauts
    [2] = LAYOUT_elora_color(
        C_BK, C_CY, C_BK, C_BK, C_BK, C_BK,                              C_BK, C_BK, C_BK, C_BK, C_BK, C_CY,
        C_BK, C_CY, C_BK, C_BK, C_BK, C_BK,                              C_BK, C_OR, C_CY, C_OR, C_BK, C_CY,
        C_BK, C_OR, C_OR, C_BK, C_BK, C_BK,                              C_BK, C_BK, C_BK, C_BK, C_CY, C_BK,
        C_BK, C_BK, C_BK, C_BK, C_BK, C_BK, C_BK, C_BK,      C_BK, C_BK, C_BK, C_CY, C_BK, C_BK, C_CY, C_CY,
                          C_BK, C_BK, C_BK, C_BK, C_BK,      C_BK, C_BK, C_BK, C_BK, C_BK,
        C_OR, C_OR, C_OR, C_OR, C_OR, C_OR,                              C_OR, C_OR, C_OR, C_OR, C_OR, C_OR
    ),


    // function
    [3] = LAYOUT_elora_color(
        C_RD, C_BK, C_BK, C_BK, C_BK, C_BK,                              C_BK, C_BK, C_BK, C_BK, C_BK, C_RD,
        C_MG, C_BL, C_BL, C_BL, C_CY, C_BK,                              C_BK, C_CY, C_YW, C_MG, C_BK, C_BK,
        C_BL, C_BL, C_BL, C_BL, C_BL, C_BK,                              C_BK, C_CY, C_YW, C_MG, C_BK, C_BK,
        C_BL, C_CY, C_BL, C_BL, C_BL, C_BK, C_BK, C_BK,      C_BK, C_BK, C_BK, C_BK, C_RD, C_RD, C_BK, C_BK,
                          C_BL, C_BK, C_BL, C_BK, C_BK,      C_BK, C_BK, C_BL, C_BK, C_BK,
        C_BL, C_BL, C_BL, C_BL, C_BL, C_BL,                              C_BL, C_BL, C_BL, C_BL, C_BL, C_BL
    ),

    // symbols
    [4] = LAYOUT_elora_color(
        C_BK, C_BK, C_BK, C_BK, C_BK, C_BK,                              C_BK, C_BK, C_BK, C_BK, C_BK, C_BK,
        C_CY, C_WT, C_WT, C_WT, C_WT, C_WT,                              C_WT, C_WT, C_WT, C_WT, C_WT, C_YW,
        C_YW, C_RD, C_RD, C_YW, C_CY, C_YW,                              C_CY, C_CY, C_CY, C_CY, C_CY, C_YW,
        C_YW, C_YW, C_RD, C_RD, C_YW, C_GN, C_GN, C_BK,      C_BK, C_GN, C_GN, C_RD, C_RD, C_RD, C_YW, C_RD,
                          C_BK, C_CY, C_BK, C_BK, C_BK,      C_BK, C_BK, C_BK, C_CY, C_BK,
        C_CY, C_CY, C_CY, C_CY, C_CY, C_CY,                              C_CY, C_CY, C_CY, C_CY, C_CY, C_CY
    ),

    // sway
    [5] = LAYOUT_elora_color(
        C_RD, C_WT, C_WT, C_WT, C_WT, C_WT,                              C_WT, C_WT, C_WT, C_WT, C_WT, C_BK,
        C_BK, C_GN, C_GN, C_GN, C_GN, C_GN,                              C_BK, C_BK, C_YW, C_GN, C_GN, C_OR,
        C_BL, C_GN, C_GN, C_GN, C_GN, C_GN,                              C_GN, C_YW, C_YW, C_YW, C_BK, C_BL,
        C_BL, C_GN, C_GN, C_GN, C_GN, C_GN, C_BK, C_BK,      C_BK, C_BK, C_GN, C_BK, C_BK, C_BK, C_BK, C_BL,
                          C_GN, C_BK, C_BK, C_MG, C_BK,      C_BK, C_MG, C_BK, C_BK, C_GN,
        C_GN, C_GN, C_GN, C_GN, C_GN, C_GN,                              C_GN, C_GN, C_GN, C_GN, C_GN, C_GN
    ),

    [6] = LAYOUT_elora_color(
        C_BL, C_WT, C_WT, C_WT, C_WT, C_WT,                              C_WT, C_WT, C_WT, C_WT, C_WT, C_BK,
        C_YW, C_MG, C_OR, C_YW, C_OR, C_MG,                              C_CY, C_CY, C_CY, C_CY, C_CY, C_BK,
        C_BL, C_BL, C_YW, C_YW, C_YW, C_OR,                              C_CY, C_CY, C_CY, C_CY, C_BK, C_BK,
        C_BL, C_CY, C_CY, C_CY, C_CY, C_CY, C_BK, C_MG,      C_BK, C_BK, C_CY, C_CY, C_BK, C_BK, C_BK, C_BK,
                          C_BK, C_RD, C_GN, C_WT, C_BL,      C_BK, C_BK, C_BK, C_BK, C_RD,
        C_BL, C_BL, C_BL, C_BL, C_BL, C_BL,                              C_BL, C_BL, C_BL, C_BL, C_BL, C_BL
    )

};


static void rgb_set_color_layout(uint8_t layer) {

    #define TOTAL_COLOR_LAYOUTS (sizeof(colors) / sizeof(colors[0]))
    if (layer >= TOTAL_COLOR_LAYOUTS) {
        return;
    }

    uint8_t side;

    if(is_keyboard_left()){
        side = 0;
    }else{
        side = 1;
    }

    for (uint8_t col = 0; col < 37; col++) {
        hsv_t base_hsv = {
            .h = colors[layer][side][col][0],
            .s = colors[layer][side][col][1],
            .v = colors[layer][side][col][2]
        };
        hsv_t adjusted_hsv = {
            .h = (base_hsv.h + rgb_matrix_config.hsv.h) % 255, // Blend or adjust hue
            .s = (base_hsv.s * rgb_matrix_config.hsv.s) / 255, // Modulate saturation
            .v = (base_hsv.v * rgb_matrix_config.hsv.v) / 255  // Modulate brightness/value
        };
        rgb_t rgb = hsv_to_rgb(adjusted_hsv);
        rgb_matrix_set_color(col, rgb.r, rgb.g, rgb.b);
    }
}

bool layer_0_effect(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    rgb_set_color_layout(0);
    return rgb_matrix_check_finished_leds(led_max);
}
bool layer_1_effect(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    rgb_set_color_layout(1);
    return rgb_matrix_check_finished_leds(led_max);
}
bool layer_2_effect(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    rgb_set_color_layout(2);
    return rgb_matrix_check_finished_leds(led_max);
}
bool layer_3_effect(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    rgb_set_color_layout(3);
    return rgb_matrix_check_finished_leds(led_max);
}
bool layer_4_effect(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    rgb_set_color_layout(4);
    return rgb_matrix_check_finished_leds(led_max);
}
bool layer_5_effect(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    rgb_set_color_layout(5);
    return rgb_matrix_check_finished_leds(led_max);
}
bool layer_6_effect(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    rgb_set_color_layout(6);
    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
