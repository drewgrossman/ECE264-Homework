
#include "answer04.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

#define FALSE 0
#define TRUE 1


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
//{
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

//}
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
	FILE * fp = NULL;
    size_t read;
    ImageHeader header;
    Image * tmp_im = NULL, * im = NULL;
    size_t n_bytes = 0;
    int err = FALSE;

    if(!err) { // Open filename
	fp = fopen(filename, "rb");
	if(!fp) {
	    fprintf(stderr, "Failed to open file '%s'\n", filename);
	    err = TRUE;
	}
    }

    if(!err) { // Read the header
	read = fread(&header, sizeof(ImageHeader), 1, fp);
	if(read != 1) {
	    fprintf(stderr, "Failed to read header from '%s'\n", filename);
	    err = TRUE;
	}
    }
	
	
    if(!err) { // We're only interested in a subset of valid ee264 files
	if((header.magic_number) != ECE264_IMAGE_MAGIC_NUMBER) {
	    fprintf(stderr, "Invalid header in '%s'\n", filename);
	    err = TRUE;
	}
    }
	
	
    if(!err) { // Allocate Image struct
	tmp_im = malloc(sizeof(Image));			
	if(tmp_im == NULL) {
	    fprintf(stderr, "Failed to allocate im structure\n");
	    err = TRUE;
	} 
    }

    if(!err) { // Init the Image struct
	tmp_im->width = header.width;
	tmp_im->height = header.height;

	// Handle the comment
	char * filename_cpy = strdup(filename);	// we want to call basename
	char * file_basename = basename(filename_cpy); // requires editable str
	const char * prefix = "Original BMP file: ";
	n_bytes = sizeof(char) * (strlen(prefix) + strlen(file_basename) + 1);
	tmp_im->comment = malloc(n_bytes);
	if(tmp_im->comment == NULL) {
	    fprintf(stderr, "Failed to allocate %zd bytes for comment\n",
		    n_bytes);
	    err = TRUE;
	} else {
	    sprintf(tmp_im->comment, "%s%s", prefix, file_basename);
	}
	free(filename_cpy); // this also takes care of file_basename

	// Handle image data
	n_bytes = sizeof(uint8_t) * header.width * header.height;
	tmp_im->data = malloc(n_bytes);
	if(tmp_im->data == NULL) {
	    fprintf(stderr, "Failed to allocate %zd bytes for image data\n",
		    n_bytes);
	    err = TRUE;
	}
    }
	/*
    if(!err) { // Seek the start of the pixel data
	if(fseek(fp, header.offset, SEEK_SET) != 0) {
	    fprintf(stderr, "Failed to seek %d, the data of the image data\n",
		    header.offset);
	    err = TRUE;
	}
    }
	*/
	
	/*
    if(!err) { // Read pixel data
	size_t bytes_per_row = ((header.bits * header.width + 31)/32) * 4;
	n_bytes = bytes_per_row * header.height;
	uint8_t * rawbmp = malloc(n_bytes);
	if(rawbmp == NULL) {
	    fprintf(stderr, "Could not allocate %zd bytes of image data\n",
		    n_bytes);
	    err = TRUE;
	} else {
	    read = fread(rawbmp, sizeof(uint8_t), n_bytes, fp);
	    if(n_bytes != read) {
		fprintf(stderr, "Only read %zd of %zd bytes of image data\n", 
			read, n_bytes);
		err = TRUE;
	    } else {
		// Must convert RGB to grayscale
		uint8_t * write_ptr = tmp_im->data;
		uint8_t * read_ptr;
		int intensity;
		int row, col; // row and column
		for(row = 0; row < header.height; ++row) {
		    read_ptr = &rawbmp[row * bytes_per_row];
		    for(col = 0; col < header.width; ++col) {
			intensity  = *read_ptr++; // blue
			intensity += *read_ptr++; // green
			intensity += *read_ptr++; // red	
			*write_ptr++ = intensity / 3; // now grayscale
		    }
		}
	    }
	}
	free(rawbmp);
    }
	*/
	
    if(!err) { // We should be at the end of the file now
	uint8_t byte;
	read = fread(&byte, sizeof(uint8_t), 1, fp);
	if(read != 0) {
	    fprintf(stderr, "Stray bytes at the end of file '%s'\n",
		    filename);
	    err = TRUE;
	}
    }

    if(!err) { // We're winners... 
	im = tmp_im;  // bmp will be returned
	tmp_im = NULL; // and not cleaned up
    }

    // Cleanup
    if(tmp_im != NULL) {
	free(tmp_im->comment); // Remember, you can always free(NULL)
	free(tmp_im->data);
	free(tmp_im);
    }
    if(fp) {
	fclose(fp);
    }

    return im;
}

