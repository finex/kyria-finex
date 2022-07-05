/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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

// Layers
enum layers {
    _QWERTY = 0,
    _COLEMAK_DH,
    _NAVIGATION,
    _SYMBOL,
    _NUMBER,
    _FUNCTION,
    _ADJUST
};

/*
 * Custom keycodes
 */

// Base layout (qwerty / colemak)
// Note: temporary switch that only persists until the keyboard loses power.
#define QWERTY  DF(_QWERTY)
#define COLEMAK DF(_COLEMAK_DH)

// Custom keycodes
enum custom_keycodes {
  COLEMAKDH = SAFE_RANGE,
  ASC_SAR,
  ASC_DAR,
  ASC_SQT,
  ASC_DQT,
  ASC_CIRC,
  ASC_TILD,
  ASC_HAP,
  ASC_SAD,
  ASC_BKT,
  ASC_CBRL,
  ASC_CBRR,
  ASC_LAN,
  ASC_RAN
};

// Tap dance codes
enum tap_dance_codes {
  DANCE_2, // Semicolon (single), Colon (double)
  DANCE_3, // Left Bracket (single), Left Brace (double)
  DANCE_4  // Right Bracket (single), Left Brace (double)
};

// Shortcuts to make keymap more readable
// - Adjustment Layer:
#define KC_ADEN LT(_ADJUST, KC_END)   // End / _ADJUST layer
#define KC_ADPU LT(_ADJUST, KC_PGUP)  // Page Up / _ADJUST layer
// - Home row modifiers:
#define KC_GU_A LGUI_T(KC_A)          // A / Left Gui
#define KC_CT_S LCTL_T(KC_S)          // R / Left Ctrl
#define KC_AL_R LALT_T(KC_R)          // S / Left Alt
#define KC_GU_O RGUI_T(KC_O)          // O / Right Gui
#define KC_AR_X RALT_T(KC_X)          // X / Right Alt
#define KC_AL_I LALT_T(KC_I)          // E / Left Alt (left alt because used as Emacs M- )
#define KC_AR_DO RALT_T(KC_DOT)       // . / Right Alt
#define KC_CT_E RCTL_T(KC_E)          // I / Right Ctrl
#define KC_RS_N RSFT_T(KC_N)          // N / Right Shift
#define KC_LS_T LSFT_T(KC_T)          // T / Left Shift
// - Other keys/modifiers:
#define KC_ATAB RALT_T(KC_TAB)        // Tab / Alt Gr
#define KC_CESC LCTL_T(KC_ESC)        // Esc / Left Ctrl
#define KC_GUSP RGUI_T(KC_SPC)        // Space / Right Gui
#define KC_AEQL LALT_T(KC_EQL)        // Equals / Left Alt
#define KC_CMIN RCTL_T(KC_MINUS)      // Minus / Right Ctrl
#define KC_NUES LT(_NUMB, KC_ESC)     // Esc / _numbers
#define KC_CBSP LCTL_T(KC_BSPC)        // Backspace / Left Ctrl
#define KC_SYSP LT(_SYMB, KC_SPC)     // Space / _symbols
/* #define KC_AWEN LT(_AWES, KC_ENT)     // Enter / AwesomeWM */
#define KC_FUTA LT(_FUNC, KC_TAB)     // Tab / _functions
#define KC_RAEN RALT_T(KC_ENT)        // Enter / Right Alt

#define KC_GUDE RGUI_T(KC_DEL)        // Delete / Right Gui
#define KC_SYBS LT(_SYMB, KC_BSPC)    // Backspace / _symbols
#define KC_FUDE LT(_FUNC, KC_DEL)     // Delete / _functions
#define KC_NUEN LT(_NUMB, KC_ENT)     // Enter / _numbers
#define KC_NAES LT(_NAVI, KC_ESC)     // Esc / _navi

#define KC_HYBS HYPR_T(KC_BSPC)        // Backspace / Hyper
#define KC_MEEN MEH_T(KC_ENT)          // Enter / Meh

// - Toggle layers:
#define TG_NUM TG(_NUMB)
#define TG_NAV TG(_NAVI)

