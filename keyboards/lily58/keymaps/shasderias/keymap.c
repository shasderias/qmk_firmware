#include QMK_KEYBOARD_H
#include "print.h"

#define CK_LOEN LT(_LOWER, KC_ENT)
#define CK_RAEN LT(_RAISE, KC_ENT)
#define CK_SHSP MT(MOD_LSFT, KC_SPC)
#define CK_MOFN MO(_FUNC)
#define CK_TDAO TD(TD_ALT)
#define CK_TDCO TD(TD_CTRL)
#define CK_TDCA TD(TD_CAPS)

enum tap_dance_state {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD,
};

enum layer_number {
    _QWERTY = 0,
    _GAME,
    _LOWER,
    _RAISE,
    _FUNC,
    _NUMBER,
    _CAPS,
};

enum {
    TD_ALT,
    TD_CTRL,
    TD_CAPS,
};

enum custom_keycodes { KC_CCCV = SAFE_RANGE };

static uint16_t copy_paste_timer;
void            td_alt_finished(tap_dance_state_t *state, void *user_data);
void            td_alt_reset(tap_dance_state_t *state, void *user_data);
void            td_ctrl_finished(tap_dance_state_t *state, void *user_data);
void            td_ctrl_reset(tap_dance_state_t *state, void *user_data);
void            td_caps_finished(tap_dance_state_t *state, void *user_data);
void            td_caps_reset(tap_dance_state_t *state, void *user_data);

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// SPECIMEN
// [_LAYER] = LAYOUT(
// ╭───────┬───────┬───────┬───────┬───────┬───────╮                    ╭───────┬───────┬───────┬───────┬───────┬───────╮
//  _______,_______,_______,_______,_______,_______,                     _______,_______,_______,_______,_______,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┤                    ├───────┼───────┼───────┼───────┼───────┼───────┤
//  _______,_______,_______,_______,_______,_______,                     _______,_______,_______,_______,_______,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┤                    ├───────┼───────┼───────┼───────┼───────┼───────┤
//  _______,_______,_______,_______,_______,_______,                     _______,_______,_______,_______,_______,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────╮    ╭───────┼───────┼───────┼───────┼───────┼───────┼───────┤
//  _______,_______,_______,_______,_______,_______,_______,     _______,_______,_______,_______,_______,_______,_______,
// ╰───────┴───────┴───────┼───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┼───────┴───────┴───────╯
//                          _______,_______,_______,_______,     _______,_______,_______,_______
//                         ╰───────┴───────┴───────┴───────╯    ╰───────┴───────┴───────┴───────╯
//),

 [_QWERTY] = LAYOUT(
// ╭───────┬───────┬───────┬───────┬───────┬───────╮                    ╭───────┬───────┬───────┬───────┬───────┬───────╮
    KC_ESC , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                      KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_BSPC,
// ├───────┼───────┼───────┼───────┼───────┼───────┤                    ├───────┼───────┼───────┼───────┼───────┼───────┤
    KC_TAB , KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,                      KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,KC_BSLS,
// ├───────┼───────┼───────┼───────┼───────┼───────┤                    ├───────┼───────┼───────┼───────┼───────┼───────┤
    KC_LSFT, KC_A  , KC_S  , KC_D  , KC_F  , KC_G  ,                      KC_H  , KC_J  , KC_K  , KC_L  ,KC_SCLN,KC_QUOT,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────╮    ╭───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    CK_TDCO, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,KC_CCCV,     QK_LEAD, KC_N  , KC_M  ,KC_COMM,KC_DOT ,KC_SLSH,CK_TDCA,
// ╰───────┴───────┴───────┼───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┼───────┴───────┴───────╯
                            KC_LGUI,CK_TDAO,CK_LOEN,CK_SHSP,     KC_SPC ,CK_RAEN,KC_DEL ,CK_MOFN
//                         ╰───────┴───────┴───────┴───────╯    ╰───────┴───────┴───────┴───────╯
),

