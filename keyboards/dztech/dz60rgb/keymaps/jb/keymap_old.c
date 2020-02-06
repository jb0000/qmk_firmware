#include QMK_KEYBOARD_H
#define _LAYER0 0
#define _LAYER1 1
#define _LAYER2 2
#define _LAYER3 3
#define _LAYER4 4
#define WIND_LEFT LCTL(LGUI(KC_LEFT))
#define WIND_RIGHT LCTL(LGUI(KC_RGHT))
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;     
uint16_t switch_timer = 0; 
bool switching = false;   


enum custom_keycodes {
  SWITCHKVM = SAFE_RANGE,
  ALT_TAB,
  R_ALT_TAB,
  LCTLL,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_60_ansi(
		KC_GESC, KC_1,    KC_2,                 KC_3,               KC_4,    KC_5,    KC_6,    KC_7,    KC_8,       KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC,
		KC_TAB,           KC_Q,                 KC_W,               KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,       KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
		CTL_T(KC_ENT),    KC_A,  				KC_S,				KC_D,    KC_F,    KC_G,    KC_H,    KC_J,       KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
		KC_LSPO,          KC_Z,                 KC_X,               KC_C,    KC_V,    KC_B,    KC_N,    KC_M,       KC_COMM, KC_DOT,  KC_SLSH,          KC_RSPC,
		MO(1),          KC_LGUI,              KC_LALT,                              LT(2,KC_SPC),                                         KC_RALT,  MO(3),  KC_APP,  MO(4)),
	[1] = LAYOUT_60_ansi(
		_______,  _______,   _______,           _______,            _______,   _______,   _______,   _______,   _______,      _______,   _______,  _______,  _______,           _______,
		_______,          _______,              _______,            _______, _______, _______, _______, _______,    _______,   _______, _______, _______, _______, _______,
		_______,          KC_1,                 KC_2,               KC_3,    KC_4,    KC_5, KC_6, KC_7,   KC_8, KC_9, KC_0, KC_MINS,           KC_EQL,
		_______,          _______,              _______,            _______, _______, _______, _______,  _______,    _______, _______, _______,          _______,
		_______,		  _______,              _______,                              _______,                                        _______, _______, _______,  _______),

	[2] = LAYOUT_60_ansi(
		KC_GRV,  KC_F1,   KC_F2,                KC_F3,              KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,      KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_DEL,
		_______,          _______,              _______,            WIND_LEFT, WIND_RIGHT, _______, _______, KC_PGUP,    KC_UP,   KC_PGDN, _______, _______, _______, _______,
		CTL_T(KC_ENT),    _______,              SWITCHKVM,         R_ALT_TAB,ALT_TAB, _______, KC_HOME, KC_LEFT,   KC_DOWN, KC_RGHT, KC_BSPC, KC_DEL,           _______,
		_______,          _______,              _______,            _______, _______, _______, KC_END,  _______,    _______, _______, _______,          _______,
		_______,		  _______,              _______,                              _______,                                        _______, _______, _______,  _______),


	[3] = LAYOUT_60_ansi(
		_______,  KC_MS_ACCEL0,   KC_MS_ACCEL1,           KC_MS_ACCEL2,            _______,   _______,   _______,   _______,   _______,      _______,   _______,  _______,  _______,           _______,
		_______,          _______,              KC_MS_WH_UP,            _______, _______, _______, _______, _______,    KC_MS_UP,   _______, _______, _______, _______, _______,
		_______,          KC_MS_WH_LEFT,              KC_MS_WH_DOWN,             KC_MS_WH_RIGHT,_______, _______, _______, KC_MS_LEFT,   KC_MS_DOWN, KC_MS_RIGHT, _______, _______,           _______,
		_______,          _______,              _______,            _______, _______, _______, _______,  _______,    _______, _______, KC_MS_BTN2,          _______,
		_______,		  _______,              _______,                              KC_MS_BTN1,                                        _______, _______, _______,  _______),		


	[4] = LAYOUT_60_ansi(
		KC_GRV,  KC_F1,   KC_F2,                KC_F3,              KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,      KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_DEL,
		_______,          RGB_TOG,              RGB_MOD,            RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI,    RGB_VAD, _______, _______, _______, _______, _______,
		_______,          _______,              _______,            _______, _______, _______, _______, _______,    _______, _______, _______, _______,          SWITCHKVM,
		_______,          _______,              _______,            _______, _______, _______,  _______, _______,  _______,  KC_VOLD, KC_VOLU,         _______,
		_______, 		  _______,             _______,                              _______,                                        KC_MPRV, KC_MPLY, KC_MNXT, _______),
		};

void rgb_matrix_layer_helper (uint8_t red, uint8_t green, uint8_t blue, bool default_layer) {
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_MODIFIER)) {
        rgb_matrix_set_color( i, red, green, blue );
    }
  }
}

void rgb_matrix_indicators_user(void) {
	  /*uint8_t this_led = host_keyboard_leds();
	  if (!g_suspend_state) {
	    switch (biton32(layer_state)) {
	      case _LAYER1:
		    rgb_matrix_layer_helper(0xFF, 0x00, 0x00, false); break;
	      case _LAYER2:
	        rgb_matrix_layer_helper(0x00, 0xFF, 0x00, false); break;
	      case _LAYER3:
	        rgb_matrix_layer_helper(0x00, 0x00, 0xFF, false); break;
	      case _LAYER4:
	        rgb_matrix_layer_helper(0xFF, 0xFF, 0x00, false); break;
	    							  }
	                        }
	  if ( this_led & (1<<USB_LED_CAPS_LOCK)) {
	        rgb_matrix_set_color(40, 0xFF, 0xFF, 0xFF);
	  }*/

}

void matrix_init_user(void) {
  //user initialization
}

void matrix_scan_user(void) {
	if (is_alt_tab_active && biton32(layer_state) != _LAYER2)
    {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  	if (switching && timer_elapsed(switch_timer) > 100) {
       tap_code(KC_SLCK);
       switching = false;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	    switch (keycode) {
    case SWITCHKVM:
      if (record->event.pressed) {
		  tap_code(KC_SLCK);
		  switching = true;
		  switch_timer = timer_read();
	  }
	  break;
	  case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        } 
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      } 
      break;
	case R_ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        } 
		register_code(KC_LSFT);
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
		unregister_code(KC_LSFT);
      } 
      break;
    case LCTLL:
      if (record->event.pressed) {         
        register_code(KC_LCTL);
		layer_on(5);
	  } else {
        unregister_code(KC_LCTL);
		layer_off(5);
      } 
      break;  
  }
  return true;
}
