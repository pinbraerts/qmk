#include <avr/pgmspace.h>
#include <stdbool.h>
#include ".build/obj_sofle_rev1/src/default_keyboard.h"
#include "action_util.h"
#include "modifiers.h"
#include "quantum.h"

enum sofle_layers {
    vim,
    game,
    options,
    function,
};

static bool left_pressed = 0, right_pressed = 0;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.key.row < 5) {
        left_pressed = record->event.pressed;
    }
    else {
        right_pressed = record->event.pressed;
    }
    return true;
}

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    switch(index) {
    case 0:
        tap_code(clockwise ? KC_AUDIO_VOL_UP : KC_AUDIO_VOL_DOWN);
        break;
    case 1:
        tap_code(clockwise ? KC_BRIGHTNESS_DOWN : KC_BRIGHTNESS_UP);
        break;
    default: return true;
    }
    return false;
}
#endif // ENCODER_ENABLE



#ifdef OS_DETECTION_ENABLE
#include "os_detection.h"
static char const* os_to_string(os_variant_t os) {
    switch (os) {
    case OS_UNSURE:  return PSTR("unsur");
    case OS_LINUX:   return PSTR("\x98\x99\0\xb8\xb9"); // 
    case OS_WINDOWS: return PSTR("\x97\x97\0\xb7\xb7"); // 
    case OS_MACOS:   return PSTR("\x95\x96\0\xb5\xb6"); // 
    default:         return PSTR("unkwn");
    }
}
#endif // OS_DETECTION_ENABLE

enum custom_keys {
    KC_ESCTL = MT(MOD_LCTL, KC_ESC),
    KC_SPSHT = MT(MOD_LSFT, KC_SPACE),
    KC_ENALT = MT(MOD_RALT, KC_ENTER),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[vim] = LAYOUT(
  KC_GRAVE, KC_1,    KC_2,   KC_3,     KC_4,    KC_5,                           KC_6,     KC_7,    KC_8,    KC_9,     KC_0,    KC_BACKSPACE,
  KC_TAB,   KC_Q,    KC_W,   KC_E,     KC_R,    KC_T,                           KC_Y,     KC_U,    KC_I,    KC_O,     KC_P,    KC_BACKSLASH,
  KC_ESC,   KC_A,    KC_S,   KC_D,     KC_F,    KC_G,                           KC_H,     KC_J,    KC_K,    KC_L,     KC_SCLN, KC_QUOTE,
  KC_MINUS, KC_EQL,  KC_Z,   KC_X,     KC_C,    KC_V,     KC_MUTE,    RGB_TOG,  KC_B,     KC_N,    KC_M,    KC_COMM,  KC_DOT,  KC_SLASH,
             TO(function),   KC_LGUI,  KC_LALT, KC_SPSHT, KC_ESCTL,   KC_LBRC,  KC_ENALT, KC_RBRC, KC_RGUI, TO(game)
),

[game] = LAYOUT(
  KC_ESC,   KC_1,    KC_2,   KC_3,     KC_4,    KC_5,                           KC_6,     KC_7,    KC_8,    KC_9,     KC_0,    KC_BACKSPACE,
  KC_TAB,   KC_Q,    KC_W,   KC_E,     KC_R,    KC_T,                           KC_Y,     KC_U,    KC_I,    KC_O,     KC_P,    KC_BACKSLASH,
  KC_LCTL,  KC_A,    KC_S,   KC_D,     KC_F,    KC_G,                           KC_H,     KC_J,    KC_K,    KC_L,     KC_SCLN, KC_QUOTE,
  KC_LSFT,  KC_GRV,  KC_Z,   KC_X,     KC_C,    KC_V,     KC_MUTE,    RGB_TOG,  KC_B,     KC_N,    KC_M,    KC_COMM,  KC_DOT,  KC_SLASH,
                  TO(vim),   KC_LGUI,  KC_LALT, KC_SPSHT, KC_ESCTL,   KC_LBRC,  KC_ENALT, KC_RBRC, KC_RGUI, TO(options)
),

[options] = LAYOUT(
  KC_ESC,   KC_1,    KC_2,   KC_3,     KC_4,    KC_5,                           KC_6,     KC_7,    KC_8,    KC_9,     KC_0,    KC_BACKSPACE,
  KC_TAB,   KC_Q,    KC_W,   KC_E,     KC_R,    KC_T,                           KC_Y,     KC_U,    KC_I,    KC_O,     KC_P,    KC_BACKSLASH,
  KC_LCTL,  KC_A,    KC_S,   KC_D,     KC_F,    KC_G,                           KC_H,     KC_J,    KC_K,    KC_L,     KC_SCLN, KC_QUOTE,
  KC_LSFT,  KC_GRV,  KC_Z,   KC_X,     KC_C,    KC_V,     KC_MUTE,    RGB_TOG,  KC_B,     KC_N,    KC_M,    KC_COMM,  KC_DOT,  KC_SLASH,
                 TO(game),   KC_LGUI,  KC_LALT, KC_SPSHT, KC_ESCTL,   KC_LBRC,  KC_ENALT, KC_RBRC, KC_RGUI, TO(function)
),

[function] = LAYOUT(
  KC_ESC,   KC_F1,   KC_F2,   KC_F3,    KC_F4,   KC_F5,                         KC_F6,    KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_DELETE,
  KC_HOME,  KC_F11,  KC_F12,  KC_F13,   KC_F14,  KC_F15,                        KC_F16,   KC_F17,  KC_F18,  KC_F19,   KC_F20,  KC_BACKSLASH,
  KC_END,   KC_F21,  KC_F22,  KC_F23,   KC_F24,  KC_G,                          KC_LEFT,  KC_DOWN, KC_UP,   KC_RIGHT, KC_SCLN, KC_QUOTE,
  KC_MINUS, KC_EQL,  KC_UNDO, KC_CUT,   KC_COPY, KC_PASTE, KC_MUTE,   RGB_TOG,  KC_B,     KC_PGDN, KC_PGUP, KC_COMM,  KC_DOT,  KC_SLASH,
                 TO(options), KC_LGUI,  KC_LALT, KC_SPSHT, KC_ESCTL,  KC_LBRC,  KC_ENALT, KC_RBRC, KC_RGUI, TO(vim)
),

};

