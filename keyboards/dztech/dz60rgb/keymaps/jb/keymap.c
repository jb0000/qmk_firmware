#include QMK_KEYBOARD_H
#define _LAYER0 0
#define _LAYER1 1
#define _LAYER2 2
#define _LAYER3 3
#define _LAYER4 4
#define _LAYER5 5
#define WIND_LEFT LCTL(LGUI(KC_LEFT))
#define WIND_RIGHT LCTL(LGUI(KC_RGHT))
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;     
uint16_t switch_timer = 0; 
uint16_t arrow_timer = 0; 
bool switching = false;   


enum custom_keycodes {
  SWITCHKVM = SAFE_RANGE,
  ALT_TAB,
  R_ALT_TAB,
  LEFTHOME,
  UPPGUP,
  DOWNPGDOWN,
  RIGHTEND,
  GITPULL,
  GITCOMMIT,
  GITCOMMITALL,
  GITPUSH,
  GITSTATUS,
  GITSTATUSUNO,
  GITLOG,
  GITDIFF,
  GITCHECKOUT,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_60_ansi(
		KC_GESC, KC_1, KC_2,	KC_3,      KC_4,    KC_5,    KC_6,    KC_7,    KC_8,       KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC,
		KC_TAB,        KC_Q,    KC_W,      KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,       KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
		CTL_T(KC_ENT), KC_A,    KC_S,	   KC_D,    KC_F,    KC_G,    KC_H,    KC_J,       KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
		KC_LSPO,       KC_Z,    KC_X,      KC_C,    KC_V,    KC_B,    KC_N,    KC_M,       KC_COMM, KC_DOT,  KC_SLSH,          KC_RSPC,
		KC_LCTL,       KC_LGUI, KC_LALT,            	     LT(1,KC_SPC),                                   KC_RALT,  MO(3),  KC_APP,  MO(4)),

	[1] = LAYOUT_60_ansi(
		KC_GRV,    KC_F1, KC_F2,   KC_F3,    KC_F4,     KC_F5,   KC_F6,   KC_F7,     KC_F8,      KC_F9,   KC_F10,   KC_F11,  KC_F12,           KC_DEL,
		SWITCHKVM,        KC_1,    KC_2,     KC_3,      KC_4,    KC_5,    KC_6,      KC_7,       KC_8,    KC_9,     KC_0,    KC_MINS, KC_EQL,  _______,
		_______,   	      _______, _______,  R_ALT_TAB, ALT_TAB, OSL(2),  LEFTHOME,  DOWNPGDOWN, UPPGUP,  RIGHTEND, KC_BSPC, KC_DEL,           _______,
		_______,          _______, _______,  _______,   _______, _______, WIND_LEFT, WIND_RIGHT, _______, _______,  _______,          SWITCHKVM,  
		_______,	 	  _______, _______,                      _______,                                           _______, _______, _______, _______),

	[2] = LAYOUT_60_ansi(
		XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX,      XXXXXXX, XXXXXXX,          XXXXXXX,
		XXXXXXX,           XXXXXXX, GITSTATUS,    XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, 		XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX,           GITLOG,  GITSTATUSUNO, GITDIFF, GITCHECKOUT, XXXXXXX, XXXXXXX, GITPULL, GITCOMMIT, GITCOMMITALL, GITPUSH, XXXXXXX,          XXXXXXX,
		XXXXXXX,           XXXXXXX, XXXXXXX, 	  XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, 		XXXXXXX,          XXXXXXX,
		XXXXXXX,  		   XXXXXXX, XXXXXXX,                            XXXXXXX,                                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),

	[3] = LAYOUT_60_ansi(
		_______,  KC_MS_ACCEL0, KC_MS_ACCEL1, KC_MS_ACCEL2,  _______,  	  	_______,   		_______, _______, _______,    _______,    _______,     _______,    _______,          _______,
		_______,          		_______,      _______,       KC_MS_WH_UP, 	_______, 		_______, _______, _______,    KC_MS_UP,   _______, 	   _______,    _______, _______, _______,
		_______,          		_______,      KC_MS_WH_LEFT, KC_MS_WH_DOWN, KC_MS_WH_RIGHT, _______, _______, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, _______,    _______,          _______,
		_______,          		_______,      _______,       _______, 		_______, 		_______, _______, _______,    _______,    _______,     KC_MS_BTN2,          _______,
		_______,		  		_______,      _______,                         		 		KC_MS_BTN1,                                        	   _______,    _______, _______, _______),		
 

	[4] = LAYOUT_60_ansi(
		KC_GRV,  KC_F1, KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,      KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_DEL,
		_______,        RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI,    RGB_VAD, _______, _______, _______, _______, _______,
		_______,        _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______,          SWITCHKVM,
		_______,        _______, _______, _______, _______, _______, _______, _______,  _______,  KC_VOLD, KC_VOLU,           _______,
		_______,  		_______, _______,                   _______,                                        KC_MPRV, KC_MPLY, KC_MNXT, _______),
	};