[_GAME] = LAYOUT(
// ╭───────┬───────┬───────┬───────┬───────┬───────╮                    ╭───────┬───────┬───────┬───────┬───────┬───────╮
    _______,_______,_______,_______,_______,_______,                     _______,_______,_______,_______,_______,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┤                    ├───────┼───────┼───────┼───────┼───────┼───────┤
    _______,_______,_______,_______,_______,_______,                     _______,_______,_______,_______,_______,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┤                    ├───────┼───────┼───────┼───────┼───────┼───────┤
    _______,_______,_______,_______,_______,_______,                     _______,_______,_______,_______,_______,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────╮    ╭───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    KC_LCTL,_______,_______,_______,_______,_______,_______,     _______,_______,_______,_______,_______,_______,_______,
// ╰───────┴───────┴───────┼───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┼───────┴───────┴───────╯
                            _______,KC_LALT,KC_ENT ,KC_SPC ,     _______,_______,_______,_______
//                         ╰───────┴───────┴───────┴───────╯    ╰───────┴───────┴───────┴───────╯
),

[_LOWER] = LAYOUT(
// ╭───────┬───────┬───────┬───────┬───────┬───────╮                    ╭───────┬───────┬───────┬───────┬───────┬───────╮
    KC_GRV ,_______,_______,KC_LABK,KC_RABK,_______,                     _______,KC_EXLM,KC_EQL ,_______,_______,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┤                    ├───────┼───────┼───────┼───────┼───────┼───────┤
    KC_TILD,_______,_______,KC_LBRC,KC_RBRC,_______,                     _______,KC_COLN,KC_EQL ,_______,_______,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┤                    ├───────┼───────┼───────┼───────┼───────┼───────┤
    _______,_______,_______,KC_LCBR,KC_RCBR,_______,                     CW_TOGG,KC_MINS,KC_EQL ,_______,_______,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────╮    ╭───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    _______,_______,_______,_______,_______,_______,_______,     CW_TOGG,_______,KC_UNDS,KC_PLUS,_______,_______,_______,
// ╰───────┴───────┴───────┼───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┼───────┴───────┴───────╯
                            _______,_______,_______,_______,     _______,_______,_______,_______
//                         ╰───────┴───────┴───────┴───────╯    ╰───────┴───────┴───────┴───────╯
),

[_RAISE] = LAYOUT(
// ╭───────┬───────┬───────┬───────┬───────┬───────╮                    ╭───────┬───────┬───────┬───────┬───────┬───────╮
    _______,_______,_______,_______,_______,_______,                     _______,_______,_______,_______,_______,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┤                    ├───────┼───────┼───────┼───────┼───────┼───────┤
    _______,_______,_______,_______,_______,_______,                     KC_PGUP,KC_HOME,KC_UP  ,KC_END ,_______,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┤                    ├───────┼───────┼───────┼───────┼───────┼───────┤
    _______,_______,_______,_______,_______,_______,                     KC_PGDN,KC_LEFT,KC_DOWN,KC_RGHT,_______,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────╮    ╭───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    _______,_______,_______,_______,_______,_______,_______,     _______,_______,_______,_______,_______,_______,_______,
// ╰───────┴───────┴───────┼───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┼───────┴───────┴───────╯
                            _______,_______,_______,_______,     _______,_______,_______,_______
//                         ╰───────┴───────┴───────┴───────╯    ╰───────┴───────┴───────┴───────╯
),

[_FUNC] = LAYOUT(
// ╭───────┬───────┬───────┬───────┬───────┬───────╮                    ╭───────┬───────┬───────┬───────┬───────┬───────╮
    KC_F1  ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,KC_F6  ,                     KC_F7  ,KC_F8  ,KC_F9  ,KC_F10 ,KC_F11 ,KC_F12 ,
// ├───────┼───────┼───────┼───────┼───────┼───────┤                    ├───────┼───────┼───────┼───────┼───────┼───────┤
    _______,_______,_______,_______,_______,_______,                     _______,_______,_______,_______,_______,KC_PSCR,
// ├───────┼───────┼───────┼───────┼───────┼───────┤                    ├───────┼───────┼───────┼───────┼───────┼───────┤
    _______,_______,_______,_______,_______,_______,                     _______,_______,_______,_______,_______,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────╮    ╭───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    _______,_______,_______,_______,_______,_______,_______,     _______,_______,_______,_______,_______,_______,_______,
// ╰───────┴───────┴───────┼───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┼───────┴───────┴───────╯
                            _______,_______,_______,_______,     _______,_______,_______,_______
//                         ╰───────┴───────┴───────┴───────╯    ╰───────┴───────┴───────┴───────╯
),