// - Tap dance keys:
#define TD_DGUM TD(DANCE_1)
#define TD_SCLN TD(DANCE_2)
#define TD_LBRC TD(DANCE_3)
#define TD_RBRC TD(DANCE_4)
// - Awesome WM macros:
#define KC_AW1 LGUI(KC_1)
#define KC_AW2 LGUI(KC_2)
#define KC_AW3 LGUI(KC_3)
#define KC_AW4 LGUI(KC_4)
#define KC_AW5 LGUI(KC_5)
#define KC_AW6 LGUI(KC_6)
#define KC_AW7 LGUI(KC_7)
#define KC_AW8 LGUI(KC_8)
#define KC_AW9 LGUI(KC_9)
// - Clipboard, Undo/Redo and "select all"
#define U_PST S(KC_INS)
#define U_CPY C(KC_INS)
#define U_CUT S(KC_DEL)
#define U_UND KC_UNDO
#define U_RDO KC_AGIN
#define U_ALL C(KC_A) // Emacs need to rebind mark-whole-buffer to: C-a

// Send custom strings or change default base layer
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch(keycode) {
      case ASC_SAR:
        SEND_STRING("->");
        return false;
      case ASC_DAR:
        SEND_STRING("=>");
        return false;
      case ASC_SQT:
        // SS_RALT(): Avoid sending dead key on software intl layouts
        SEND_STRING(SS_RALT("'"));
        return false;
      case ASC_DQT:
        // SS_RALT(SS_LSFT()): Avoid sending dead key on software intl layouts
        SEND_STRING(SS_RALT(SS_LSFT("\"")));
        return false;
      case ASC_CIRC:
        // SS_RALT(): Avoid sending dead key on software intl layouts
        SEND_STRING(SS_RALT("^"));
        return false;
      case ASC_TILD:
        // SS_RALT(SS_LSFT()): Avoid sending dead key on software intl layouts
        SEND_STRING(SS_RALT(SS_LSFT("~")));
        return false;
      case ASC_HAP:
        SEND_STRING(":-) ");
        return false;
      case ASC_SAD:
        SEND_STRING(":-( ");
        return false;
      case ASC_BKT:
        // SS_RALT(): Avoid sending dead key on software intl layouts
        SEND_STRING(SS_RALT("`"));
        return false;
      case ASC_CBRL:
        SEND_STRING("{");
        return false;
      case ASC_CBRR:
        SEND_STRING("}");
        return false;
      case ASC_LAN:
        SEND_STRING(SS_RALT("["));
        return false;
      case ASC_RAN:
        SEND_STRING(SS_RALT("]"));
        return false;
      case COLEMAKDH:
        if (record->event.pressed) {
          set_single_persistent_default_layer(_COLEMAKDH);
        }
        return false;
        break;
    }
  }
  return true;
};

// Fine tuning of TAPPING_TERM valuer on some home row modifiers to avoid errors during typing.
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

  // Ring fingers
  case KC_AL_I:
  case KC_AL_R:
    return TAPPING_TERM + 200;

  // Pinkies
  case KC_GU_O:
  case KC_GU_A:
    return TAPPING_TERM + 50;

  // Middle fingers
  case KC_CT_S:
  case KC_CT_E:
    return TAPPING_TERM - 30;

  // Right thumb for "symbols" layer
  case KC_SYSP:
    return TAPPING_TERM - 50;

  // Left thumb for delete/gui/mouse combo
  case KC_GUDE:
    return TAPPING_TERM - 20;

  // All other keys
  default:
    return TAPPING_TERM;
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * Base Layer: QWERTY
 */
    [_QWERTY] = LAYOUT(
     TG_BUTT , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    ,                                            KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , TG_NUM  ,
     KC_GRV  , QHGA    , QHAS    , QHCD    , QHSF    , KC_G    ,                                            KC_H    , QHSJ    , QHCK    , QHAL    , QHGSCLN , KC_QUOT ,
     KC_LSPO , KC_Z    , QHLX    , KC_C    , KC_V    , KC_B    , LT_ADPD , KC_PGUP ,    KC_HOME , LT_ADEN , KC_N    , KC_M    , KC_COMM , QHLD    , KC_SLSH , KC_RSPC ,
                                   HYP_PRS , KC_ENT  , MT_CTES , LT_NASP , LT_MOTA ,    LT_SYEN , LT_NUBS , LT_FUDE , KC_SPC  , KC_MEH
    ),

