

#include QMK_KEYBOARD_H

#include <stdio.h>
#ifdef POINTING_DEVICE_ENABLE
    //#include "../../../../drivers/sensors/pimoroni_trackball.h"
    //#include "../../../../drivers/sensors/pointing_device.h"
#endif


enum custom_keycodes {
  BALL_HUI,//cycles hue
  BALL_WHT,//cycles white
  BALL_DEC,//decreased color
  BALL_SCR,//scrolls
  BALL_NCL,//left click
  BALL_RCL,//right click
  BALL_MCL,//middle click
};

enum unicode_names {
    BANG,
    IRONY,
    SNEK
};

const uint32_t PROGMEM unicode_map[] = {
    [BANG]  = 0x203D,  // ‽
    [IRONY] = 0x2E2E,  // ⸮
    [SNEK]  = 0x1F40D, // 🐍
};

extern uint8_t is_master;

enum layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
    _NUMERIC,
    _MOUSE,
};

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


 [_QWERTY] = LAYOUT(
  KC_TAB  ,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,   KC_BSLS,
  KC_LSFT ,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN, KC_RSFT,
  KC_LCTRL,   KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,                    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_LCTRL,

                                            KC_LALT, LOWER , KC_SPC,   KC_ENT,   RAISE,   KC_BSPC
),
[_LOWER] = LAYOUT(
  KC_GRV  ,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   KC_MINS,
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_QUOTE, KC_DOUBLE_QUOTE, KC_UNDS,
  KC_LCTRL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                  KC_EQL, KC_PLUS, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
                                           _______, _______, _______, KC_SPC,  _______, _______
),

[_RAISE] = LAYOUT(
  KC_ESC, XXXXXXX, XXXXXXX, KC_INS, KC_HOME,  KC_PGUP,                        XXXXXXX,  XXXXXXX,    KC_UP, XXXXXXX, XXXXXXX, XXXXXXX,
  KC_LSFT, XXXXXXX, XXXXXXX, KC_DEL, KC_END, KC_PGDN,                       XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT,   XXXXXXX, KC_F12,
  KC_LCTRL, KC_F1, KC_F2, KC_F3,KC_F4, KC_F5,                                KC_F6, KC_F7, KC_F8,  KC_F9, KC_F10, KC_F11,
                                            _______, _______,  _______,   _______,  _______, _______
),
[_ADJUST] = LAYOUT(
KC_PSCREEN, KC_CAPSLOCK, KC_RCTRL, XXXXXXX, KC_BRIGHTNESS_UP, KC__VOLUP,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
KC_LGUI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC__VOLDOWN,                   XXXXXXX, XXXXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI,
TG(_NUMERIC), RESET, XXXXXXX, XXXXXXX, XXXXXXX, KC__MUTE,                   XXXXXXX, XXXXXXX, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD,
                                    TG(_MOUSE), _______, _______, _______,  _______, _______
),

[ _NUMERIC] = LAYOUT(
XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,KC_PGUP ,                   KC_1, KC_2, KC_3, KC_SLSH, KC_ASTR, KC_MINS,
XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,KC_PGDN ,                   KC_4, KC_5, KC_6, KC_BSPC, KC_UP, KC_PLUS,
TG(_NUMERIC), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX ,             KC_7, KC_8, KC_9, KC_LEFT, KC_DOWN, KC_RGHT,
                                    XXXXXXX, _______, _______, _______,  KC_0, KC_DOT
),

[_MOUSE] = LAYOUT(
XXXXXXX, XXXXXXX, XXXXXXX, KC_MS_ACCEL0, KC_MS_ACCEL1,KC_MS_ACCEL2 ,                   XXXXXXX, XXXXXXX, KC_MS_UP, XXXXXXX, XXXXXXX, XXXXXXX,
XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX ,                   XXXXXXX, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, XXXXXXX, XXXXXXX,
TG(_NUMERIC), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX ,             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                    TG(_MOUSE), _______, _______, _______,  XXXXXXX, XXXXXXX
)
};

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
    return state;
}

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    } else {
        return OLED_ROTATION_0;
    }
}