#ifdef OLED_ENABLE
#include "oled_driver.h"

static const char PROGMEM cat[4][128 * 3] = {
    {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64,160, 32, 32, 64,128, 64, 32, 16, 16,  8,  8,  4,  2,  1,  2,  4,  8, 16, 16, 16, 16, 32, 32, 32, 64, 64, 64, 32, 32,144,208, 16,240,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 31, 18, 16, 22, 38, 33, 32, 65, 70, 64,128,134,134,  0,  8, 16, 16,  8, 32, 32, 16,  0, 48, 48,128, 64, 32, 80, 16,144, 32,193,  3, 49,204,  3,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  2,  2,  2,  4,  4,  4,  8,  8,  8, 31, 17, 16, 35, 35, 32, 64, 64, 71,128,129,142,240,  0,  0,
    }, {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64,160, 32, 32, 64,128, 64, 32, 16, 16,  8,  8,  4,  2,  1,  2,  4,  8, 16, 16, 16, 16, 32, 32, 32, 64, 64, 64, 32, 32,144,208, 16,240,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 31, 18, 16, 22, 38, 33, 32, 65, 70, 64,128,134,134,  0,  8, 16, 16,  8, 32, 32, 16,  0, 48, 48,  0,  0,  0,  0,  0,  0,  0,  1,  3, 49,204,  3,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  2,  2,  2,  4,  4,  4,  8,  8,  8, 16, 16, 16, 32, 32, 56,192,  0,  0,  0,  1, 14,240,  0,  0,
    }, {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16, 16,  8,  8,  4,  2,  1,  2,  4,  8, 16, 16, 16, 16, 32, 32, 32, 64, 64, 64, 32, 32,144,208, 16,240,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,224, 24,  4,  2,  2,  1,128, 96, 64,128,134,134,  0,  8, 16, 16,  8, 32, 32, 16,  0, 48, 48,128, 64, 32, 80, 16,144, 32,193,  3, 49,204,  3,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  2,  4,  4,  4,  2,  1,  0,  0,  0,  0,  1,  1,  1,  2,  2,  2,  4,  4,  4,  8,  8,  8, 31, 17, 16, 35, 35, 32, 64, 64, 71,128,129,142,240,  0,  0,
    }, {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16, 16,  8,  8,  4,  2,  1,  2,  4,  8, 16, 16, 16, 16, 32, 32, 32, 64, 64, 64, 32, 32,144,208, 16,240,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,224, 24,  4,  2,  2,  1,128, 96, 64,128,134,134,  0,  8, 16, 16,  8, 32, 32, 16,  0, 48, 48,  0,  0,  0,  0,  0,  0,  0,  1,  3, 49,204,  3,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  2,  4,  4,  4,  2,  1,  0,  0,  0,  0,  1,  1,  1,  2,  2,  2,  4,  4,  4,  8,  8,  8, 16, 16, 16, 32, 32, 56,192,  0,  0,  0,  1, 14,240,  0,  0,
    }
};

static char const* layer_to_string(layer_state_t layer) {
    switch (layer) {
    case vim:      return PSTR("\x9a\x9b\n\xba\xbb");
    case game:     return PSTR("\x9c\x9d\n\xbc\xbd");
    case function: return PSTR("\x9e\x9f\n\xbe\xbb");
    case options:  return PSTR("\x9e\x9f\n\xbe\xbf");
    default:       return PSTR("\nunkwn");
    }
}

