/**
 *	Libraries.
 */

#include <stdio.h>
#include "images_handler.h"


/**
 *	Functions' declaration.
 */

/* Prints image. */
void debug_print_image_info(float*, float);


/**
 *	Functions' definitions.
 */

/* Main function. */
int main(int argc, char** argv)
{
	/* Loading images. */
	read_images();
	
	/* Print image. */
	debug_print_image_info(training_images[0], training_labels[0]);
	
	/* Free all allocated memory. */
	free_images_memory();
	
	/* Returning zero. */
	return 0;
}

/* Prints image. */
void debug_print_image_info(float* image, float label)
{
	/* Print label. */
	printf("Label: %d", (int)label);
	
	/* Print image. */
	for(int i = 0; i < width * height; i++)
	{
		if(i % width == 0)
			printf("\n");
		
		printf("%0.1f", image[i]);
	}
}