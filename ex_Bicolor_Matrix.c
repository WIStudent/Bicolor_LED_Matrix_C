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
#define _XOPEN_SOURCE 700
#include "Bicolor_Matrix.h"
#include <signal.h>
#include <stdbool.h>
#include <time.h>



void INThandler(int sig)
{
	bicolor_matrix_clear();
	bicolor_matrix_write_display();
	bicolor_matrix_close_i2c_connection();
	exit(0);
}

int main(int argc, char *argv[])
{
	signal(SIGINT, INThandler);

	bicolor_matrix_init_i2c_connection(0x70, 1);
	bicolor_matrix_begin();


	while(true)
	{
		bicolor_matrix_clear();
		for (int color = 1; color < 5; color++)
		{
			for (int16_t y = 0; y < 8; y++)
			{
				for (int16_t x = 0; x < 8; x++)
				{
					bicolor_matrix_draw_pixel(x, y, color);
					bicolor_matrix_write_display();

					nanosleep((const struct timespec[]) {{0, 100000000L}}, NULL);

				}
			}
		}
		for(int c = 32; c < 128; c++)
		{
			bicolor_matrix_draw_character(c, BICOLOR_MATRIX_LED_OFF, BICOLOR_MATRIX_LED_RED);
			bicolor_matrix_write_display();
			nanosleep((const struct timespec[]) {{1, 0L}}, NULL);
		}
	}
}
