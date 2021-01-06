/**
 *	Libraries.
 */

#include <stdio.h>
#include "debug.h"


/**
 *	Functions' definitions.
 */

/* Prints image. */
void debug_print_image_info(float* image, float label, int width, int height)
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