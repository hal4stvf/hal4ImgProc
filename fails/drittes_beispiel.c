#include <HsFFI.h>


#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> // something about input files
#include <sys/stat.h> /* contains constructs that facilitate getting information
	*about files attributes */

#include <jpeglib.h>

//extern JSAMPLE * image_buffer;
//extern int image_height;
//extern int image_width;

int main(int argc, char *argv[]){
	hs_init(&argc,&argv); // Haskell
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/	
/*%% 									Setup jpeg out  Part 1													%%*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/	
  char *filename = (char *)"test_jpeg.jpg";
  int quality    = 50;

  struct jpeg_compress_struct cinfo;    // Basic info for JPEG properties.
  struct jpeg_error_mgr jerr;           // In case of error.
  FILE * outfile;                       // Target file.
  JSAMPROW row_pointer[1];              // Pointer to JSAMPLE row[s].
  int row_stride;                       // Physical row width in image buffer.

  //## ALLOCATE AND INITIALIZE JPEG COMPRESSION OBJECT

  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_compress(&cinfo);

  //## OPEN FILE FOR DATA DESTINATION:

  if ((outfile = fopen(filename, "wb")) == NULL) {
    fprintf(stderr, "ERROR: can't open %s\n", filename);
    exit(1);
  }
  jpeg_stdio_dest(&cinfo, outfile);

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/	
/*%% 									Setup jpeg in Part 1														%%*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/	

	int rc, i, j;
	if (argc != 2) {
		fprintf(stderr, "USAGE: %s filename.jpg\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	// Variables for the source jpg
	struct stat file_info;
	unsigned long jpg_size;
	unsigned char *jpg_buffer;

	// Variables for the decompressor itself
	struct jpeg_decompress_struct cinfo_in;
	struct jpeg_error_mgr jerr_in;

	// Load the jpeg data from file into a memory buffer
	rc = stat(argv[1], &file_info);
	if (rc) {
		exit(EXIT_FAILURE);
	}
	jpg_size = file_info.st_size;
	jpg_buffer = (unsigned char*) malloc(jpg_size + 100);
	
	// Allocate a new decompress struct, with the default error handler.
	// The default error handler will exit() on pretty much any issue,
	// so it's likely you'll want to replace it or supplement it with
	// your own.
	cinfo_in.err = jpeg_std_error(&jerr_in);
	jpeg_create_decompress(&cinfo_in);

	//Decompressor
	jpeg_mem_src(&cinfo_in, jpg_buffer, jpg_size);

	// By calling jpeg_start_decompress, you populate cinfo_in
	// and can then allocate your output jpg buffers for
	// each scanline.
	jpeg_start_decompress(&cinfo_in);

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/	
/*%% 									Setup matrix																		%%*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/	
	cinfo.image_width = cinfo_in.output_width;
	cinfo.image_height = cinfo_in.output_height;
	cinfo.input_components = cinfo_in.output_components;
	//pixel_size = cinfo.output_components;
	// cinfo.in_color_space = JCS_RGB; 
	
  jpeg_set_defaults(&cinfo);
  jpeg_set_quality(&cinfo, quality, TRUE);

	unsigned char *image_buffer = NULL;
	// int image_size = ; 
	image_buffer = (unsigned char*) malloc(cinfo.image_width*cinfo.image_height*cinfo.num_components);

	// The row_stride is the total number of bytes it takes to store an
	// entire scanline (row).
	row_stride = cinfo.image_width * cinfo.input_components;

	while (cinfo_in.output_scanline < cinfo_in.output_height) {
		unsigned char *buffer_array[1];
		buffer_array[0] = image_buffer + \
						   (cinfo_in.output_scanline) * row_stride;

		jpeg_read_scanlines(&cinfo_in, buffer_array, 1);
	}

	jpeg_finish_decompress(&cinfo_in);
	jpeg_destroy_decompress(&cinfo_in);
	free(jpg_buffer);
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/	
/*%% 								Finish compression of processed FILE %%%*/ 
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/	
  //## START COMPRESSION:

  jpeg_start_compress(&cinfo, TRUE);
  row_stride = cinfo.image_width * 3;        // JSAMPLEs per row in image_buffer

  while (cinfo.next_scanline < cinfo.image_height)
  {
    row_pointer[0] = &image_buffer[cinfo.next_scanline * row_stride];
    (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
  }
            // NOTE: jpeg_write_scanlines expects an array of pointers to scanlines.
            //       Here the array is only one element long, but you could pass
            //       more than one scanline at a time if that's more convenient.

  //## FINISH COMPRESSION AND CLOSE FILE:

  jpeg_finish_compress(&cinfo);
  fclose(outfile);
  jpeg_destroy_compress(&cinfo);
/**************************************************************************/
// DeleteAfterUse
i = 0;
while (i < 100){
	printf("%c", image_buffer[1]);
}
	printf("\n");
/**************************************************************************/	
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/	
	free(image_buffer);
	hs_exit(); 					// Haskell	
  return 0;
}