#    define KEYLOG_LEN 12
char     keylog_str[KEYLOG_LEN] = {};
uint8_t  keylogs_str_idx        = 0;
uint16_t log_timer              = 0;

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void add_keylog(uint16_t keycode, keypos_t* keypos ) {
    if(keypos){
        if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
            keycode = keycode & 0xFF;
        }

        /* for (uint8_t i = KEYLOG_LEN - 1; i > 0; i--) { */
        /*     keylog_str[i] = keylog_str[i - 1]; */
        /* } */
        /*if (keycode < 60) { */
        /* keylog_str[0] = code_to_name[keycode]; */
        /* } */

/*         keylog_str[0] = code_to_name[keypos->col + 0x30 ];  */
        /* keylog_str[KEYLOG_LEN - 1] = 0; */
        uint8_t modifiers = get_mods();
        sprintf(keylog_str, "c:%hhu\nr:%hhu\n", keypos->col, keypos->row);
        sprintf(keylog_str + 8, modifiers & MOD_MASK_SHIFT ? "s:1" : "s:0");
        keylog_str[KEYLOG_LEN - 1] = 0;

        log_timer = timer_read();
    }
}

void update_log(void) {
    if (timer_elapsed(log_timer) > 750) {
        add_keylog(0, 0);
    }
}

void render_keylogger_status(void) {

    //oled_write_P(PSTR("KLogr"), false);
    //oled_write(keylog_str, false);
}

void render_wpm(uint8_t padding) {
#ifdef WPM_ENABLE

    /* oled_write_P(PSTR(OLED_RENDER_WPM_COUNTER), false); */
    /* if (padding) { */
    /*     for (uint8_t n = padding; n > 0; n--) { */
    /*         oled_write_P(PSTR(" "), false); */
    /*     } */
    /* } */
    oled_write_ln_P(PSTR("WPM  "), false);
    oled_write_P(PSTR(" "), false);
    oled_write(get_u8_str(get_current_wpm(), ' '), false);
#endif
}

void render_default_layer_state(void) {
    oled_write_P(PSTR("Layer"), false);
    oled_write_P(PSTR(" "), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("QRTY"), false);
            break;
        case _LOWER:
            oled_write_ln_P(PSTR("LOW "), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("HIGH"), false);
            break;
        case _ADJUST:
            oled_write_ln_P(PSTR("ADJ "), false);
         case _NUMERIC:
            break;
            oled_write_ln_P(PSTR("NUM "), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undefined"), false);
    }
}

void render_keylock_status(led_t led_state) {
    oled_write_ln_P(PSTR("Lock\n"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("N"), led_state.num_lock);
    oled_write_P(PSTR("C"), led_state.caps_lock);
    oled_write_ln_P(PSTR("S\n"), led_state.scroll_lock);
}

void render_mod_status(uint8_t modifiers) {
    oled_write_ln_P(PSTR("Mods"), false);
    oled_write_P(PSTR("  "), false);
    oled_write_P(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR("C"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR("A"), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR("G"), (modifiers & MOD_MASK_GUI));
}

void render_status_main(void) {
    // Show keyboard layout
    render_default_layer_state();
    // Add a empty line
    oled_write_P(PSTR("-----"), false);
    // Show host keyboard led status
    render_keylock_status(host_keyboard_led_state());
    // Add a empty line
    oled_write_P(PSTR("-----"), false);
    // Show modifier status
    render_mod_status(get_mods());
    // Add a empty line
    oled_write_P(PSTR("-----"), false);
    render_wpm(0);
    render_keylogger_status();
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
  }  else {
        oled_render_logo();
    }
  return false;
}

bool set_scrolling = false;
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (set_scrolling) {
        mouse_report.h = mouse_report.x;
        mouse_report.v = mouse_report.y;
        mouse_report.x = mouse_report.y = 0; 
    }
    return mouse_report;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        add_keylog(keycode, &record->event.key);
    }
    //uint8_t modifiers = host_keyboard_leds();
