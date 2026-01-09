/* Copyright 2025 Carlos Eduardo de Paula <carlosedp@gmail.com>
 * Copyright 2025 EPOMAKER <https://github.com/Epomaker>
 * Copyright 2023 LiWenLiu <https://github.com/LiuLiuQMK>
 * Copyright 2021 QMK <https://github.com/qmk/qmk_firmware>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "rdmctmzt_common.h"
#include "config.h"
#include "../../../../../quantum/keycodes.h"
#include "../../../../../quantum/eeconfig.h"
#include "../../../../../quantum/keymap_extras/keymap_us.h"

#define SHSP MT(MOD_LSFT, KC_SPC)
#define LOSP LT(_LOWER, KC_SPC)

#define CK_ESC LT(_LOWER, KC_ESC)
#define CK_BPSP LT(_RAISE, KC_BSPC)

#define MOUT MO(_UTILITY)

#define CK_TAB LT(_NUM, KC_TAB)

#define TC_ALT TD(TD_ALT)
#define TC_CTRL TD(TD_CTRL)
#define TC_SHFT TD(TD_SHIFT)
#define CK_TDCA TD(TD_CAPS)
#define CK_TDRC TD(TD_RCTRL)
#define CK_RSFT MO(_RIGHT_SHIFT)
#define CK_LGUI TD(TD_LGUI)

#define CK_LSPC TD(TD_LEFT_SPACE)
#define CK_FN MO(_FUNC)
#define CK_RSPC LT(_RAISE, KC_SPC)

#define KC_SF1 S(KC_F1)
#define KC_SF2 S(KC_F2)
#define KC_SF3 S(KC_F3)
#define KC_SF4 S(KC_F4)
#define KC_SF5 S(KC_F5)
#define KC_SF6 S(KC_F6)
#define KC_SF7 S(KC_F7)
#define KC_SF8 S(KC_F8)
#define KC_SF9 S(KC_F9)
#define KC_SF10 S(KC_F10)
#define KC_SF11 S(KC_F11)
#define KC_SF12 S(KC_F12)

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
    _LOWER,
    _RAISE,
    _FUNC,
    _RCTRL,
    _NUM,
    _TD_FN,
    _OSL_LSPC,
    _RIGHT_SHIFT,
};

enum {
    TD_ALT,
    TD_CTRL,
    TD_CAPS,
    TD_RCTRL,
    TD_SHIFT,
    TD_LEFT_SPACE,
    TD_RIGHT_SPACE,
    TD_LGUI,
};

void td_alt_finished(tap_dance_state_t *state, void *user_data);
void td_alt_reset(tap_dance_state_t *state, void *user_data);
void td_ctrl_finished(tap_dance_state_t *state, void *user_data);
void td_ctrl_reset(tap_dance_state_t *state, void *user_data);
void td_caps_finished(tap_dance_state_t *state, void *user_data);
void td_caps_reset(tap_dance_state_t *state, void *user_data);
void td_rctrl_finished(tap_dance_state_t *state, void *user_data);
void td_rctrl_reset(tap_dance_state_t *state, void *user_data);
void td_shift_finished(tap_dance_state_t *state, void *user_data);
void td_shift_reset(tap_dance_state_t *state, void *user_data);
void td_left_space_finished(tap_dance_state_t *state, void *user_data);
void td_left_space_reset(tap_dance_state_t *state, void *user_data);
void td_right_space_finished(tap_dance_state_t *state, void *user_data);
void td_right_space_reset(tap_dance_state_t *state, void *user_data);
void td_lgui_finished(tap_dance_state_t *state, void *user_data);
void td_lgui_reset(tap_dance_state_t *state, void *user_data);

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// SPECIMEN
// [_LAYER] = LAYOUT_tkl_ansi(
// ╭───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────╮
//  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┴───────┤
//  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,    _______    ,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┬───────┤
//  _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
// ├───────┼───────┼───────┼───────┴───────┴───┬───┴───┬───┴───────┴───────┼───────┼───────┼───────┤
//  _______,_______,_______,      _______      ,_______,      _______      ,_______,_______,_______
// ╰───────┴───────┴───────┴───────────────────┴───────┴───────────────────┴───────┴───────┴───────╯
//),

 [_QWERTY] = LAYOUT_tkl_ansi(
// ╭───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────╮
    CK_ESC , KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  , KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,CK_BPSP,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┴───────┤
    CK_TAB , KC_A  , KC_S  , KC_D  , KC_F  , KC_G  , KC_H  , KC_J  , KC_K  , KC_L  ,    KC_ENT     ,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┬───────┤
    TC_SHFT,KC_SLSH, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  , KC_N  , KC_M  ,KC_COMM,KC_DOT ,CK_RSFT,
// ├───────┼───────┼───────┼───────┴───────┴───┬───┴───┬───┴───────┴───────┼───────┼───────┼───────┤
    TC_CTRL,CK_LGUI,TC_ALT,      CK_LSPC       , CK_FN ,       CK_RSPC     ,KC_RALT,KC_APP ,CK_TDRC
// ╰───────┴───────┴───────┴───────────────────┴───────┴───────────────────┴───────┴───────┴───────╯
),

[_LOWER] = LAYOUT_tkl_ansi(
// ╭───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────╮
    KC_GRV ,_______,_______,KC_LABK,KC_RABK,_______,_______,KC_EXLM,KC_EQL ,KC_LPRN,KC_RPRN,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┴───────┤
    KC_TILD,_______,_______,KC_LBRC,KC_RBRC,_______,_______,KC_COLN,KC_EQL ,_______,    _______    ,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┬───────┤
    _______,_______,_______,_______,KC_LCBR,KC_RCBR,_______,KC_UNDS,KC_MINS,KC_PLUS,_______,_______,
// ├───────┼───────┼───────┼───────┴───────┴───┬───┴───┬───┴───────┴───────┼───────┼───────┼───────┤
    _______,_______,_______,      _______      ,_______,      _______      ,_______,_______,_______
// ╰───────┴───────┴───────┴───────────────────┴───────┴───────────────────┴───────┴───────┴───────╯
),

[_RAISE] = LAYOUT_tkl_ansi(
// ╭───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────╮
    _______,_______,_______,KC_LABK,KC_RABK,_______,KC_PGUP,KC_HOME, KC_UP ,KC_END ,_______,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┴───────┤
    _______,_______,_______,KC_LBRC,KC_RBRC,_______,KC_PGDN,KC_LEFT,KC_DOWN,KC_RGHT,    _______    ,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┬───────┤
    _______,_______,_______,_______,KC_LCBR,KC_RCBR,_______,_______,_______,_______,_______,_______,
// ├───────┼───────┼───────┼───────┴───────┴───┬───┴───┬───┴───────┴───────┼───────┼───────┼───────┤
    _______,_______,_______,      _______      ,_______,      _______      ,_______,_______,_______
// ╰───────┴───────┴───────┴───────────────────┴───────┴───────────────────┴───────┴───────┴───────╯
),


[_FUNC] = LAYOUT_tkl_ansi(
// ╭───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────╮
    KC_F1  , KC_F2 , KC_F3 , KC_F4 , KC_F5 , KC_F6 , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,KC_F12 ,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┴───────┤
    _______,MD_BLE1,MD_BLE2,MD_BLE3,MD_24G ,MD_USB ,RM_VALU,RM_SATD,_______,_______,    RM_TOGG    ,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┬───────┤
    _______,_______,RM_NEXT,RM_SPDD,RM_SPDU,_______,RM_HUED,RM_VALD,RM_HUEU,_______,_______,_______,
// ├───────┼───────┼───────┼───────┴───────┴───┬───┴───┬───┴───────┴───────┼───────┼───────┼───────┤
    _______,_______,_______,      QK_BAT       ,_______,       _______     ,_______,_______,QK_BOOT
// ╰───────┴───────┴───────┴───────────────────┴───────┴───────────────────┴───────┴───────┴───────╯
),

[_RCTRL] = LAYOUT_tkl_ansi(
// ╭───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────╮
    KC_GRV , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  , KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┴───────┤
    _______,_______,_______,_______,_______,_______,KC_LEFT,KC_DOWN, KC_UP ,KC_RGHT,    _______    ,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┴───────┤
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
// ├───────┼───────┼───────┼───────┴───────┴───┬───┴───┬───┴───────┴───────┼───────┼───────┼───────┤
    _______,_______,_______,      _______      ,_______,      _______      ,_______,_______,_______
// ╰───────┴───────┴───────┴───────────────────┴───────┴───────────────────┴───────┴───────┴───────╯
),

[_NUM] = LAYOUT_tkl_ansi(
// ╭───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────╮
    _______, KC_1  , KC_2  , KC_3  , KC_4  , KC_5  , KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┴───────┤
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,    _______    ,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┬───────┤
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
// ├───────┼───────┼───────┼───────┴───────┴───┬───┴───┬───┴───────┴───────┼───────┼───────┼───────┤
    _______,_______,_______,      _______      ,_______,      _______      ,_______,_______,_______
// ╰───────┴───────┴───────┴───────────────────┴───────┴───────────────────┴───────┴───────┴───────╯
),

[_TD_FN] = LAYOUT_tkl_ansi(
// ╭───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────╮
     KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 , KC_F6 , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,KC_F12 ,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┴───────┤
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,    _______    ,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┬───────┤
    KC_SF1 ,KC_SF2 ,KC_SF3 ,KC_SF4 ,KC_SF5 ,KC_SF6 ,KC_SF7 ,KC_SF8 ,KC_SF9 ,KC_SF10,KC_SF11,KC_SF12,
// ├───────┼───────┼───────┼───────┴───────┴───┬───┴───┬───┴───────┴───────┼───────┼───────┼───────┤
    _______,_______,_______,      _______      ,_______,      _______      ,_______,_______,_______
// ╰───────┴───────┴───────┴───────────────────┴───────┴───────────────────┴───────┴───────┴───────╯
),

[_OSL_LSPC] = LAYOUT_tkl_ansi(
// ╭───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────╮
    KC_GRV , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  , KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┴───────┤
    KC_TILD,KC_EXLM, KC_AT ,KC_HASH,KC_DLR ,KC_PERC,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,    KC_RPRN    ,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┬───────┤
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
// ├───────┼───────┼───────┼───────┴───────┴───┬───┴───┬───┴───────┴───────┼───────┼───────┼───────┤
    _______,_______,_______,      _______      ,_______,      _______      ,_______,_______,_______
// ╰───────┴───────┴───────┴───────────────────┴───────┴───────────────────┴───────┴───────┴───────╯
),

[_RIGHT_SHIFT] = LAYOUT_tkl_ansi(
// ╭───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────╮
    _______, KC_1  , KC_2  , KC_3  , KC_4  , KC_5  , KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┴───────┤
    _______,_______,_______,KC_LBRC,KC_RBRC,KC_LABK,KC_RABK,KC_COLN,KC_EQL ,KC_EQL ,    _______    ,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┬───────┤
    _______,_______,_______,_______,KC_LCBR,KC_RCBR,_______,KC_MINS,KC_UNDS,KC_PLUS,_______,_______,
// ├───────┼───────┼───────┼───────┴───────┴───┬───┴───┬───┴───────┴───────┼───────┼───────┼───────┤
    _______,_______,_______,      _______      ,_______,      _______      ,_______,_______,_______
// ╰───────┴───────┴───────┴───────────────────┴───────┴───────────────────┴───────┴───────┴───────╯
),

};
// clang-format on

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TC_ALT:
        case TC_CTRL:
        case TC_SHFT:
        case CK_LGUI:
            return TAPPING_TERM + 80;
        default:
            return TAPPING_TERM;
    }
}

const uint16_t PROGMEM combo_back_slash[] = {KC_P, KC_BSPC, COMBO_END};
const uint16_t PROGMEM combo_semicolon[]  = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM combo_slash[]      = {KC_DOT, CK_RSFT, COMBO_END};
const uint16_t PROGMEM combo_quote[]      = {KC_K, KC_L, COMBO_END};

combo_t key_combos[] = {
    COMBO(combo_back_slash, KC_BACKSLASH),
    COMBO(combo_semicolon, KC_SEMICOLON),
    COMBO(combo_slash, KC_SLASH),
    COMBO(combo_quote, KC_QUOTE),
};

enum tap_dance_state calc_state(tap_dance_state_t *state) {
    switch (state->count) {
        case 1:
            if (state->pressed) return TD_SINGLE_HOLD;
            return TD_SINGLE_TAP;
        case 2:
            if (state->pressed) return TD_DOUBLE_HOLD;
            return TD_DOUBLE_TAP;
        case 3:
            if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
            return TD_TRIPLE_HOLD;
    }
    return TD_UNKNOWN;
}

static enum tap_dance_state alt_td_state;

void td_alt_finished(tap_dance_state_t *state, void *user_data) {
    alt_td_state = calc_state(state);
    switch (alt_td_state) {
        case TD_SINGLE_TAP:
            tap_code(KC_LEFT_ALT);
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_LEFT_ALT);
            break;
        case TD_DOUBLE_TAP:
            // do nothing for now
            break;
        case TD_DOUBLE_HOLD:
            layer_on(_NUM);
            break;
        case TD_TRIPLE_TAP:
            register_code(KC_LEFT_ALT);
            // do nothing
            break;
        case TD_TRIPLE_HOLD:
            register_code(KC_LEFT_ALT);
            layer_on(_TD_FN);
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
            // do nothing for now
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_LEFT_ALT);
            layer_off(_NUM);
            break;
        case TD_TRIPLE_TAP:
            // do nothing
            break;
        case TD_TRIPLE_HOLD:
            unregister_code(KC_LEFT_ALT);
            layer_off(_TD_FN);
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
            tap_code(KC_LEFT_CTRL);
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_LEFT_CTRL);
            break;
        case TD_DOUBLE_TAP:
            // do nothing for now
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_LEFT_CTRL);
            layer_on(_NUM);
            break;
        case TD_TRIPLE_TAP:
            // do nothing
            break;
        case TD_TRIPLE_HOLD:
            register_code(KC_LEFT_CTRL);
            layer_on(_TD_FN);
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
            // do nothing for now
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_LEFT_CTRL);
            layer_off(_NUM);
            break;
        case TD_TRIPLE_TAP:
            // do nothing
            break;
        case TD_TRIPLE_HOLD:
            unregister_code(KC_LEFT_CTRL);
            layer_off(_TD_FN);
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

static enum tap_dance_state rctrl_td_state;

void td_rctrl_finished(tap_dance_state_t *state, void *user_data) {
    rctrl_td_state = calc_state(state);
    switch (rctrl_td_state) {
        case TD_SINGLE_TAP:
            tap_code(KC_RCTL);
            break;
        case TD_SINGLE_HOLD:
            layer_on(_RCTRL);
            break;
        case TD_DOUBLE_TAP:
            // do nothing (user will decide later)
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_RCTL);
            layer_on(_RCTRL);
            break;
        case TD_TRIPLE_TAP:
            // do nothing (user will decide later)
            break;
        case TD_TRIPLE_HOLD:
            // do nothing (user will decide later)
            break;
        default:
            break;
    }
}

void td_rctrl_reset(tap_dance_state_t *state, void *user_data) {
    switch (rctrl_td_state) {
        case TD_SINGLE_TAP:
            break;
        case TD_SINGLE_HOLD:
            layer_off(_RCTRL);
            break;
        case TD_DOUBLE_TAP:
            // do nothing (user will decide later)
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_RCTL);
            layer_off(_RCTRL);
            break;
        case TD_TRIPLE_TAP:
            // do nothing (user will decide later)
            break;
        case TD_TRIPLE_HOLD:
            // do nothing (user will decide later)
            break;
        default:
            break;
    }
}

static enum tap_dance_state shift_td_state;

void td_shift_finished(tap_dance_state_t *state, void *user_data) {
    shift_td_state = calc_state(state);
    switch (shift_td_state) {
        case TD_SINGLE_TAP:
            tap_code(KC_LSFT);
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_LSFT);
            break;
        case TD_DOUBLE_TAP:
            // do nothing for now
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_LSFT);
            layer_on(_NUM);
            break;
        case TD_TRIPLE_TAP:
            // do nothing
            break;
        case TD_TRIPLE_HOLD:
            register_code(KC_LSFT);
            layer_on(_TD_FN);
            break;
        default:
            break;
    }
}

void td_shift_reset(tap_dance_state_t *state, void *user_data) {
    switch (shift_td_state) {
        case TD_SINGLE_TAP:
            break;
        case TD_SINGLE_HOLD:
            unregister_code(KC_LSFT);
            break;
        case TD_DOUBLE_TAP:
            // do nothing for now
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_LSFT);
            layer_off(_NUM);
            break;
        case TD_TRIPLE_TAP:
            // do nothing
            break;
        case TD_TRIPLE_HOLD:
            unregister_code(KC_LSFT);
            layer_off(_TD_FN);
            break;
        default:
            break;
    }
}

static enum tap_dance_state right_space_td_state;

void td_right_space_finished(tap_dance_state_t *state, void *user_data) {
    right_space_td_state = calc_state(state);
    switch (right_space_td_state) {
        case TD_SINGLE_TAP:
            tap_code(KC_SPC);
            break;
        case TD_SINGLE_HOLD:
            layer_on(_RAISE);
            break;
        case TD_DOUBLE_TAP:
            tap_code(KC_SPC);
            tap_code(KC_SPC);
            break;
        case TD_DOUBLE_HOLD:
            layer_on(_LOWER);
            break;
        case TD_TRIPLE_TAP:
            tap_code(KC_SPC);
            tap_code(KC_SPC);
            tap_code(KC_SPC);
            break;
        case TD_TRIPLE_HOLD:
            // do nothing
            break;
        default:
            break;
    }
}

void td_right_space_reset(tap_dance_state_t *state, void *user_data) {
    switch (right_space_td_state) {
        case TD_SINGLE_TAP:
            break;
        case TD_SINGLE_HOLD:
            layer_off(_RAISE);
            break;
        case TD_DOUBLE_TAP:
            break;
        case TD_DOUBLE_HOLD:
            layer_off(_LOWER);
            break;
        case TD_TRIPLE_TAP:
            break;
        case TD_TRIPLE_HOLD:
            // do nothing
            break;
        default:
            break;
    }
}

static enum tap_dance_state left_space_td_state;

void td_left_space_finished(tap_dance_state_t *state, void *user_data) {
    left_space_td_state = calc_state(state);
    switch (left_space_td_state) {
        case TD_SINGLE_TAP:
            tap_code(KC_SPC);
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_LSFT);
            break;
        case TD_DOUBLE_TAP:
            set_oneshot_layer(_OSL_LSPC, ONESHOT_START);
            break;
        case TD_DOUBLE_HOLD:
            layer_on(_LOWER);
            break;
        case TD_TRIPLE_TAP:
            break;
        case TD_TRIPLE_HOLD:
            break;
        default:
            break;
    }
}

void td_left_space_reset(tap_dance_state_t *state, void *user_data) {
    switch (left_space_td_state) {
        case TD_SINGLE_TAP:
            break;
        case TD_SINGLE_HOLD:
            unregister_code(KC_LSFT);
            break;
        case TD_DOUBLE_TAP:
            clear_oneshot_layer_state(ONESHOT_PRESSED);
            break;
        case TD_DOUBLE_HOLD:
            layer_off(_LOWER);
            break;
        case TD_TRIPLE_TAP:
            break;
        case TD_TRIPLE_HOLD:
            break;
        default:
            break;
    }
}

static enum tap_dance_state lgui_td_state;

void td_lgui_finished(tap_dance_state_t *state, void *user_data) {
    lgui_td_state = calc_state(state);
    switch (lgui_td_state) {
        case TD_SINGLE_TAP:
            tap_code(KC_LGUI);
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_LGUI);
            break;
        case TD_DOUBLE_TAP:
            tap_code(KC_LGUI);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_LGUI);
            layer_on(_NUM);
            break;
        case TD_TRIPLE_TAP:
            tap_code(KC_LGUI);
            break;
        case TD_TRIPLE_HOLD:
            register_code(KC_LGUI);
            layer_on(_TD_FN);
            break;
        default:
            break;
    }
}

void td_lgui_reset(tap_dance_state_t *state, void *user_data) {
    switch (lgui_td_state) {
        case TD_SINGLE_TAP:
            break;
        case TD_SINGLE_HOLD:
            unregister_code(KC_LGUI);
            break;
        case TD_DOUBLE_TAP:
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_LGUI);
            layer_off(_NUM);
            break;
        case TD_TRIPLE_TAP:
            break;
        case TD_TRIPLE_HOLD:
            unregister_code(KC_LGUI);
            layer_off(_TD_FN);
            break;
        default:
            break;
    }
}

// clang-format off
tap_dance_action_t tap_dance_actions[] = {
    [TD_ALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_alt_finished, td_alt_reset),
    [TD_CTRL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_ctrl_finished, td_ctrl_reset),
    [TD_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_caps_finished, td_caps_reset),
    [TD_RCTRL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_rctrl_finished, td_rctrl_reset),
    [TD_SHIFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_shift_finished, td_shift_reset),
    [TD_RIGHT_SPACE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_right_space_finished, td_right_space_reset),
    [TD_LEFT_SPACE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_left_space_finished, td_left_space_reset),
    [TD_LGUI] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_lgui_finished, td_lgui_reset),
};
// clang-format on

// const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//     [0] = LAYOUT_tkl_ansi(
//         KC_ESC,  KC_Q,    KC_W,      KC_E,    KC_R,    KC_T,     KC_Y,    KC_U,    KC_I,    KC_O,     KC_P,     KC_BSPC,
//         KC_TAB,  KC_A,    KC_S,      KC_D,    KC_F,    KC_G,     KC_H,    KC_J,    KC_K,    KC_L,               KC_ENT,
//         KC_LSFT, KC_SLSH, KC_Z,      KC_X,    KC_C,    KC_V,     KC_B,    KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_RSFT,
//         KC_LCTL, KC_LGUI, KC_LALT,                     KC_SPC,   MO(2),   KC_SPC,           KC_RALT,  KC_APP,   KC_RCTL
//     ),
//     [1] = LAYOUT_tkl_ansi(
//         KC_TAB,  KC_Q,    KC_W,      KC_E,    KC_R,    KC_T,     KC_Y,    KC_U,    KC_I,    KC_O,     KC_P,     KC_BSPC,
//         KC_CAPS, KC_A,    KC_S,      KC_D,    KC_F,    KC_G,     KC_H,    KC_J,    KC_K,    KC_L,               KC_ENT,
//         KC_LSFT, KC_SLSH, KC_Z,      KC_X,    KC_C,    KC_V,     KC_B,    KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_RSFT,
//         KC_LCTL, KC_LALT, KC_LGUI,                     KC_SPC,   MO(3),   KC_SPC,           KC_RGUI,  KC_APP,   KC_RCTL
//     ),
//     [2] = LAYOUT_tkl_ansi(
//         KC_ESC,   KC_1,    KC_2,     KC_3,    KC_4,    KC_5,     KC_6,    KC_7,    KC_8,    KC_9,     KC_0,     KC_BSLS,
//         KC_CAPS,  MD_BLE1, MD_BLE2,  MD_BLE3, MD_24G,  MD_USB,   RM_VALU, RM_SATD, KC_MINS, KC_EQL,             RM_TOGG,
//         KC_LSFT,  KC_GRV,  RM_NEXT,  RM_SPDD, RM_SPDU, KC_V,     RM_HUED, RM_VALD, RM_HUEU, KC_COMM,  KC_UP,    MW_CH,
//         EE_CLR,   QK_WLO,  KC_LALT,                    QK_BAT,   KC_NO,   KC_SPC,           KC_LEFT,  KC_DOWN,  DBG_SW
//     ),
//     [3] = LAYOUT_tkl_ansi(
//         KC_ESC,   KC_1,    KC_2,     KC_3,    KC_4,    KC_5,     KC_6,    KC_7,    KC_8,    KC_9,     KC_0,     KC_BSLS,
//         KC_CAPS,  MD_BLE1, MD_BLE2,  MD_BLE3, MD_24G,  MD_USB,   RM_VALU, RM_SATD, KC_MINS, KC_EQL,             RM_TOGG,
//         KC_LSFT,  KC_GRV,  RM_NEXT,  RM_SPDD, RM_SPDU, KC_V,     RM_HUED, RM_VALD, RM_HUEU, KC_COMM,  KC_UP,    MW_CH,
//         EE_CLR,   KC_LALT, KC_LGUI,                    QK_BAT,   KC_NO,   KC_SPC,           KC_LEFT,  KC_DOWN,  DBG_SW
//     )
// };

// Stub for dynamic_keymap_get_keycode when DYNAMIC_KEYMAP_ENABLE is disabled
// This is called during wake-from-sleep in USB mode to replay the wake key
// Returning KC_ESC means any key will wake as ESC
uint16_t dynamic_keymap_get_keycode(uint8_t layer, uint8_t row, uint8_t column) {
    return KC_ESC;
}
