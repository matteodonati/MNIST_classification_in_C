/**
 *	Libraries.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "neural_network_handler.h"


/**
 *	Global variables.
 */

/* Array of layers. */
layer_t* l;

/* Size of l. */
int l_size;


/**
 *	Functions' definition.
 */

/* Initializes layers, neurons, weiights and biases. */
void init_neural_network(int layers_number, int* neurons_number)
{
	/* Set the specific l_size; */
	l_size = layers_number;

	/* Allocating memory for layers array. */
	l = (layer_t*)malloc(l_size * sizeof(layer_t));

	/* Initializing seed. */
	srand(time(NULL));

	/* Allocating memory for neurons and weights. */
	for(int i = 0; i < l_size; i++)
	{	
		/* Set the specific n_size. */
		l[i].n_size = neurons_number[i];

		/* Neurons. */
		l[i].n = (neuron_t*)malloc(l[i].n_size * sizeof(neuron_t));

		/* Allocate memory for each neuron in the ith layer. */
		for(int j = 0; j < l[i].n_size; j++)
		{
			/* Check if there exist an i + 1 layer. */
			if(i < l_size - 1)
			{
				/* Set the specific w_size. */
				l[i].n[j].w_size = neurons_number[i + 1];
	
				/* Weights.  */
				l[i].n[j].w = (weight_t*)malloc(l[i].n[j].w_size * sizeof(weight_t));

				/* Initializing weights. */
				for(int k = 0; k < l[i].n[j].w_size; k++)
				{
					l[i].n[j].w[k].value = ((float)rand() / (float)((unsigned)RAND_MAX + 1) * 2) - 1;
				}
			}

			/* Initializing biases. */
			l[i].n[j].b.value = ((float)rand() / (float)((unsigned)RAND_MAX + 1) * 2) - 1;
		}
	}
}

/* Frees memory. */
void free_neural_network_memory()
{
	/* Free l, n, w. */
	for(int i = 0; i < l_size; i++)
	{
		/* Free w. */
		for(int j = 0; j < l[i].n_size; j++)
		{
			/* Check if there exist an i + 1 layer. */
			if(i < l_size - 1)
			{
				/* Free w. */
				free(l[i].n[j].w);
			}
		}

		/* Free n. */
		free(l[i].n);
	}

	/* Free l. */
	free(l);
}
