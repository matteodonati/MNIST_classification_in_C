/**
 *	Libraries.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "images_handler.h"
#include "neural_network_handler.h"


/**
 *	Functions' declaration.
 */

/* Starts training.  */
void train();

/* Starts testing. */
void test();


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

		/* Shuffle images. */
		shuffle_images();

		/* Training. */
		train();

		/* Testing. */
		test();
	
		/* Free neural network memory. */
		free_neural_network_memory();

		/* Free images memory. */
		free_images_memory();
	}
	
	/* Returning zero. */
	return 0;
}


/* Starts training. */
void train()
{
	/* Print information text. */
	printf("Training.\n");

	/* Run training for ten epochs. */
	for(int i = 0; i < 10; i++)
	{
		/* Temporary sum used to compute accuracy. */
		int correct_classifications = 0;

		/* Temporary sum used to compute error. */
		double error = 0;
		
		/* Iterate through training samples. */
		for(int j = 0; j < N_TRAINING_SAMPLES; j++)
		{
			/* Maximum value in logits array. */
			double max = 0;

			/* Index of maximum value in logits array. */
			int index_max = -1;
			
			/* Forward pass. */
			compute_forward(training_samples[j]);
	
			/* Compute error. */
			error += cross_entropy(training_samples[j][l[0].n_size]);

			/* Check if the model's prediction is correct. */
			for(int k = 0; k < l[l_size - 1].n_size; k++)
			{
				/* Compare max with l[l_size - 1].n[k].a. */
				if(max < l[l_size - 1].n[k].a)
				{
					/* Update max. */
					max = l[l_size - 1].n[k].a;

					/* Update index_max. */
					index_max = k;
				}
			}

			/* Compare index_max with label. */
			if(index_max == (int)training_samples[j][l[0].n_size])
			
				/* Update correct_classifications. */
				correct_classifications += 1;

			/* Backward pass. */
			compute_backward(training_samples[j][l[0].n_size]);

			/* Reset neural network. */
			reset_neural_network();
		}

		/* Print epoch number, accuracy and error. */
		printf("Epoch: %d, correct classifications: %d/%d, accuracy: %f, error: %f\n", i, correct_classifications, N_TRAINING_SAMPLES, (float)correct_classifications / N_TRAINING_SAMPLES, error / N_TRAINING_SAMPLES);
	}
}


/* Starts testing. */
void test()
{
	/* Print information text. */
	printf("Testing.\n");

	/* Temporary sum used to compute accuracy. */
	int correct_classifications = 0;

	/* Temporary sum used to compute error. */
	double error = 0;
		
	/* Iterate over testing_samples.. */
	for(int j = 0; j < N_TESTING_SAMPLES; j++)
	{
		/* Maximum value in logits array. */
		double max = 0;

		/* Index of maximum value in logits array. */
		int index_max = -1;
			
		/* Forward pass. */
		compute_forward(testing_samples[j]);
	
		/* Compute error. */
		error += cross_entropy(testing_samples[j][l[0].n_size]);

		/* Check if the model's prediction is correct. */
		for(int k = 0; k < l[l_size - 1].n_size; k++)
		{
			/* Compare max with l[l_size - 1].n[k].a. */
			if(max < l[l_size - 1].n[k].a)
			{
				/* Update max. */
				max = l[l_size - 1].n[k].a;

				/* Update index_max. */
				index_max = k;
			}
		}

		/* Compare index_max with label. */
		if(index_max == (int)testing_samples[j][l[0].n_size])
			
			/* Update correct_classifications. */
			correct_classifications += 1;
	}

	/* Print epoch number, accuracy and error. */
	printf("Correct classifications: %d/%d, accuracy: %f, error: %f\n", correct_classifications, N_TESTING_SAMPLES, (float)correct_classifications / N_TESTING_SAMPLES, error / N_TESTING_SAMPLES);	
}