/*
 * Alternative Layer: Colemak DH
 */
    [_COLEMAK_DH] = LAYOUT(
     KC_TAB , KC_Q    , KC_W    , KC_F    , KC_P    , KC_B    ,                                            KC_J    , KC_L    , KC_U    , KC_Y    , KC_SCLN , KC_EQL  ,
     KC_ESC  , KC_GU_A ,KC_AL_R ,KC_CT_S ,KC_LS_T    , KC_G    ,                                            KC_M    ,KC_RS_N ,KC_CT_E ,KC_AL_I ,KC_GU_O    , KC_MINS ,
     KC_LSPO , KC_Z    , KC_AR_X    , KC_C    , KC_D    , KC_V    , KC_ADPU ,KC_PGDN ,    KC_HOME ,KC_ADEN , KC_K    ,KC_H    ,KC_COMM ,KC_AR_DO,KC_SLSH , KC_RSPC ,
                                   KC_HYBS ,KC_MEEN ,     KC_NAES ,    KC_CBSP ,KC_GUDE ,    KC_NUEN ,KC_SYSP ,    KC_FUTA , TG_NAV  ,TG_NUM
    ),


/*
 * Navigation
 */
    [_NAVIGATION] = LAYOUT(
       _______, KC_PGUP ,KC_UP   ,KC_PGDN ,KC_HOME, _______,                                     U_UND   ,U_CUT   ,U_CPY   ,U_PST   ,U_RDO  , _______,
       _______, KC_LEFT ,KC_DOWN ,KC_RGHT ,KC_END, _______,                                     _______, KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT, _______,
       _______, _UND   ,U_CUT   ,U_CPY   ,U_PST   ,U_RDO, _______, _______, _______, _______, _______, KC_HOME ,KC_PGDN ,KC_PGUP ,KC_END , _______,
                                  _______, _______, _______, _______, _______, KC_ENT , KC_BSPC, KC_DEL , _______, _______
    ),


/*
 * Symbols
 */
    [_SYMBOL] = LAYOUT(
       _______, KC_RBRC ,KC_AT   ,KC_HASH ,KC_DLR  ,KC_PERC,                                     _______, _______, _______, _______, _______, _______,
       _______, KC_PIPE ,KC_PMNS ,ASC_SQT ,ASC_DQT ,KC_AMPR,                                     _______, _______, _______, _______, _______, _______,
       _______, KC_BSLS ,KC_UNDS ,ASC_CIRC,ASC_TILD,KC_EXLM, ASC_SAD ,ASC_HAP, _______, _______, _______, _______, _______, _______, _______, _______,
                                  _______, _______, KC_LPRN, KC_GRV  ,KC_QUOT, _______, _______, _______, _______, _______
    ),

/*
 * Numbers
 */
    [_NUMBER] = LAYOUT(
       _______, KC_LBRC ,KC_9    ,KC_8    ,KC_9    ,KC_PPLS,                                     _______, KC_AW7  ,KC_AW8  ,KC_AW9, _______, _______,
       _______, KC_PMNS ,KC_4    ,KC_5    ,KC_6    ,KC_PAST ,                                     _______, KC_AW4  ,KC_AW5  ,KC_AW6, _______, _______,
       _______, KC_PSLS ,KC_1    ,KC_2    ,KC_3    ,KC_EQL, _______, _______, _______, _______, _______, KC_AW1  ,KC_AW2  ,KC_AW3, _______, _______,
                                  KC_DOT  ,KC_0    ,     KC_COMM ,    _______ ,KC_ENT, _______, _______, _______, _______, _______
    ),

/*
 * Functions
 */
    [_FUNCTION] = LAYOUT(
       _______, KC_F12  ,KC_F7   ,KC_F8   ,KC_F9   ,KC_CAPS,                                     _______, _______, _______, _______, _______, _______,
       _______, KC_F11  ,KC_F4   ,KC_F5   ,KC_F6   ,KC_NLCK,                                     _______, _______, _______, _______, _______, _______,
       _______, KC_F10  ,KC_F1   ,KC_F2   ,KC_F3   ,KC_INS , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                  _______, _______, KC_APP , KC_SPC , KC_TAB , _______, _______, _______, _______, _______
    ),


/*
 * Adjust Layer: Default layer settings, RGB
 */
    [_ADJUST] = LAYOUT(
      XXXXXXX, QWERTY , COLEMAK, XXXXXXX, XXXXXXX, XXXXXXX,                                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                    RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_SAD, RGB_HUD, RGB_VAD,RGB_RMOD, XXXXXXX,
                                 XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),

// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};



//extern bool g_suspend_state;
//#define GET_TAP_KC(dual_role_key) dual_role_key & 0xFF
//uint16_t last_keycode = KC_NO;
//uint8_t last_modifier = 0;

// Define "tap" structure
typedef struct {
    bool is_press_action;
    uint8_t step;
} tap;

