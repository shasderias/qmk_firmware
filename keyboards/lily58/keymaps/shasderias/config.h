/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#define EE_HANDS

#define QUICK_TAP_TERM 0
#define TAPPING_TERM 200
#define PERMISSIVE_HOLD
#define HOLD_ON_OTHER_KEY_PRESS

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET

#undef RGBLED_NUM
#undef WS2812_DI_PIN
#define RGBLED_NUM 2
#define WS2812_DI_PIN 17
#define RGBLED_SPLIT {1, 1}
#define RGBLIGHT_LIMIT_VAL 255
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17
