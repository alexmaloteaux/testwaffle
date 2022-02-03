/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

/* Select hand configuration */

#define MASTER_LEFT
//#define MASTER_RIGHT
//#define EE_HANDS


/* #ifdef RGBLIGHT_ENABLE */
/* #    undef RGBLED_NUM */
/* #    define RGBLIGHT_ANIMATIONS */
/* #    define RGBLED_NUM 54 */
/* #    undef RGBLED_SPLIT */
/* #    define RGBLED_SPLIT \ */
/*         { 27, 27 } */
/* #    define RGBLIGHT_LIMIT_VAL 255 */
/* #    define RGBLIGHT_HUE_STEP  10 */
/* #    define RGBLIGHT_SAT_STEP  17 */
/* #    define RGBLIGHT_VAL_STEP  17 */
/* #endif */



/* #undef SOFT_SERIAL_PIN */
/* //#define SELECT_SOFT_SERIAL_SPEED 5 */
/* #define SOFT_SERIAL_PIN D3 */
/* #define SERIAL_USART_SPEED 921600 */
/* #define SERIAL_USART_DRIVER SD1 */
/* #define SERIAL_USART_TX_PAL_MODE 7 */



#pragma once
#include "config_common.h"
#undef PRODUCT
#undef MANUFACTURER
//#define MANUFACTURER Waffles
#define PRODUCT Protorne Keyboard
#undef USE_I2C
#undef SSD1306OLED
#ifdef AUDIO_ENABLE
#define AUDIO_PIN A5
#define STARTUP_SONG SONG(ODE_TO_JOY)
#endif
#define USE_SERIAL_PD2
#ifdef RGBLIGHT_ENABLE
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_LIMIT_VAL 100
#undef RGBLED_SPLIT
#define RGBLED_SPLIT { 27, 27 }
#endif
#ifdef RGB_MATRIX_ENABLE
//#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 100
#define RGB_MATRIX_SPLIT { 27, 27 }
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define SPLIT_TRANSPORT_MIRROR
#endif
#undef RGBLED_NUM
#undef RGB_DI_PIN
#define RGBLED_NUM 54
#define RGB_DI_PIN B5

//oled
#define OLED_TIMEOUT 50000
#define OLED_FONT_H "keyboards/wafflesm_smt32/lib/glcdfont.c"
#define OLED_UPDATE_INTERVAL 100

#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
#define BOOTMAGIC_LITE_ROW_RIGHT 4
#define BOOTMAGIC_LITE_COLUMN_RIGHT 0

#define WS2812_PWM_DRIVER PWMD3
#define WS2812_PWM_CHANNEL 3
#define WS2812_PWM_PAL_MODE 2
#define WS2812_DMA_STREAM STM32_DMA1_STREAM3
#define WS2812_DMA_CHANNEL 3


#undef SOFT_SERIAL_PIN
#define SOFT_SERIAL_PIN D3
#define SERIAL_USART_SPEED 921600
#define SERIAL_USART_DRIVER SD1
#define SERIAL_USART_TX_PAL_MODE 7
#define ENCODERS_PAD_A { B2 }
#define ENCODERS_PAD_B { B6 }
#define ENCODERS_PAD_A_RIGHT { B2 }
#define ENCODERS_PAD_B_RIGHT { B6 }

//(https://github.com/MangoIV/dracuLad)
#define POINTING_DEVICE_ROTATION_90

//comment that out if your trackball is on the left side
#define TRACKBALL_RIGHT

#ifdef TRACKBALL_RIGHT
    #define POINTING_DEVICE_INVERT_X
    #define POINTING_DEVICE_INVERT_Y
#endif