// Tap combinations
enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP,
    MORE_TAPS
};

static tap dance_state = {
    .is_press_action = true,
    .step = 0
};

/* void on_dance_1(qk_tap_dance_state_t *state, void *user_data); */
/* uint8_t dance_1_dance_step(qk_tap_dance_state_t *state); */
/* void dance_1_finished(qk_tap_dance_state_t *state, void *user_data); */
/* void dance_1_reset(qk_tap_dance_state_t *state, void *user_data); */

// Dance 2: Semicolon to Colon
void dance_2_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_SCLN);
  } else {
    register_code (KC_RSFT);
    register_code (KC_SCLN);
  }
}
void dance_2_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_SCLN);
  } else {
    unregister_code (KC_RSFT);
    unregister_code (KC_SCLN);
  }
}

// Dance 3: Square braket to curly bracket (left)
void dance_3_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_LBRC);
  } else {
    register_code (KC_RSFT);
    register_code (KC_LBRC);
  }
}
void dance_3_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_LBRC);
  } else {
    unregister_code (KC_RSFT);
    unregister_code (KC_LBRC);
  }
}

// Dance 4: Square braket to curly bracket (right)
void dance_4_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_RBRC);
  } else {
    register_code (KC_RSFT);
    register_code (KC_RBRC);
  }
}
void dance_4_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_RBRC);
  } else {
    unregister_code (KC_RSFT);
    unregister_code (KC_RBRC);
  }
}

// Match tap dance actions with the corresponding index
qk_tap_dance_action_t tap_dance_actions[] = {
  [DANCE_2] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_2_finished, dance_2_reset),
  [DANCE_3] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_3_finished, dance_3_reset),
  [DANCE_4] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_4_finished, dance_4_reset)
};

// Enable tapping_force_hold only for home row mods
bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case KC_LS_T:
  case KC_CT_S:
  case KC_AL_R:
  case KC_GU_A:
  case KC_RS_N:
  case KC_CT_E:
  case KC_AL_I:
  case KC_GU_O:
    return true;
  default:
    return false;
  }
}






/* The default OLED and rotary encoder code can be found at the bottom of qmk_firmware/keyboards/splitkb/kyria/rev1/rev1.c
 * These default settings can be overriden by your own settings in your keymap.c
 * For your convenience, here's a copy of those settings so that you can uncomment them if you wish to apply your own modifications.
 * DO NOT edit the rev1.c file; instead override the weakly defined default functions by your own.
 */

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

void oled_task_user(void) {
    if (is_keyboard_master()) {
        // QMK Logo and version information
        // clang-format off
        static const char PROGMEM qmk_logo[] = {
            0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
            0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
            0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
        // clang-format on

        oled_write_P(qmk_logo, false);
        oled_write_P(PSTR("Kyria rev1.0\n\n"), false);

        // Host Keyboard Layer Status
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state|default_layer_state)) {
            case _QWERTY:
                oled_write_P(PSTR("QWERTY\n"), false);
                break;
            case _COLEMAK_DH:
                oled_write_P(PSTR("Colemak-DH\n"), false);
                break;
            /* case _MEDIA: */
            /*     oled_write_P(PSTR("Media\n"), false); */
            /*     break; */
            case _NAVIGATION:
                oled_write_P(PSTR("Nav\n"), false);
                break;
            case _MOUSE:
                oled_write_P(PSTR("Mouse\n"), false);
                break;
            case _SYMBOL:
                oled_write_P(PSTR("Sym\n"), false);
                break;
            case _NUMBER:
                oled_write_P(PSTR("Number\n"), false);
                break;
            case _FUNCTION:
                oled_write_P(PSTR("Function\n"), false);
                break;
            case _BUTTON:
                oled_write_P(PSTR("Button\n"), false);
                break;
            case _ADJUST:
                oled_write_P(PSTR("Adjust\n"), false);
                break;
            default:
                oled_write_P(PSTR("Undefined\n"), false);
        }

        // Write host Keyboard LED Status to OLEDs
        led_t led_usb_state = host_keyboard_led_state();
        oled_write_P(led_usb_state.num_lock    ? PSTR("NUMLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.caps_lock   ? PSTR("CAPLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);
    } else {
        // clang-format off
        static const char PROGMEM kyria_logo[] = {
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
            0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
            0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
        };
        // clang-format on
        oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
    }
}
#endif

 /*
#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {

    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return false;
}
#endif
DELETE THIS LINE TO UNCOMMENT (2/2) */