/*
		13,      12,      11,       10,      9,       8,       7,       6,       5,       4,       3,       2,       1,       0,      \
		27,      26,      25,       24,      23,      22,      21,      20,      19,      18,      17,      16,      15,      14,     \
		40,      39,      38,       37,      36,      35,      34,      33,      32,      31,      30,      29,      28,              \
		53,      52,      51,       50,      49,      48,      47,      46,      45,      44,      43,               42,      41,     \
		62,      61,      60,                         59,                        58,      57,               56,      55,      54      \
*/

void rgb_matrix_layer_helper (uint8_t red, uint8_t green, uint8_t blue) {
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        rgb_matrix_set_color( i, red, green, blue );
  }
}
layer_state_t layer_state_set_user(layer_state_t state) {
    if (!g_suspend_state) {
        switch (get_highest_layer(state)) {
            case _LAYER0:
                rgb_matrix_layer_helper(0, 0, 0);
                break;
            case _LAYER2:
                // homerow
                rgb_matrix_set_color(39, 0x00, 0xFF, 0x00);
                rgb_matrix_set_color(38, 0x00, 0xFF, 0x00);
                rgb_matrix_set_color(37, 0x00, 0xFF, 0x00);
                rgb_matrix_set_color(36, 0x00, 0xFF, 0x00);
                rgb_matrix_set_color(33, 0x00, 0xFF, 0x00);
                rgb_matrix_set_color(32, 0x00, 0xFF, 0x00);
                rgb_matrix_set_color(31, 0x00, 0xFF, 0x00);
                rgb_matrix_set_color(30, 0x00, 0xFF, 0x00);
                // additionals
                rgb_matrix_set_color(25, 0x00, 0xFF, 0x00);
                break;
            case _LAYER4:
                rgb_matrix_set_color(54, 0x00, 0xFF, 0xFF);
                rgb_matrix_set_color(55, 0x00, 0xFF, 0xFF);
                rgb_matrix_set_color(56, 0x00, 0xFF, 0xFF);
                rgb_matrix_set_color(42, 0x00, 0xFF, 0xFF);
                rgb_matrix_set_color(43, 0x00, 0xFF, 0xFF);
                break;
        }
    }
    return state;
}
/*
void rgb_matrix_indicators_user(void) {
	  if ( this_led & (1<<USB_LED_CAPS_LOCK)) {
	        rgb_matrix_set_color(40, 0xFF, 0xFF, 0xFF);
	  }
}
*/
void matrix_init_user(void) {
  	rgblight_mode(99);
}

void matrix_scan_user(void) {
	if (is_alt_tab_active && biton32(layer_state) != _LAYER1)
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
                switching    = true;
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
        case LEFTHOME:
            if (record->event.pressed) {
                arrow_timer = timer_read();
            } else {
                if (timer_elapsed(arrow_timer) > 120) {
                    tap_code(KC_HOME);
                } else {
                    tap_code(KC_LEFT);
                }
            }
            break;
        case UPPGUP:
            if (record->event.pressed) {
                arrow_timer = timer_read();
            } else {
                if (timer_elapsed(arrow_timer) > 120) {
                    tap_code(KC_PGUP);
                } else {
                    tap_code(KC_UP);
                }
            }
            break;
        case DOWNPGDOWN:
            if (record->event.pressed) {
                arrow_timer = timer_read();
            } else {
                if (timer_elapsed(arrow_timer) > 120) {
                    tap_code(KC_PGDN);
                } else {
                    tap_code(KC_DOWN);
                }
            }
            break;
        case RIGHTEND:
            if (record->event.pressed) {
                arrow_timer = timer_read();
            } else {
                if (timer_elapsed(arrow_timer) > 120) {
                    tap_code(KC_END);
                } else {
                    tap_code(KC_RIGHT);
                }
            }
            break;
        case GITPULL:
            if (record->event.pressed) {
                SEND_STRING("git pull\n");
            }
            break;
        case GITCOMMIT:
            if (record->event.pressed) {
                SEND_STRING("git commit -m''");
                tap_code(KC_LEFT);
            }
            break;
        case GITCOMMITALL:
            if (record->event.pressed) {
                SEND_STRING("git commit -a -m''");
                tap_code(KC_LEFT);
            }
            break;
        case GITPUSH:
            if (record->event.pressed) {
                SEND_STRING("git push\n");
            }
            break;
        case GITSTATUS:
            if (record->event.pressed) {
                SEND_STRING("git status\n");
            }
            break;
        case GITSTATUSUNO:
            if (record->event.pressed) {
                SEND_STRING("git status -uno\n");
            }
            break;
        case GITLOG:
            if (record->event.pressed) {
                SEND_STRING("git log\n");
            }
            break;
        case GITDIFF:
            if (record->event.pressed) {
                SEND_STRING("git diff\n");
            }
            break;
        case GITCHECKOUT:
            if (record->event.pressed) {
                SEND_STRING("git checkout ");
            }
            break;
    }
    return true;
}
