/***********************************************************************************************************************
 This is a port of the code that is used to control the "Adafruit Bicolor LED Square Pixel Matrix" to C. Also functions
 to easily display characters on the LED matrix were added. You can find the original C++ code at
 https://github.com/adafruit/Adafruit-LED-Backpack-Library and the bicolor matrix at
 https://www.adafruit.com/products/902.

 Original work Copyright (c) 2012 Adafruit Industries
 Modified work Copyright (c) 2015 Tobias Trumm

 Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
 rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit
 persons to whom the Software is furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
 Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
 OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
 OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 **********************************************************************************************************************/
#ifndef LEDBACKPACK_BICOLOR_BICOLOR_MATRIX_H
#define LEDBACKPACK_BICOLOR_BICOLOR_MATRIX_H

#include <linux/i2c-dev.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define BICOLOR_MATRIX_LED_OFF 0
#define BICOLOR_MATRIX_LED_RED 1
#define BICOLOR_MATRIX_LED_YELLOW 2
#define BICOLOR_MATRIX_LED_GREEN 3

#define BICOLOR_MATRIX_BLINK_OFF 0
#define BICOLOR_MATRIX_BLINK_2HZ  1
#define BICOLOR_MATRIX_BLINK_1HZ  2
#define BICOLOR_MATRIX_BLINK_HALFHZ  3

typedef struct _Matrix *Matrix;

/**
 * @brief Initiate the i2c connection to the matrix.
 *
 * @param _addr i2c address of the matrix
 * @param _bus  i2c bus that the matrix is connected to. Pass 1 if it is connected to /dev/i2c-1, 2 if it is connected to /dev/i2c-2, and so on.
 *
 * @return A Matrix pointer that is used in subesquent functions.
 */
Matrix *bicolor_matrix_init_i2c_connection(uint8_t _addr, uint8_t _bus);

/**
 * @brief Close the i2c connection to the matrix.
 *
 * @param m Pointer to the matrix whose connection should be closed
 */
void bicolor_matrix_close_i2c_connection(Matrix *m);

/**
 * @brief Set up the matrix
 *
 * @param m Pointer to the matrix that should be set up.
 */
void bicolor_matrix_begin(Matrix *m);

/**
 * @brief Set brightness of the matrix.
 *
 * @param m Pointer to the matrix whose brightness should be changed.
 * @param b Brightness. Accepts values between 0 and 15 (including these values). If the value is higher than 15 brightness will be set to 15.
 */
void bicolor_matrix_set_brightness(Matrix *m, uint8_t b);

/**
 * @brief Set blink rate
 *
 * @param m Pointer to the matrix whose blink rate should be changed
 * @param b Blink rate
 *          BICOLOR_MATRIX_BLINK_OFF     No blinking
 *          BICOLOR_MATRIX_BLINK_2HZ     2 Hz
 *          BICOLOR_MATRIX_BLINK_1HZ     1 Hz
 *          BICOLOR_MATRIX_BLINK_HALFHZ  0.5 Hz
 */
void bicolor_matrix_blink_rate(Matrix *m, uint8_t b);

/**
 * @brief Write content of the display buffer to the led matrix
 *
 * @param m Pointer to the matrix.
 */
void bicolor_matrix_write_display(Matrix *m);

/**
 * @brief Clear the display buffer.
 *
 * Call bicolor_matrix_write_display() to apply the changes to the matrix.
 *
 * @param m Pointer to the matrix.
 */
void bicolor_matrix_clear(Matrix *m);

/**
 * @brief Set a pixel on the display buffer
 *
 * @param m     Pointer to the matrix.
 * @param x     x-coordinate. Values < 0 or > 7 will be ignored.
 * @param y     y-coordinate. Values < 0 or > 7 will be ignored.
 * @param color Possible values:
 *              BICOLOR_MATRIX_LED_OFF
 *              BICOLOR_MATRIX_LED_RED
 *              BICOLOR_MATRIX_LED_YELLOW
 *              BICOLOR_MATRIX_LED_GREEN
 */
void bicolor_matrix_draw_pixel(Matrix *m, int16_t x, int16_t y, uint16_t color);

/**
 * @brief Set rotation of the image
 *
 * This will not affect pixels that are already written to the display buffer. If you want to rotate the current image
 * you have to clear the display buffer, call bicolor_matrix_set_rotation and then draw your image again.
 *
 * @param m Pointer to the matrix.
 * @param r Rotation of the image. Values > 3 will be changed to (r % 4)
 */
void bicolor_matrix_set_rotation(Matrix *m, uint8_t r);

/**
 * @brief Write a character to the display buffer.
 *
 * Call bicolor_matrix_write_display() to apply the changes to the matrix.
 *
 * @param m				   Pointer to the matrix.
 * @param c                Character that should be displayed on the matrix
 * @param font_color       Font color. Possible values: BICOLOR_MATRIX_LED_OFF, BICOLOR_MATRIX_LED_RED, BICOLOR_MATRIX_LED_YELLOW and BICOLOR_MATRIX_LED_GREEN
 * @param background_color Background color. Possible values: BICOLOR_MATRIX_LED_OFF, BICOLOR_MATRIX_LED_RED, BICOLOR_MATRIX_LED_YELLOW and BICOLOR_MATRIX_LED_GREEN
 *
 */
void bicolor_matrix_draw_character(Matrix *m, char c, uint8_t font_color, uint8_t background_color);

/**
 * @brief Free a matrix struct
 *
 * Calling this function closes the i2c connection if it is still open.
 *
 * @param m  Pointer to the matrix struct.
 */
void bicolor_matrix_free(Matrix *m);

#endif //LEDBACKPACK_BICOLOR_BICOLOR_MATRIX_H