/*     switch (keycode) { */
        /* case LSFT_T(KC_A): */
        /*     if (record->tap.count && record->event.pressed) { */
        /*         //tap_code(KC_C); */
        /*     } else if (record->event.pressed) { */
        /*         tap_code((KC_F)); */
        /*     } */
        /*     return false; */
    /* } */

#ifdef POINTING_DEVICE_ENABLE



  switch (keycode) {
      case BALL_HUI:
        //if (record->event.pressed) { ball_increase_hue(); }
        break;
      case BALL_WHT:
        //if (record->event.pressed) { cycle_white(); }
        break;
      case BALL_DEC:
        //if (record->event.pressed) { decrease_color(); }
        break;
      case BALL_SCR:
        if (record->event.pressed) {
            //trackball_set_scrolling(true);
        } else {
            //trackball_set_scrolling(false);
        }
        break;
      case BALL_NCL:
        record->event.pressed ? register_code(KC_BTN1) : unregister_code(KC_BTN1);
        break;
      case BALL_RCL:
        record->event.pressed ? register_code(KC_BTN2) : unregister_code(KC_BTN2);
        break;
      case BALL_MCL:
        record->event.pressed ? register_code(KC_BTN3) : unregister_code(KC_BTN3);
        break;
  }
#endif

    return true;
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}


#endif // OLED_ENABLE


// Rotary encoder related code
#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { // Encoder on master side
    if(IS_LAYER_ON(_RAISE)) { // on Raise layer
      // Cursor control
      if (clockwise) {
          tap_code(KC_MNXT);
      } else {
          tap_code(KC_MPRV);
      }
    }
    else {
      if (clockwise) {
          tap_code(KC_VOLU);
      } else {
          tap_code(KC_VOLD);
      }
    }
  }
  else if (index == 1) { // Encoder on slave side
    if(IS_LAYER_ON(s_LOWER)) { // on Lower layer
      //
      if (clockwise) {
          tap_code(KC_LEFT);
      } else {
          tap_code(KC_RIGHT);
      }
    }
    else {
      if (clockwise) {
          tap_code(KC_DOWN);
      } else {
          tap_code(KC_UP);
      }
    }
  }
    return true;
}
#endif


enum combos {
  JK_ESC,

  RM_BSLASH,
  VU_SLSH,

  RT_LPRN,
  YU_RPRN,

  FG_LPRN,
  HJ_RPRN,

  VB_LCBR,
  NM_RCBR,

  LSRS_CAPSLOCK
};

const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM rm_combo[] = {KC_R, KC_M, COMBO_END};
const uint16_t PROGMEM vu_combo[] = {KC_V, KC_U, COMBO_END};

const uint16_t PROGMEM rt_combo[] = {KC_R, KC_T, COMBO_END};
const uint16_t PROGMEM yu_combo[] = {KC_Y, KC_U, COMBO_END};

const uint16_t PROGMEM fg_combo[] = {KC_F, KC_G, COMBO_END};
const uint16_t PROGMEM hj_combo[] = {KC_H, KC_J, COMBO_END};

const uint16_t PROGMEM vb_combo[] = {KC_V, KC_B, COMBO_END};
const uint16_t PROGMEM nm_combo[] = {KC_N, KC_M, COMBO_END};

