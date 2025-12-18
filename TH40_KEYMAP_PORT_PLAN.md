# Plan: Port lily58:shasderias Keymap to epomaker/th40:shasderias

## Overview
Port all 7 layers and advanced features from lily58:shasderias (58 keys) to epomaker/th40:shasderias (44 keys), adding a new wireless control layer for TH40-specific functionality.

## Physical Constraints
- **lily58**: 58 keys (split, 6×4 + 4 thumb keys per side)
- **TH40**: 44 keys (single PCB, standard 40% layout)
  - Row 0: 1 key (Tab 1.5u)
  - Row 1: 11 keys (Q-P, Backspace 1.5u)
  - Row 2: 10 keys (Caps 1.75u, A-semicolon, Enter 2.25u)
  - Row 3: 12 keys (Shift 1.25u, slash-M, right shift 1.75u)
  - Row 4: 9 keys (bottom mods with split space bars)

## Layer Structure (8 Total)

```
Layer 0: _QWERTY    - Base typing layer
Layer 1: _GAME      - Gaming mode (leader-toggled)
Layer 2: _LOWER     - Symbols, brackets, numbers
Layer 3: _RAISE     - Navigation (arrows, home/end, pgup/pgdn)
Layer 4: _FUNC      - Function keys F1-F12
Layer 5: _NUMBER    - Numpad layout
Layer 6: _CAPS      - Caps word helper (auto-activated)
Layer 7: _WIRELESS  - NEW: Wireless/system controls for TH40
```

## Features to Port (All Portable)

### Direct Ports (No Changes Required)
1. **Tap Dance** (3 implementations):
   - TD_ALT: single tap/hold (alt), double tap/hold (FUNC+alt)
   - TD_CTRL: single tap/hold (ctrl), double tap/hold (FUNC+ctrl)
   - TD_CAPS: single tap activates caps word
2. **Leader Key** (4 sequences):
   - Leader+Q: disable game layer (gold flash)
   - Leader+G: enable game layer (blue flash)
   - Leader+P: paste (Shift+Insert)
   - Leader+ESC+BSP: bootloader
3. **Custom Keycode**: KC_CCCV (tap=paste, hold=copy)
4. **Caps Word**: activates _CAPS layer automatically

### Requires Adaptation
1. **RGB Feedback**: Convert from `rgblight_*` (underglow) to `rgb_matrix_*` (per-key)
   - Purple on leader start
   - Gold/blue on game mode toggle
   - Black on idle
2. **Process Record**: Chain with `kb_process_record_common()` for TH40 wireless integration

## Key Layer Access Scheme

### Bottom Row Positions
```
[4,0]: CK_TDCO (tap dance CTRL)
[4,2]: KC_LGUI
[4,3]: CK_TDAO (tap dance ALT)
[4,4]: CK_LOEN = LT(_LOWER, KC_SPC)
[4,6]: MO(_WIRELESS)
[4,7]: CK_RAEN = LT(_RAISE, KC_SPC)
[4,8]: KC_DEL
[4,9]: CK_MOFN = MO(_FUNC)
[4,10]: CK_TDCA (tap dance CAPS)
```

### Additional Access
- _NUMBER: via MO(_NUMBER) on _FUNC layer at [3,8]
- _GAME: toggled via leader sequences (Leader+G/Q)
- _CAPS: auto-activated by caps_word_set_user()

### Special Positions
- [3,11]: QK_LEAD (leader key, replaces right shift)
- [2,0]: KC_ESC (moved from number row for better ergonomics)

## Layer 7: _WIRELESS (New)

Purpose: TH40-specific wireless and system controls

**Key Features**:
- Number row (1-0) for quick number access
- Wireless mode selection: MD_BLE1, MD_BLE2, MD_BLE3, MD_24G, MD_USB
- RGB matrix controls: RM_TOGG, RM_NEXT, RM_SPDU, RM_SPDD, RM_HUED, RM_HUEU, RM_VALU, RM_VALD, RM_SATD
- System functions: QK_BAT (battery), EE_CLR, QK_WLO (Win lock), DBG_SW, MW_CH (Mac/Win)
- Relocated symbols: KC_GRV, KC_BSLS, KC_SCLN, KC_QUOT

**Wireless Keycodes** (defined in rdmctmzt_common.h):
```c
MD_BLE1  = QMK_KB_MODE_BLE1  // Bluetooth channel 1
MD_BLE2  = QMK_KB_MODE_BLE2  // Bluetooth channel 2
MD_BLE3  = QMK_KB_MODE_BLE3  // Bluetooth channel 3
MD_24G   = QMK_KB_MODE_2P4G  // 2.4GHz wireless
MD_USB   = QMK_KB_MODE_USB   // USB mode
QK_BAT   = QMK_BATT_NUM      // Battery status display
QK_WLO   = QMK_WIN_LOCK      // Windows key lock
DBG_SW   = QMK_DEBUG_SWITCH  // Debug mode
MW_CH    = QMK_MAC_WIN_CH    // Mac/Windows switch
```

## Implementation Changes

### File 1: keymap.c
**Path**: `/home/shasderias/dev/qmk_firmware/keyboards/epomaker/th40/keymaps/shasderias/keymap.c`