static char mod_to_string(enum mods_8bit mod) {
    switch (mod) {
    case MOD_BIT_LCTRL:  return 'C';
    case MOD_BIT_LSHIFT: return 'S';
    case MOD_BIT_LALT:   return 'A';
    case MOD_BIT_LGUI:   return 'G';
    case MOD_BIT_RCTRL:  return 'c';
    case MOD_BIT_RSHIFT: return 's';
    case MOD_BIT_RALT:   return 'a';
    case MOD_BIT_RGUI:   return 'g';
    default:             return ' ';
    }
}

static void print_status_narrow(void) {
    const char* os = os_to_string(detected_host_os());
    static char const* const PROGMEM sm = "\xa0\xa1\0\xc0\xc1";
    oled_write_ln_P(os, false);
    oled_write_char(' ', false);
    oled_write_ln_P(sm, false);
    oled_write_char('\n', false);
    oled_write_ln_P(os + 3, false);
    oled_write_char(' ', false);
    oled_write_ln_P(sm + 3, false);
    oled_write_char('\n', false);
    //oled_write_ln_P(layer_to_string(get_highest_layer(default_layer_state)), false);
    oled_write_ln_P(layer_to_string(get_highest_layer(layer_state)), false);
    oled_write_char(':', false);
    oled_write_char(mod_to_string(get_mods() & MOD_MASK_SHIFT), false);
    oled_write_char(mod_to_string(get_mods() & MOD_MASK_CTRL), false);
    oled_write_char(mod_to_string(get_mods() & MOD_MASK_ALT), false);
    oled_write_char(mod_to_string(get_mods() & MOD_MASK_GUI), false);
    oled_write_ln_P(PSTR(""), false);
    oled_write_char(left_pressed ? 'L' : ' ', false);
    oled_write_char(' ', false);
    oled_write_char(right_pressed ? 'R' : ' ', false);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        oled_write_raw_P(cat[(left_pressed << 1) & right_pressed], sizeof(cat[0][0]));
    }
    return false;
}

#endif // OLED_ENABLE

#if RGBLIGHT_ENABLE
#include "rgblight.h"
#include "color.h"

#define INDICATOR_BRIGHTNESS 30

#define HSV_OVERRIDE_HELP(h, s, v, Override) h, s , Override
#define HSV_OVERRIDE(hsv, Override) HSV_OVERRIDE_HELP(hsv,Override)

// Light combinations
#define SET_INDICATORS(hsv) \
	{0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
    {35+0, 1, hsv}
#define SET_UNDERGLOW(hsv) \
	{1, 6, hsv}, \
    {35+1, 6,hsv}
#define SET_NUMPAD(hsv)     \
	{35+15, 5, hsv},\
	  {35+22, 3, hsv},\
	  {35+27, 3, hsv}
#define SET_NUMROW(hsv) \
	{10, 2, hsv}, \
		{20, 2, hsv}, \
		{30, 2, hsv}, \
	  {35+ 10, 2, hsv}, \
	  {35+ 20, 2, hsv}, \
	  {35+ 30, 2, hsv}
#define SET_INNER_COL(hsv)	\
	{33, 4, hsv}, \
	  {35+ 33, 4, hsv}

#define SET_OUTER_COL(hsv) \
	{7, 4, hsv}, \
	  {35+ 7, 4, hsv}
#define SET_THUMB_CLUSTER(hsv) 	\
	{25, 2, hsv}, \
	  {35+ 25, 2, hsv}
#define SET_LAYER_ID(hsv) 	\
	{0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
    {35+0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
		{1, 6, hsv}, \
    {35+1, 6, hsv}, \
		{7, 4, hsv}, \
	  {35+ 7, 4, hsv}, \
		{25, 2, hsv}, \
	  {35+ 25, 2, hsv}

const rgblight_segment_t PROGMEM layer_vim[] = RGBLIGHT_LAYER_SEGMENTS(
    SET_LAYER_ID(HSV_BLUE)
);

const rgblight_segment_t PROGMEM layer_game[] = RGBLIGHT_LAYER_SEGMENTS(
    SET_LAYER_ID(HSV_RED)
);

const rgblight_segment_t PROGMEM layer_function[] = RGBLIGHT_LAYER_SEGMENTS(
    SET_LAYER_ID(HSV_GREEN)
);

const rgblight_segment_t PROGMEM layer_option[] = RGBLIGHT_LAYER_SEGMENTS(
    SET_LAYER_ID(HSV_PINK)
);

rgblight_segment_t const* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    layer_vim,
    layer_game,
    layer_option,
    layer_function
);

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(vim, layer_state_cmp(state, vim));
    rgblight_set_layer_state(game, layer_state_cmp(state, game));
    rgblight_set_layer_state(options, layer_state_cmp(state, options));
    rgblight_set_layer_state(function, layer_state_cmp(state, function));
    return state;
}

void keyboard_post_init_user() {
    rgblight_layers = my_rgb_layers;
    rgblight_mode(10);
}

#endif // RGBLIGHT_ENABLE

