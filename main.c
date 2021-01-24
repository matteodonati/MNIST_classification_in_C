/**
 *	Libraries.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "images_handler.h"
#include "neural_network_handler.h"


/**
 *	Functions' definitions.
 */

/* Main function. */
int main(int argc, char* argv[])
{
	/* Check if argc is less than eleven (minimum number of arguments required). */
	if(argc < 7)
		printf("Too few arguments.\n");
	
	/* Check if -l argument is correct. */
	else if(strcmp(argv[1], "-l"))
		printf("-l argument not correct.\n");
	
	/* Check if -n argument is correct. */
	else if(strcmp(argv[3], "-n"))
		printf("-n argument not correct.\n");
	
	/* Check if the number of arguments is correct. */
	else if(atoi(argv[2]) != argc - 4)
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

		/* Example: load training_images[0] and train for five epochs. */
		for(int i = 0; i < 50; i++)
		{
			/* Forward pass. */
			compute_forward(training_images[0]);

			/* Print epoch number. */
			printf("Epoch: %d\n", i);

			/* Print output distribution. */
			for(int i = 0; i < l[l_size - 1].n_size; i++)
				printf("y[%d]: %f.\n", i, l[l_size - 1].n[i].a);

			/* Print error. */
			printf("Error: %f.\n\n", cross_entropy(training_labels[0]));

			/* Backward pass. */
			compute_backward(training_labels[0]);

			/* Reset neural network. */
			reset_neural_network();
		}
	
		/* Free neural network memory. */
		free_neural_network_memory();

		/* Free images memory. */
		free_images_memory();
	}
	
	/* Returning zero. */
	return 0;
}