[_NUMBER] = LAYOUT(
// ╭───────┬───────┬───────┬───────┬───────┬───────╮                    ╭───────┬───────┬───────┬───────┬───────┬───────╮
    _______,_______,_______,_______,_______,_______,                     _______,_______,_______,_______,_______,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┤                    ├───────┼───────┼───────┼───────┼───────┼───────┤
    _______,_______,_______,_______,_______,_______,                     _______,KC_P7  ,KC_P8  ,KC_P9  ,KC_PPLS,KC_PPLS,
// ├───────┼───────┼───────┼───────┼───────┼───────┤                    ├───────┼───────┼───────┼───────┼───────┼───────┤
    _______,_______,_______,_______,_______,_______,                     _______,KC_P4  ,KC_P5  ,KC_P6  ,KC_PENT,KC_PENT,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────╮    ╭───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    _______,_______,_______,_______,_______,_______,_______,     _______,_______,KC_P1  ,KC_P2  ,KC_P3  ,KC_PENT,KC_PENT,
// ╰───────┴───────┴───────┼───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┼───────┴───────┴───────╯
                            _______,_______,_______,_______,     KC_P0  ,KC_PDOT,_______,_______
//                         ╰───────┴───────┴───────┴───────╯    ╰───────┴───────┴───────┴───────╯
),

[_CAPS] = LAYOUT(
// ╭───────┬───────┬───────┬───────┬───────┬───────╮                    ╭───────┬───────┬───────┬───────┬───────┬───────╮
    _______,_______,_______,_______,_______,_______,                     _______,_______,_______,_______,_______,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┤                    ├───────┼───────┼───────┼───────┼───────┼───────┤
    _______,_______,_______,_______,_______,_______,                     _______,_______,_______,_______,_______,KC_UNDS,
// ├───────┼───────┼───────┼───────┼───────┼───────┤                    ├───────┼───────┼───────┼───────┼───────┼───────┤
    _______,_______,_______,_______,_______,_______,                     _______,_______,_______,_______,_______,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────╮    ╭───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    _______,_______,_______,_______,_______,_______,_______,     _______,_______,_______,_______,_______,_______,_______,
// ╰───────┴───────┴───────┼───────┼───────┼───────┼───────┤    ├───────┼───────┼───────┼───────┼───────┴───────┴───────╯
                            _______,_______,_______,KC_UNDS,     KC_UNDS,_______,_______,_______
//                         ╰───────┴───────┴───────┴───────╯    ╰───────┴───────┴───────┴───────╯
),

};
// clang-format on

uint32_t led_off_callback(uint32_t trigger_time, void *cb_arg) {
    rgblight_sethsv_noeeprom(HSV_BLACK);
    return 0;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_CCCV:
            if (record->event.pressed) {
                copy_paste_timer = timer_read();
            } else {
                if (timer_elapsed(copy_paste_timer) > TAPPING_TERM) { // hold - copy
                    tap_code16(LCTL(KC_C));
                } else { // tap - paste
                    tap_code16(LCTL(KC_V));
                }
            }
            break;
    }
    return true;
}

void leader_start_user(void) {
    rgblight_sethsv_noeeprom(HSV_PURPLE);
}

void leader_end_user(void) {
    if (leader_sequence_one_key(KC_Q)) {
        defer_exec(500, led_off_callback, NULL);
        rgblight_sethsv_noeeprom(HSV_GOLD);
        layer_off(_GAME);
    } else if (leader_sequence_one_key(KC_G)) {
        defer_exec(500, led_off_callback, NULL);
        rgblight_sethsv_noeeprom(HSV_BLUE);
        layer_on(_GAME);
    } else if (leader_sequence_one_key(KC_P)) {
        rgblight_sethsv_noeeprom(HSV_BLACK);
        SEND_STRING(SS_DOWN(X_LSFT) SS_TAP(X_INS) SS_UP(X_LSFT));
    } else if (leader_sequence_two_keys(KC_ESCAPE, KC_BACKSPACE)) {
        rgblight_sethsv_noeeprom(HSV_BLACK);
        bootloader_jump();
    }
}

