#include QMK_KEYBOARD_H

#include "tapdance.h"

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}
/*
// ### A ###

static td_tap_t atap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void a_finished(tap_dance_state_t *state, void *user_data) {
    atap_state.state = cur_dance(state);
    switch (atap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_A); break;
        case TD_SINGLE_HOLD: register_code(KC_LSFT); break;
        case TD_DOUBLE_TAP: register_code(KC_RALT); register_code(KC_Q); break;
        case TD_DOUBLE_HOLD: tap_code(KC_A); register_code(KC_LSFT); break;
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_A); register_code(KC_RALT); register_code(KC_Q); break;
        default: break;
    }
}

void a_reset(tap_dance_state_t *state, void *user_data) {
    switch (atap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_A); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LSFT); break;
        case TD_DOUBLE_TAP: unregister_code(KC_Q); unregister_code(KC_RALT); break;
        case TD_DOUBLE_HOLD: unregister_code(KC_LSFT); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_Q); unregister_code(KC_RALT); break;
        default: break;
    }
    atap_state.state = TD_NONE;
}

// ### U ###
static td_tap_t utap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void u_finished(tap_dance_state_t *state, void *user_data) {
    utap_state.state = cur_dance(state);
    switch (utap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_U); break;
        case TD_SINGLE_HOLD: break;
        case TD_DOUBLE_TAP: register_code(KC_RALT); register_code(KC_Y); break;
        case TD_DOUBLE_HOLD: tap_code(KC_U); break;
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_U); register_code(KC_RALT); register_code(KC_Y); break;
        default: break;
    }
}

void u_reset(tap_dance_state_t *state, void *user_data) {
    switch (utap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_U); break;
        case TD_SINGLE_HOLD:  break;
        case TD_DOUBLE_TAP: unregister_code(KC_Y); unregister_code(KC_RALT); break;
        case TD_DOUBLE_HOLD:  break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_Y); unregister_code(KC_RALT); break;
        default: break;
    }
    utap_state.state = TD_NONE;
}

// ### O ###
static td_tap_t otap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void o_finished(tap_dance_state_t *state, void *user_data) {
    otap_state.state = cur_dance(state);
    switch (otap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_O); break;
        case TD_SINGLE_HOLD: break;
        case TD_DOUBLE_TAP: register_code(KC_RALT); register_code(KC_P); break;
        case TD_DOUBLE_HOLD: tap_code(KC_O); break;
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_O); register_code(KC_RALT); register_code(KC_P); break;
        default: break;
    }
}

void o_reset(tap_dance_state_t *state, void *user_data) {
    switch (otap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_O); break;
        case TD_SINGLE_HOLD:  break;
        case TD_DOUBLE_TAP: unregister_code(KC_P); unregister_code(KC_RALT); break;
        case TD_DOUBLE_HOLD:  break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_P); unregister_code(KC_RALT); break;
        default: break;
    }
    otap_state.state = TD_NONE;
}

// ### S ###
static td_tap_t stap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void s_finished(tap_dance_state_t *state, void *user_data) {
    stap_state.state = cur_dance(state);
    switch (stap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_S); break;
        case TD_SINGLE_HOLD: register_code(KC_LCTL); break;
        case TD_DOUBLE_TAP: register_code(KC_RALT); register_code(KC_S); break;
        case TD_DOUBLE_HOLD: tap_code(KC_S); register_code(KC_LCTL); break;
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_S); register_code(KC_RALT); register_code(KC_S); break;
        default: break;
    }
}

void s_reset(tap_dance_state_t *state, void *user_data) {
    switch (stap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_S); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LCTL); break;
        case TD_DOUBLE_TAP: unregister_code(KC_S); unregister_code(KC_RALT); break;
        case TD_DOUBLE_HOLD: tap_code(KC_S); register_code(KC_LCTL); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_S); unregister_code(KC_RALT); break;
        default: break;
    }
    stap_state.state = TD_NONE;
}*/

//static bool layer1_active = false;

void layer_tap_1(tap_dance_state_t *state, void *user_data) {
    layer_on(1);
}

void layer_reset_1(tap_dance_state_t *state, void *user_data) {
    if (state->count != 2) {
        layer_off(1);
    }
}

void layer_tap_3(tap_dance_state_t *state, void *user_data) {
    layer_on(3);
}

void layer_reset_3(tap_dance_state_t *state, void *user_data) {
    if (state->count != 2) {
        layer_off(3);
    }
}

void td_esc(tap_dance_state_t *state, void *user_data) {
    if (state->count == 4) {
        rgb_matrix_set_color(36, 0,0,255);
        reset_keyboard();
        reset_tap_dance(state);
    }
}

tap_dance_action_t my_tap_dance_actions[TAP_DANCE_ACTIONS_COUNT] = {
 /*   [TD_A] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, a_finished, a_reset),
    [TD_U] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, u_finished, u_reset),
    [TD_O] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, o_finished, o_reset),
    [TD_S] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, s_finished, s_reset),*/
    [TD_1] = ACTION_TAP_DANCE_FN_ADVANCED(layer_tap_1, NULL, layer_reset_1),
    [TD_3] = ACTION_TAP_DANCE_FN_ADVANCED(layer_tap_3, NULL, layer_reset_3),
    [TD_BL] = ACTION_TAP_DANCE_FN(td_esc),
};
