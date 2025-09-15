// Copyright 2024 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "quantum.h"
#include "keymap_us_international.h"
#include "tapdance.h"
//#include "rgbmatrix.h"
#include "timer.h"
#include "raw_hid.h"
#include "wpm.h"
enum layers {
    _QWERTY = 0,
    _DVORAK,
    _COLEMAK_DH,
    _NAV,
    _SYM,
    _FUNCTION,
    _ADJUST,
};

// Aliases for readability
#define QWERTY   DF(_QWERTY)
#define COLEMAK  DF(_COLEMAK_DH)
#define DVORAK   DF(_DVORAK)

#define SYM      MO(_SYM)
#define NAV      MO(_NAV)
#define FKEYS    MO(_FUNCTION)
#define ADJUST   MO(_ADJUST)

#define CTL_ESC  MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS MT(MOD_RCTL, KC_MINUS)
#define ALT_ENT  MT(MOD_LALT, KC_ENT)

#define COLOR_KEY_1 {255, 0, 0}    // Red
#define COLOR_KEY_2 {0, 255, 0}    // Green
#define COLOR_KEY_3 {0, 0, 255}    // Blue

#define HR_A LSFT_T(KC_A)
#define HR_S LCTL_T(KC_S)
#define HR_D LALT_T(KC_D)
#define HR_F LT(2,KC_F)

#define HR_J LT(2, KC_J)
#define HR_K RALT_T(KC_K)
#define HR_L RCTL_T(KC_L)
#define HR_SPACE LT(2, KC_SPC)
#define HR_ENTER LT(2, KC_ENTER)
#define HR_SCLN RSFT_T(KC_SCLN)

#define L5_LGUI LM(5, MOD_LGUI)
#define L5_RGUI LM(5, MOD_RGUI)

enum custom_keycodes {
    CG_SHGI = SAFE_RANGE, // Ensure your custom keycodes start from SAFE_RANGE
    CG_RAIN,
    CG_LSFT,
    CG_RCTL,
    CG_RSFT,
    CG_LCTL,
};


/*
#define WPM_INTERVAL 1000  // Interval in milliseconds to send the WPM
static uint16_t last_wpm_time = 0;

void matrix_scan_user(void) {
    uint16_t current_time = timer_read();

    if (current_time - last_wpm_time > WPM_INTERVAL) {
        // Time to send the WPM


        // Update the last send time
        last_wpm_time = current_time;
    }
}*/

bool animation_mode = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif

        uint8_t wpm = get_current_wpm(); // Get the current WPM

        // Prepare the data to send (1-byte WPM followed by padding zeros)
        uint8_t raw_hid_data[32] = {0};
        raw_hid_data[0] = wpm;

        raw_hid_send(raw_hid_data, 32);
    switch (keycode) {

        case CG_LCTL:
            if(record->event.pressed) {
                register_code(KC_LCTL);
            } else {
                unregister_code(KC_LCTL);
            }
            return false;
        case CG_LSFT:
            if(record->event.pressed) {
                register_code(KC_LSFT);
            } else {
                unregister_code(KC_LSFT);
            }
            return false;
        case CG_RCTL:
            if(record->event.pressed) {
                register_code(KC_RCTL);
            } else {
                unregister_code(KC_RCTL);
            }
            return false;
        case CG_RSFT:
            if(record->event.pressed) {
                register_code(KC_RSFT);
            } else {
                unregister_code(KC_RSFT);
            }
            return false;
        case CG_SHGI:
            if (record->event.pressed) {
                // When the key is pressed, register Ctrl and GUI
                register_code(KC_LCTL);
                register_code(KC_LGUI);
            } else {
                // When the key is released, unregister Ctrl and GUI
                unregister_code(KC_LCTL);
                unregister_code(KC_LGUI);
            }
            return false; // Skip all further processing of this key
        case CG_RAIN:
            if (record->event.pressed) {
                uprintf("Rain mode activated\n");
                rgb_matrix_mode(RGB_MATRIX_DIGITAL_RAIN);
                rgb_matrix_set_speed(255);
            }
            return false;
        default:
            return true; // Process other keycodes normally
    }
}




// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT_elora_hlc(
     KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                   /**/                   KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINUS,
     KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                   /**/                   KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC,
     KC_LSFT, HR_A   , HR_S   , HR_D   , HR_F   , KC_G   ,                   /**/                   KC_H   , HR_J   , HR_K   , HR_L   , HR_SCLN, KC_RSFT,
     KC_LCTL, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_LBRC, CG_RAIN ,/**/ RM_TOGG, KC_RBRC, KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_QUOTE,
                                L5_LGUI, MO(4)  ,TD(TD_2), HR_SPACE,TD(TD_1),/**/ TD(TD_1),HR_ENTER,TD(TD_2),MO(4)  , L5_RGUI  ,
     KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
    ),

    [1] = LAYOUT_elora_hlc(
     _______  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                   /**/                   TG(6)  , KC_NO  , KC_NO  , KC_NO  , TG(0)  , KC_NO,
     _______  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                   /**/                   KC_PGUP, KC_HOME, KC_UP  , KC_END , KC_VOLU, KC_DEL,
     _______, KC_NO  , KC_NO  , MS_BTN1, MS_BTN2, MS_WHLU,                   /**/                   KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD, KC_INS,
     _______, KC_NO  , KC_NO  , KC_NO  , MS_BTN3, MS_WHLD, KC_NO  , KC_NO  , /**/ KC_NO  , KC_NO  , KC_PAUSE,KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_PSCR,
                                KC_NO  , KC_NO  , KC_NO  , KC_NO  , _______  , /**/_______ , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
     KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                                                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO
    ),

    [2] = LAYOUT_elora_hlc(
     _______  , KC_GRV  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                   /**/                   KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_PLUS,
     _______  , KC_AT  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                   /**/                   KC_NO  , US_UDIA, KC_PIPE, US_ODIA, KC_NO  , KC_DEL,
     _______  , US_ADIA, US_SS  , KC_NO  , KC_NO  , KC_NO  ,                   /**/                   KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_TILD, _______,
     _______  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , /**/ KC_NO  , KC_NO  , KC_NO  , RALT(KC_M),KC_NO, KC_NO  , KC_BSLS, KC_EQL,
                                KC_NO  , KC_NO  , _______  , KC_NO  , KC_NO  , /**/ KC_NO  , KC_NO  , _______  , KC_NO  , KC_NO  ,
     KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                                                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO
    ),

    [3] = LAYOUT_elora_hlc(
     TD(TD_BL), KC_NO,  KC_NO , KC_NO  , KC_NO  , KC_NO  ,                   /**/                   KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , TD(TD_BL),
     DB_TOGG,  KC_F9 ,  KC_F10, KC_F11 , KC_F12 , KC_NO  ,                   /**/                   CG_RAIN, RM_HUEU, RM_SATU, RM_VALU, KC_NO  , KC_NO,
     KC_LSFT , KC_F5 ,  KC_F6 , KC_F7  , KC_F8  , KC_NO  ,                   /**/                   KC_NO  , RM_HUED, RM_SATD, RM_VALD, KC_NO  , KC_NO,
     KC_LCTL , KC_F1 ,  KC_F2 , KC_F3  , KC_F4  , KC_NO  , KC_NO  , KC_NO  , /**/ KC_NO  , KC_NO  , KC_NO  , KC_NO  , RM_PREV, RM_NEXT, KC_NO  , KC_NO,
                                KC_LALT  , KC_NO  , _______  , KC_NO  , KC_NO  , /**/ KC_NO  , KC_NO  , _______  , KC_NO  , KC_NO  ,
     KC_NO  , KC_NO  ,  KC_NO , KC_NO  , KC_NO  ,                                                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO
    ),

    // symbols
    [4] = LAYOUT_elora_hlc(
     KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                   /**/                   KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
     KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                   /**/                   KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_EQL ,
     KC_TILD, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC,                   /**/                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PLUS,
     KC_PIPE, KC_BSLS, KC_COLN, KC_SCLN, KC_MINS, KC_LBRC, KC_LCBR, KC_NO  , /**/ KC_NO  , KC_RCBR, KC_RBRC, KC_UNDS, KC_COMM, KC_DOT , KC_SLSH, KC_QUES,
                                KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , /**/ KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
     KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                                                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO
    ),

    // sw
    [5] = LAYOUT_elora_hlc(
     C(KC_L), KC_1   , KC_2   , KC_3   , KC_4   , KC_5,                      /**/                   KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_NO,
     KC_NO  , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T,                      /**/                   KC_NO  , KC_NO  , KC_UP  , KC_O   , KC_P   , KC_BSPC,
     CG_LSFT, KC_A   , KC_S   , KC_D   , KC_F   , KC_G,                      /**/                   KC_H, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO  , CG_RSFT,
     CG_LCTL, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B,    KC_NO  , KC_NO  , /**/ KC_NO  , KC_NO  , KC_N, KC_NO  , KC_NO  , KC_NO  , KC_NO  , CG_RCTL,
                                KC_NO  , KC_NO  , KC_NO, KC_SPACE  , KC_NO , /**/ KC_NO  , KC_ENTER,KC_NO  , KC_NO  , KC_NO  ,
     KC_NO  , KC_NO  , KC_NO  , KC_NO,KC_NO  ,                                                            KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO
    ),

    [6] = LAYOUT_elora_hlc(
     KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                   /**/                   KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_NO,
     KC_TAB , KC_F   , KC_Q   , KC_W   , KC_E   , KC_R   ,                   /**/                   KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_NO,
     KC_LSFT, LALT(KC_A),KC_A , KC_S   , KC_D   , KC_G   ,                   /**/                   KC_H   , KC_J   , KC_K   , KC_L   , KC_NO,   KC_NO,
     KC_LCTL, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_NO, LALT(KC_L),/**/ RM_TOGG, KC_RBRC, KC_N   , KC_M   , KC_NO  , KC_NO  , KC_NO  , KC_NO,
                                KC_NO  ,LALT(KC_M),LALT(KC_K),KC_SPACE, KC_T,/**/ KC_NO  , KC_NO  , KC_NO  , KC_NO  , TG(6)  ,
     KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
    ),
};
/*
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),  ENCODER_CCW_CW(KC_VOLD, KC_VOLU),  ENCODER_CCW_CW(KC_PGUP, KC_PGDN),  ENCODER_CCW_CW(KC_PGUP, KC_PGDN)  },
    [1] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [2] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [3] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [4] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [5] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
    [6] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______)  },
};
#endif

*/
layer_state_t layer_state_set_user(layer_state_t state) {

    switch(get_highest_layer(state)){
        case 0:
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_layer_0_effect);
            break;
        case 1:
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_layer_1_effect);
            break;
        case 2:
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_layer_2_effect);
            break;
        case 3:
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_layer_3_effect);
            break;
        case 4:
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_layer_4_effect);
            break;
        case 5:
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_layer_5_effect);
            break;
        case 6:
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_layer_6_effect);
            break;
        default:
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_layer_0_effect);
            break;
    }

    //rgb_matrix_mode(RGB_MATRIX_CUSTOM_my_cool_effect);
    //rgb_set_color_layout(get_highest_layer(layer_state|default_layer_state));
    return state;
}

void keyboard_post_init_user(void) {
    rgb_matrix_mode(RGB_MATRIX_CUSTOM_layer_0_effect);
}


enum combo_events {
    VISAVE
};

const uint16_t PROGMEM combo1[] = {KC_ESC, KC_1, COMBO_END};
combo_t key_combos[] = {
    [VISAVE] = COMBO_ACTION(combo1),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case VISAVE:
      if (pressed) {
        tap_code16(KC_ESC);
        tap_code16(KC_COLN);
        tap_code16(KC_W);
        wait_ms(200);
        tap_code16(KC_ENTER);
      }
      break;
  }
}