const uint16_t PROGMEM lsrs_combo[] = {KC_LSFT, KC_RSFT, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {

  // For Vim, put Escape on the home row
  [JK_ESC]    = COMBO(jk_combo, KC_ESC),

  // a line between the R & M positions draws a back slash
  [RM_BSLASH] = COMBO(rm_combo, KC_BSLASH),

  // a line between the V & U positions draws a forward slash
  [VU_SLSH]   = COMBO(vu_combo, KC_SLSH),

  // Brackets combos are pressed with a single finger in between two keys
  [RT_LPRN]   = COMBO(rt_combo, KC_LPRN),
  [YU_RPRN]   = COMBO(yu_combo, KC_RPRN),

  // Parens are pressed with a single finger between F&J or H&J
  [FG_LPRN]   = COMBO(fg_combo, KC_LBRC),
  [HJ_RPRN]   = COMBO(hj_combo, KC_RBRC),

  // Curly Braces are pressed with a single figure between two keys
  [VB_LCBR]   = COMBO(vb_combo, KC_LCBR),
  [NM_RCBR]   = COMBO(nm_combo, KC_RCBR),
  [LSRS_CAPSLOCK]   = COMBO(lsrs_combo, KC_CAPSLOCK)
};


/* #ifdef POINTING_DEVICE_ENABLE */
/* uint8_t white = 0; */
/* uint8_t red = 255; */
/* uint8_t green = 0; */
/* uint8_t blue = 0; */
/* void ball_increase_hue(void){ */
/*       if(red!=255&&green!=255&&blue!=255){ red =255; } */
/*       if (red==255&&green<255&&blue==0){ green += 15; */
/*       } else if(green==255&&blue==0&&red>0){ red-=15; */
/*       } else if(red==0&&blue<255&&green==255){ blue+=15; */
/*       } else if(blue==255&&green>0&&red==0){ green -= 15; */
/*       } else if(green == 0&&blue==255&&red<255){ red +=15; */
/*       } else if(green ==0&&blue>0&&red==255){ blue -=15; } */
/*       pimoroni_trackball_set_rgbw(red,green,blue,white); */
/* } */
/* void decrease_color(void){ */
/*   if (green>0){ green-=15; } */
/*   if (red>0){ red-=15; } */
/*   if (blue>0){ blue-=15; } */
/*   pimoroni_trackball_set_rgbw(red,green,blue,white); */
/* } */
/* void cycle_white(void){ */
/*   if (white<255){ white +=15; */
/*   } else{ white=0; } */
/*   pimoroni_trackball_set_rgbw(red,green,blue,white); */
/* } */
/* #endif //trackball */

#ifdef POINTING_DEVICE_ENABLE
uint8_t white = 0;
uint8_t red = 255;
uint8_t green = 0;
uint8_t blue = 0;
void ball_increase_hue(void){
/*       if(red!=255&&green!=255&&blue!=255){ red =255; } */
      /* if (red==255&&green<255&&blue==0){ green += 15; */
      /* } else if(green==255&&blue==0&&red>0){ red-=15; */
      /* } else if(red==0&&blue<255&&green==255){ blue+=15; */
      /* } else if(blue==255&&green>0&&red==0){ green -= 15; */
      /* } else if(green == 0&&blue==255&&red<255){ red +=15; */
      /* } else if(green ==0&&blue>0&&red==255){ blue -=15; } */
      /* pimoroni_trackball_set_rgbw(red,green,blue,white); */
}
void decrease_color(void){
  /* if (green>0){ green-=15; } */
  /* if (red>0){ red-=15; } */
  /* if (blue>0){ blue-=15; } */
  /* pimoroni_trackball_set_rgbw(red,green,blue,white); */
}
void cycle_white(void){
  /* if (white<255){ white +=15; */
  /* } else{ white=0; } */
  /* pimoroni_trackball_set_rgbw(red,green,blue,white); */
}
#endif //trackball

#ifdef AUDIO_ENABLE
void keyboard_pre_init_kb(void) { //thank you to @sigprof for this
    // Set audio pins to analog mode
    palSetLineMode(A5, PAL_MODE_INPUT_ANALOG);
    palSetLineMode(B1, PAL_MODE_INPUT_ANALOG);
}

void keyboard_post_init_kb(void) {
    // Enable OPAMP1 as A5 → B1 follower
    OPAMP3->CSR = OPAMP3_CSR_VMSEL_1 | OPAMP3_CSR_VMSEL_0 | OPAMP3_CSR_VPSEL_0 | OPAMP3_CSR_OPAMP3EN;
}
#endif //audio

#ifdef RAW_ENABLE
void raw_hid_receive(uint8_t *data, uint8_t length) {
    //raw_hid_send(data, length);
}
#endif
