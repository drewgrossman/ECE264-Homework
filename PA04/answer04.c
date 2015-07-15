
#include "answer04.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

// ------------------------------------------------------------------ Predefin
/**
 * Welcome to PA04.
 *
 * This file is an example to help you get started.
 * It works on BMP files and inverts the pixel intensity (whiteness)
 * You will need to write routines to read and write the simpler
 * ece264 format, and perform linear normalization.
 */
 
 /*
int main(int argc, char * * argv)
{
    int ret = EXIT_SUCCESS; // unless otherwise noted

    const char * in_filename = argv[1];
    const char * out_filename = argv[2];

    // Read the file
    Image * im = Image_loadbmp(in_filename);
    if(im == NULL) {
	fprintf(stderr, "Error: failed to read '%s'\n", in_filename);
	return EXIT_FAILURE;
    }

    // Linear Normalization
	
	//linearNormalization(int im->width, int im->height, uint8_t * intensity);

	
    int n_pixels = im->width * im->height;
    int ind;
    for(ind = 0; ind < n_pixels; ++ind)
	im->data[ind] = 255 - im->data[ind];
	
	 
	int n_pixels = im->width * im->height;
    int ind;
	
	int max  = 0;
	int min = 255;
		
    for(ind = 0; ind < n_pixels; ++ind)
	{
		if(im->data[ind] > max)
			max = im->data[ind];
		else if(im->data[ind] < min)
			min = im->data[ind];
	}
    for(ind = 0; ind < n_pixels; ++ind)
	{
		im->data[ind] = (im->data[ind] - min) * 255.0 / (max - min);
	}

}
*/


// --------------------------------------------------------------- Image_loadbmp

/**
 * Loads a bmp (windows bitmap) image, returning an Image structure.
 * Will return NULL if there is any error.
 *
 * Note: This function is written for you and appears in image-bmp.c
 */


// -------------------------------------------------------------- BMP_checkValid

/**
 * We are only interested in a subset of BMP functionality.
 */

// ------------------------------------------------------------- BMP_printHeader


/**
 * Loads an ECE264 image file, returning an Image structure.
 * Will return NULL if there is any error.
 *
 * Hint: Please see the README for extensive hints
 */
Image * Image_load(const char * filename)
{
	return 0;
}

/**
 * Save an image to the passed filename, in ECE264 format.
 * Return TRUE if this succeeds, or FALSE if there is any error.
 *
 * Hint: Please see the README for extensive hints
 */
int Image_save(const char * filename, Image * image)
{
	return 0;
}

/**
 * Free memory for an image structure
 *
 * Image_load(...) (above) allocates memory for an image structure. 
 * This function must clean up any allocated resources. If image is 
 * NULL, then it does nothing. (There should be no error message.) If 
 * you do not write this function correctly, then valgrind will 
 * report an error. 
 */
void Image_free(Image * image)
{
	
	image = NULL;
	
	
	return;
}

/**
 * Performs linear normalization, see README
 */

void linearNormalization(int width, int height, uint8_t * intensity)
{

    int n_pixels = width * height;
    int ind;
	
	int max  = 0;
	int min = 255;
		
    for(ind = 0; ind < n_pixels; ++ind)
	{
		if(intensity[ind] > max)
			max = intensity[ind];
		else if(intensity[ind] < min)
			min = intensity[ind];
	}
    for(ind = 0; ind < n_pixels; ++ind)
	{
		intensity[ind] = (intensity[ind] - min) * 255.0 / (max - min);
	}
	
 return;
}