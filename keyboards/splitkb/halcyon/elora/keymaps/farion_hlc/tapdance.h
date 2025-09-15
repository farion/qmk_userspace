#define TAP_DANCE_ACTIONS_COUNT 5

enum custom_tapdances {
  /*  TD_A,
    TD_U,
    TD_O,
    TD_S,*/
    TD_1,
    TD_2,
    TD_3,
    TD_BL
};

tap_dance_action_t my_tap_dance_actions[TAP_DANCE_ACTIONS_COUNT];
extern tap_dance_action_t my_tap_dance_actions[TAP_DANCE_ACTIONS_COUNT];
#define tap_dance_actions my_tap_dance_actions
