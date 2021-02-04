/**
 *	Libraries.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "images_handler.h"
#include "neural_network_handler.h"


/**
 *	Symbolic constants.
 */

#define L_ARG_INDEX 1
#define N_ARG_INDEX 3
#define ARGS_COUNT_WITHOUT_N_VALUES 8
#define ARGS_BEFORE_N_VALUES 4
#define ARGS_BEFORE_LR 6


/**
 *	Functions' declaration.
 */

/* Finds index of the maximum value in the output distribution. */
int get_predicted_output();

/* Starts training.  */
void train(int, float);

/* Starts testing. */
void test();


/**
 *	Functions' definitions.
 */

/* Main function. */
int main(int argc, char* argv[])
{
	/* Check if the number of arguments is correct. */
	if(argc - ARGS_COUNT_WITHOUT_N_VALUES != atoi(argv[L_ARG_INDEX + 1]))
		printf("Number of arguments not valid.\n");		
	
	/* Check if -l argument is correct. */
	else if(strcmp(argv[L_ARG_INDEX], "-l"))
		printf("-l argument not valid.\n");
	
	/* Check if -n argument is correct. */
	else if(strcmp(argv[N_ARG_INDEX], "-n"))
		printf("-n argument not valid.\n");

	/* Check if -e argument is correct. */
	else if(strcmp(argv[ARGS_BEFORE_N_VALUES + atoi(argv[L_ARG_INDEX + 1])], "-e"))
		printf("-e argument not valid.\n");

	/* Check if -lr argument is correct. */
	else if(strcmp(argv[ARGS_BEFORE_LR + atoi(argv[L_ARG_INDEX + 1])], "-lr"))
		printf("-lr argument not valid.\n");
	
	else
	{
		/* Number of layers (hidden layers plus input layer plus output layer). */
		int layers_number = atoi(argv[L_ARG_INDEX + 1]) + 2;

		/* Array containing the number of neurons in each layer. */
		int neurons_number[layers_number];

		/* Initialize neurons_number[0] to N_INPUT. */
		neurons_number[0] = N_INPUT;

		/* Initialize neurons_number[layers_number - 1] to N_OUTPUT. */
		neurons_number[layers_number - 1] = N_OUTPUT;

		/* Initialize every other neurons_number's element. */
		for(int i = 1; i < layers_number - 1; i++)
			neurons_number[i] = atoi(argv[i - 1 + ARGS_BEFORE_N_VALUES]);

		/* Number of epochs. */
		int epochs = atoi(argv[ARGS_BEFORE_N_VALUES + atoi(argv[L_ARG_INDEX + 1]) + 1]);

		/* Learning rate. */
		float learning_rate = atof(argv[ARGS_BEFORE_LR + atoi(argv[L_ARG_INDEX + 1]) + 1]);

		/* Initialize neural network. */
		init_neural_network(layers_number, neurons_number);
			
		/* Load data. */
		read_data();

		/* Shuffle data. */
		shuffle_data();

		/* Training. */
		train(epochs, learning_rate);

		/* Testing. */
		test();
	
		/* Free neural network memory. */
		free_neural_network_memory();

		/* Free data memory. */
		free_data_memory();
	}
	
	/* Return zero. */
	return 0;
}

/* Finds index of the maximum value in the output distribution. */
int get_predicted_output()
{
	/* Maximum value in the given array. */
	double max = 0;

	/* Index of maximum value in the given array. */
	int index = -1;
	
	/* Iterate over last layers' neurons. */
	for(int i = 0; i < l[l_size - 1].n_size; i++)

		/* Compare max with l[l_size - 1].n[i].a. */
		if(max < l[l_size - 1].n[i].a)
		{
			/* Update max. */
			max = l[l_size - 1].n[i].a;

			/* Update index. */
			index = i;
		}

	/* Return index. */
	return index;
}


/* Starts training. */
void train(int epochs, float learning_rate)
{
	/* Print information text. */
	printf("Training.\n");

	/* Run training for ten epochs. */
	for(int i = 0; i < epochs; i++)
	{
		/* Temporary sum used to compute accuracy. */
		int correct_classifications = 0;

		/* Temporary sum used to compute error. */
		double loss = 0;
		
		/* Iterate through training samples. */
		for(int j = 0; j < N_TRAINING_SAMPLES; j++)
		{			
			/* Forward pass. */
			compute_forward(training_samples[j]);
	
			/* Compute loss. */
			loss += cross_entropy(training_samples[j][l[0].n_size]);

			/* Compare the predicted output with the specific label. */
			if(get_predicted_output() == (int)training_samples[j][l[0].n_size])
			
				/* Update correct_classifications. */
				correct_classifications += 1;

			/* Backward pass. */
			compute_backward(training_samples[j][l[0].n_size], learning_rate);

			/* Reset neural network. */
			reset_neural_network();
		}

		/* Print epoch number, accuracy and error. */
		printf("Epoch: %d/%d, accuracy: %f, loss: %f\n", (i + 1), epochs, (float)correct_classifications / N_TRAINING_SAMPLES, loss / N_TRAINING_SAMPLES);
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
	double loss = 0;
		
	/* Iterate over testing_samples.. */
	for(int j = 0; j < N_TESTING_SAMPLES; j++)
	{			
		/* Forward pass. */
		compute_forward(testing_samples[j]);
	
		/* Compute error. */
		loss += cross_entropy(testing_samples[j][l[0].n_size]);

		/* Compare the predicted output with the specific label. */
		if(get_predicted_output() == (int)testing_samples[j][l[0].n_size])
			
			/* Update correct_classifications. */
			correct_classifications += 1;
	}

	/* Print epoch number, accuracy and error. */
	printf("Accuracy: %f, loss: %f\n", (float)correct_classifications / N_TESTING_SAMPLES, loss / N_TESTING_SAMPLES);	
}
