/**
 *	Libraries.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "images_handler.h"
#include "debug.h"
#include "neural_network_handler.h"


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
		/* Number of layers. */
		int layers_number = atoi(argv[2]);

		/* Array containing the number of neurons in each layer. */
		int neurons_number[layers_number];

		/* Initialize neurons_number. */
		for(int i = 0; i < layers_number; i++)
			neurons_number[i] = atoi(argv[i + 4]);

		/* Initialize neural network. */
		init_neural_network(layers_number, neurons_number);
			
		/* Load images. */
		read_images();
	
		/* Free neural network memory. */
		free_neural_network_memory();

		/* Free all allocated memory. */
		free_images_memory();
	}
	
	/* Returning zero. */
	return 0;
}
