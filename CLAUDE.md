# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a forked QMK firmware repository focused on two custom keymaps:
- `lily58:shasderias` - Split keyboard with custom layers and tap dance features
- `epomaker/th40:shasderias` - 40% keyboard with wireless support

The fork includes keyboards not officially supported by QMK, particularly Epomaker keyboards with ES32 MCU wireless support.

## Build Commands

### Compiling Firmware

```bash
# Compile lily58 keymap
qmk compile -kb lily58/rev1 -km shasderias

# Compile epomaker th40 keymap
qmk compile -kb epomaker/th40 -km shasderias

# Clean build
qmk compile -kb <keyboard> -km shasderias --clean

# Generate compile_commands.json for IDE support
qmk compile -kb <keyboard> -km shasderias --compiledb
```

### Flashing Firmware

```bash
# Flash lily58 (drag .uf2 file to mounted drive when in bootloader mode)
qmk flash -kb lily58/rev1 -km shasderias

# Flash epomaker th40 (drag .bin file to mounted drive)
qmk flash -kb epomaker/th40 -km shasderias
```

### Other Useful Commands

```bash
# List all keymaps for a keyboard
qmk list-keymaps -kb lily58

# Get keyboard info
qmk info -kb lily58/rev1

# Lint check
qmk lint -kb lily58/rev1 -km shasderias

# Clean build artifacts
qmk clean
```

## Keymap Architecture

### lily58:shasderias

Located in: `keyboards/lily58/keymaps/shasderias/`

**Key Features:**
- **Tap Dance**: Complex tap/hold behaviors on Alt, Ctrl, and Caps keys
  - Single tap: oneshot layer to base
  - Single hold: modifier key
  - Double tap: oneshot modifier + func layer
  - Double hold: modifier + func layer
- **Custom Keycode**: `KC_CCCV` - tap for paste, hold for copy
- **Leader Key**: Used to switch game layer and trigger bootloader
- **Layers**: QWERTY (base), GAME, LOWER, RAISE, FUNC, NUMBER, CAPS
- **RGB Control**: Uses 2 LEDs per side for visual feedback on layer changes
- **Caps Word**: Activates dedicated CAPS layer with underscore on spacebar

**Hardware Config:**
- RP2040 (KB2040) conversion with custom pin mappings
- EE_HANDS for split side detection
- Tapping term: 200ms with permissive hold
- RGB on pin 17 with custom HSV feedback

### epomaker/th40:shasderias

Located in: `keyboards/epomaker/th40/keymaps/shasderias/`

**Key Features:**
- Uses `rdmctmzt_common` library for wireless functionality (BLE, 2.4GHz, USB)
- Custom keycodes for mode switching: `MD_BLE1`, `MD_BLE2`, `MD_BLE3`, `MD_24G`, `MD_USB`
- Battery status with `QK_BAT` keycode
- 2 layers (base + function layer with connectivity controls)
- Reduced debounce (7ms) and tapping term (130ms) for responsiveness

**Hardware Config:**
- ES32 FS026 MCU (Cortex M0)
- Custom bootloader and SPI drivers
- VIA enabled for dynamic keymap support

## Code Structure

**Keymap Files:**
- `keymap.c` - Layer definitions and custom key behavior
- `config.h` - Hardware and timing configuration
- `rules.mk` - Feature flags and build options

**Important QMK Features Used:**
- `TAP_DANCE_ENABLE` - Multi-function tap/hold keys
- `LEADER_ENABLE` - Leader key sequences
- `CAPS_WORD_ENABLE` - Smart caps lock behavior
- `RGBLIGHT_ENABLE` - LED feedback
- `DEFERRED_EXEC_ENABLE` - Timed callbacks for LED effects
- `VIA_ENABLE` - Runtime keymap configuration (th40 only)

**Wireless Features (th40):**
- Common library at `lib/rdmctmzt_common/` handles BLE/2.4GHz/USB switching
- Custom EEPROM and battery management
- Three-mode wireless stack with mode persistence

## Keymap Development Patterns

1. **Layer Access**: Use `LT()` for layer-tap, `MO()` for momentary layer
2. **Mod-Tap**: `MT(MOD_*, KC_*)` combines modifier when held, key when tapped
3. **Oneshot**: `set_oneshot_layer()` and `set_oneshot_mods()` for sticky behavior
4. **Custom Processing**: Implement `process_record_user()` for key override logic
5. **RGB Feedback**: Use `rgblight_sethsv_noeeprom()` for temporary color changes
6. **Leader Actions**: Define sequences in `leader_end_user()` with `leader_sequence_*_key()`

## Common Modifications

When editing keymaps:
- Update layer enum if adding/removing layers
- Match layer numbers in keymap array with enum values
- For lily58: maintain the 6x4+4 thumb cluster layout format
- For th40: preserve wireless control keys in function layer
- Test tap dance timing adjustments in config.h before changing code
- Use the visual ASCII keymap comments to plan layout changes

## Documentation

Official QMK documentation: https://docs.qmk.fm