**Changes**:
1. Add includes:
   ```c
   #include QMK_KEYBOARD_H
   #include "rdmctmzt_common.h"
   #include "print.h"
   ```

2. Copy from lily58:
   - Layer enum (update to 8 layers)
   - Tap dance enums and state tracking
   - Custom keycode enum (KC_CCCV)
   - Layer-tap and mod-tap defines

3. Define all 8 keymaps for 44-key LAYOUT_tkl_ansi

4. Copy functions from lily58, adapt RGB calls:
   - `led_off_callback()` - use `rgb_matrix_sethsv_noeeprom()`
   - `td_alt_finished()`, `td_alt_reset()`
   - `td_ctrl_finished()`, `td_ctrl_reset()`
   - `td_caps_finished()`, `td_caps_reset()`
   - `calc_state()` - no changes
   - `tap_dance_actions[]` - no changes
   - `leader_start_user()` - use `rgb_matrix_sethsv_noeeprom()`
   - `leader_end_user()` - use `rgb_matrix_sethsv_noeeprom()`
   - `caps_word_set_user()` - no changes

5. Update `process_record_user()` to chain with TH40 common:
   ```c
   bool process_record_user(uint16_t keycode, keyrecord_t *record) {
       // Handle TH40 wireless keycodes first
       if (!kb_process_record_common(keycode, record)) {
           return false;
       }

       // Handle custom keycodes
       switch (keycode) {
           case KC_CCCV:
               // [existing lily58 implementation]
               break;
       }
       return true;
   }
   ```

6. Update `keyboard_post_init_user()`:
   ```c
   void keyboard_post_init_user(void) {
       kb_keyboard_post_init(); // TH40 common init
       rgb_matrix_enable_noeeprom();
       rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
       rgb_matrix_sethsv_noeeprom(HSV_BLACK);
   }
   ```

### File 2: config.h
**Path**: `/home/shasderias/dev/qmk_firmware/keyboards/epomaker/th40/keymaps/shasderias/config.h`

**Changes** (append to existing):
```c
// Tap dance and layer-tap settings (from lily58)
#define QUICK_TAP_TERM 0
#undef TAPPING_TERM
#define TAPPING_TERM 200
#define PERMISSIVE_HOLD
#define HOLD_ON_OTHER_KEY_PRESS

// Leader key settings
#define LEADER_TIMEOUT 300
#define LEADER_PER_KEY_TIMING

// RGB Matrix - don't timeout, manual control
#define RGB_MATRIX_TIMEOUT 0
```

Note: Keep existing `DEBOUNCE 7` from current config.

### File 3: rules.mk
**Path**: `/home/shasderias/dev/qmk_firmware/keyboards/epomaker/th40/keymaps/shasderias/rules.mk`

**Changes** (append to existing):
```make
# Features from lily58
LEADER_ENABLE = yes
TAP_DANCE_ENABLE = yes
CAPS_WORD_ENABLE = yes
DEFERRED_EXEC_ENABLE = yes
```

## Trade-offs

### Advantages
- All 7 lily58 layers preserved + 1 new wireless layer
- All advanced features maintained (tap dance, leader, KC_CCCV, caps word)
- Efficient layer access (max 2 actions to reach any layer)
- Dedicated wireless control layer
- Better ESC position (Caps key position)

### Compromises
- Number row requires holding LOWER/RAISE/WIRELESS layer
- Some symbols relocated to layers (KC_BSLS, KC_GRV, KC_SCLN, KC_QUOT)
- Right shift replaced by leader key (shift moved to [3,0])
- Space bars become layer-tap keys (may need adjustment period)
- NUMBER layer requires two hands: hold FUNC + hold MO(_NUMBER)

## Testing Checklist

1. Basic functionality: all base layer keys work
2. Layer access: test all LT and MO keys
3. Tap dance: verify all 3 tap dance behaviors (single/double, tap/hold)
4. Leader sequences: test all 4 combinations
5. KC_CCCV: test tap (paste) and hold (copy) timing
6. Caps word: test activation and _CAPS layer
7. Game mode: test leader toggle and layer overlay
8. Wireless controls: verify TH40-specific keys work
9. RGB feedback: verify leader and game mode colors
10. Process record chaining: ensure wireless keys still work after custom implementation

## RGB API Migration Reference

| lily58 (rgblight) | TH40 (rgb_matrix) |
|-------------------|-------------------|
| `rgblight_enable_noeeprom()` | `rgb_matrix_enable_noeeprom()` |
| `rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT)` | `rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR)` |
| `rgblight_sethsv_noeeprom(HSV_*)` | `rgb_matrix_sethsv_noeeprom(HSV_*)` |

HSV color constants remain the same (HSV_PURPLE, HSV_GOLD, HSV_BLUE, HSV_BLACK).

## Critical Files

1. **keymap.c** - Primary implementation (all 8 layers, tap dance, leader, custom features)
2. **config.h** - Timing and feature configuration
3. **rules.mk** - Feature enablement flags
4. **lily58/keymaps/shasderias/keymap.c** - Source reference for exact logic to copy
5. **lib/rdmctmzt_common/rdmctmzt_common.h** - Wireless keycode definitions and integration functions