/**
 * Save an image to the passed filename, in ECE264 format.
 * Return TRUE if this succeeds, or FALSE if there is any error.
 *
 * Hint: Please see the README for extensive hints
 */
int Image_save(const char * filename, Image * image)
{
	int err = FALSE; 
    FILE * fp = NULL;
    uint8_t * buffer = NULL;    
    size_t written = 0;

    // Attempt to open file for writing
    fp = fopen(filename, "wb");
    if(fp == NULL) {
	fprintf(stderr, "Failed to open '%s' for writing\n", filename);
	return FALSE; // No file ==> out of here.
    }

    // Number of bytes stored on each row
    size_t bytes_per_row = (((24 * image->width + 31)/32) * 4)/3;

    // Prepare the header
    ImageHeader header;
    header.magic_number = ECE264_IMAGE_MAGIC_NUMBER;
    //header.size = sizeof(BMP_Header) + bytes_per_row * image->height;
    //header.reserved1 = 0;
    //header.reserved2 = 0;
    //header.offset = sizeof(BMP_Header);
    //header.header_size = sizeof(BMP_Header) - 14;
    header.width = image->width;
    header.height = image->height;
    //header.planes = 1;
    //header.bits = 24; // BGR
    //header.compression = 0; // no compression
    //header.imagesize = bytes_per_row * image->height;
    //header.xresolution = DEFAULT_DPI_X;
    //header.yresolution = DEFAULT_DPI_Y;
    //header.ncolors = 1 << header.bits;
    //header.importantcolors = 0; // i.e., every color is important
	header.comment_len = strlen(image->comment);

	
		
    if(!err) {  // Write the header
	written = fwrite(&header, sizeof(ImageHeader), 1, fp);
	if(written != 1) {
	    fprintf(stderr, 
		    "Error: only wrote %zd of %zd of file header to '%s'\n",
		    written, sizeof(ImageHeader), filename);
	    err = TRUE;	
	}
    }
	
	if(!err) { //comment
	written = fwrite(image->comment, strlen(image->comment) + 1, 1, fp);
	//written = fwrite((image->comment) + 1, 17, 1, fp);
	if(written != 1) {
	    fprintf(stderr, 
		    "Error: ony wrote %zd of %zd of file header to '%s'\n",
		    written, strlen(image->comment), filename);
	    err = TRUE;	
	}
    }
	
	
    if(!err) { // Before writing, we'll need a write buffer
	buffer = malloc(bytes_per_row);
	if(buffer == NULL) {
	    fprintf(stderr, "Error: failed to allocate write buffer\n");
	    err = TRUE;
	} else {
	    // not strictly necessary, we output file will be tidier.
	    memset(buffer, 0, bytes_per_row); 
	}
    }

    if(!err) { // Write pixels
	uint8_t * read_ptr = image->data;	
	int row, col; // row and column
	for(row = 0; row < header.height && !err; ++row) {
	    uint8_t * write_ptr = buffer;
	    for(col = 0; col < header.width; ++col) {
		*write_ptr++ = *read_ptr; // blue
		//*write_ptr++ = *read_ptr; // green
		//*write_ptr++ = *read_ptr; // red
		read_ptr++; // advance to the next pixel
	    }
	    // Write line to file
	    written = fwrite(buffer, sizeof(uint8_t), bytes_per_row, fp);
	    if(written != bytes_per_row) {
		fprintf(stderr, "Failed to write pixel data to file\n");
		err = TRUE;
	    }
	}
    }
    
    // Cleanup
    free(buffer);
    if(fp)
	fclose(fp);

    return !err;
	
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
	
	free(image->data);
	free(image->comment);
	free(image);
	
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