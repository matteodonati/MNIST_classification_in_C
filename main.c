/**
 *	Libraries.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "images_handler.h"
#include "debug.h"


/**
 *	Functions' definitions.
 */

/* Main function. */
int main(int argc, char* argv[])
{
	/* Check if argc is less than eleven (minimum number of arguments required). */
	if(argc < 11)
		printf("Too few arguments.\n");
	
	/* Check if -l argument is correct. */
	else if(strcmp(argv[1], "-l"))
		printf("-l argument not correct.\n");
	
	/* Check if -n argument is correct. */
	else if(strcmp(argv[3], "-n"))
		printf("-n argument not correct.\n");
	
	/* Check if -a argument is correct. */
	else if(strcmp(argv[3 + atoi(argv[2]) + 1], "-a"))
		printf("-a argument not correct.\n");
	
	/* Check if the number of arguments is correct. */
	else if(atoi(argv[2]) != argc - 8)
		printf("Number of argument not correct.\n");		
	
	else
	{
		/* Loading images. */
		read_images();
		
		/* Print image. */
		debug_print_image_info(training_images[0], training_labels[0], width, height);
		
		/* Free all allocated memory. */
		free_images_memory();
	}
	
	/* Returning zero. */
	return 0;
}