/*
#include QMK_KEYBOARD_H

#define C_BK {0,0,0}
#define C_BL {0,0,255}
#define C_RD {255,0,0}
#define C_YW {255,220,0}
#define C_WT {255,255,255}
#define C_GN {0,255,0}
#define C_CY {0,255,255}
#define C_MG {255,0,255}
#define C_OR {255, 80, 0}


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
        C_BK, C_BK, C_BK, C_BK, C_BK, C_BK,                              C_BK, C_BK, C_BK, C_BK, C_BK, C_CY,
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

void rgb_set_color_layout(uint8_t layer) {



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
        uint8_t r = pgm_read_byte(&colors[layer][side][col][0]);
        uint8_t g = pgm_read_byte(&colors[layer][side][col][1]);
        uint8_t b = pgm_read_byte(&colors[layer][side][col][2]);
        rgb_matrix_set_color(col, r, g, b);
    }
}
*/

/*RGB_MATRIX_EFFECT(layer_1_effect)

static bool layer_1_effect(effect_params_t* params) {
  rgb_set_color_layout(1);
    return true;
}

*/
/*
bool rgb_matrix_indicators_kb(void) {

    if (!rgb_matrix_indicators_user()) {
        return false;
    }
     rgb_set_color_layout(get_highest_layer(layer_state|default_layer_state));
   return true;
}
*/

/*
layer_state_t layer_state_set_user(layer_state_t state) {
    //rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_layer_1_effect);
    rgb_matrix_mode(RGB_MATRIX_CUSTOM_my_cool_effect);
    //rgb_set_color_layout(get_highest_layer(layer_state|default_layer_state));
    return state;
}

*/