enum tap_dance_state calc_state(tap_dance_state_t *state) {
    switch (state->count) {
        case 1:
            if (state->pressed)
                return TD_SINGLE_HOLD;
            else
                return TD_SINGLE_TAP;
        case 2:
            if (state->pressed)
                return TD_DOUBLE_HOLD;
            else
                return TD_DOUBLE_TAP;
        case 3:
            if (state->interrupted || !state->pressed)
                return TD_TRIPLE_TAP;
            else
                return TD_TRIPLE_HOLD;
    }
    return TD_UNKNOWN;
}

static enum tap_dance_state alt_td_state;

void td_alt_finished(tap_dance_state_t *state, void *user_data) {
    alt_td_state = calc_state(state);
    switch (alt_td_state) {
        case TD_SINGLE_TAP:
            set_oneshot_layer(_QWERTY, ONESHOT_START);
            clear_oneshot_layer_state(ONESHOT_PRESSED);
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_LEFT_ALT);
            break;
        case TD_DOUBLE_TAP:
            set_oneshot_mods(MOD_BIT(KC_LEFT_ALT));
            set_oneshot_layer(_FUNC, ONESHOT_START);
            clear_oneshot_layer_state(ONESHOT_PRESSED);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_LEFT_ALT);
            layer_on(_FUNC);
            break;
        default:
            break;
    }
}

void td_alt_reset(tap_dance_state_t *state, void *user_data) {
    switch (alt_td_state) {
        case TD_SINGLE_TAP:
            break;
        case TD_SINGLE_HOLD:
            unregister_code(KC_LEFT_ALT);
            break;
        case TD_DOUBLE_TAP:
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_LEFT_ALT);
            layer_off(_FUNC);
            break;
        default:
            break;
    }
}

static enum tap_dance_state ctrl_td_state;

void td_ctrl_finished(tap_dance_state_t *state, void *user_data) {
    ctrl_td_state = calc_state(state);
    switch (ctrl_td_state) {
        case TD_SINGLE_TAP:
            set_oneshot_layer(_QWERTY, ONESHOT_START);
            clear_oneshot_layer_state(ONESHOT_PRESSED);
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_LEFT_CTRL);
            break;
        case TD_DOUBLE_TAP:
            set_oneshot_mods(MOD_BIT(KC_LEFT_ALT));
            set_oneshot_layer(_FUNC, ONESHOT_START);
            clear_oneshot_layer_state(ONESHOT_PRESSED);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_LEFT_CTRL);
            layer_on(_FUNC);
            break;
        default:
            break;
    }
}

void td_ctrl_reset(tap_dance_state_t *state, void *user_data) {
    switch (ctrl_td_state) {
        case TD_SINGLE_TAP:
            break;
        case TD_SINGLE_HOLD:
            unregister_code(KC_LEFT_CTRL);
            break;
        case TD_DOUBLE_TAP:
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_LEFT_CTRL);
            layer_off(_FUNC);
            break;
        default:
            break;
    }
}

static enum tap_dance_state caps_td_state;

void td_caps_finished(tap_dance_state_t *state, void *user_data) {
    caps_td_state = calc_state(state);
    switch (caps_td_state) {
        case TD_SINGLE_TAP:
            caps_word_on();
            break;
        case TD_SINGLE_HOLD:
            break;
        case TD_DOUBLE_TAP:
            break;
        case TD_DOUBLE_HOLD:
            break;
        default:
            break;
    }
}

void td_caps_reset(tap_dance_state_t *state, void *user_data) {
    switch (caps_td_state) {
        case TD_SINGLE_TAP:
            break;
        case TD_SINGLE_HOLD:
            break;
        case TD_DOUBLE_TAP:
            break;
        case TD_DOUBLE_HOLD:
            break;
        default:
            break;
    }
}
tap_dance_action_t tap_dance_actions[] = {
    [TD_ALT]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_alt_finished, td_alt_reset),
    [TD_CTRL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_ctrl_finished, td_ctrl_reset),
    [TD_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_caps_finished, td_caps_reset),
};

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(HSV_BLACK);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}

void caps_word_set_user(bool active) {
    if (active) {
        layer_on(_CAPS);
    } else {
        layer_off(_CAPS);
    }
}
