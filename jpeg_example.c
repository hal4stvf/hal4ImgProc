/*
 * example.c angepasst von der ljpeg 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jpeglib.h"


#include <setjmp.h>


/*
 * gray imread 
 */


GLOBAL(int)
read_JPEG_file (char * filename) 
{
  struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr err;

	cinfo.err = jpeg_std_error( &err );
  /* More stuff */
  FILE * infile;		/* source file */
//  JSAMPARRAY buffer;		/* Output row buffer */
  int row_stride;		/* physical row width in output buffer */

  if ((infile = fopen(filename, "rb")) == NULL) {
    fprintf(stderr, "can't open %s\n", filename);
    return 0;
  }

  /* Step 1: allocate and initialize JPEG decompression object */

  /* Now we can initialize the JPEG decompression object. */
  jpeg_create_decompress(&cinfo); // initialize JPEG decompression

  /* Step 2: specify data source (eg, a file) */

  jpeg_stdio_src(&cinfo, infile);

  /* Step 3: read file parameters with jpeg_read_header() */

  (void) jpeg_read_header(&cinfo, TRUE); // Nötig?

  /* Step 4: set parameters for decompression */


  /* Step 5: Start decompressor */

  (void) jpeg_start_decompress(&cinfo);

  /* JSAMPLEs per row in output buffer */
  row_stride = cinfo.output_width * cinfo.output_components;
	
	/* Initializiert */
	int w = cinfo.output_width;
	int h = cinfo.output_height;
	int numChannels = cinfo.num_components;
	unsigned long dataSize = w*h*numChannels;

	unsigned char* data = (unsigned char*) malloc(dataSize);
	unsigned char* rowptr;
	while (cinfo.output_scanline <h)
	{
		rowptr = data + cinfo.output_scanline*w*numChannels;		
		jpeg_read_scanlines(&cinfo,&rowptr,1);
	}


  /* Step 7: Finish decompression */

  (void) jpeg_finish_decompress(&cinfo);

  /* Step 8: Release JPEG decompression object */

  /* This is an important step since it will release a good deal of memory. */
  jpeg_destroy_decompress(&cinfo);

  fclose(infile);

  /* And we're done! */
  return 1;
}

int main(int argc, char* argv[]){

	read_JPEG_file(argv[1]);
	return 0;
}
