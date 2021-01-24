/**
 *	Libraries.
 */

#include <stdlib.h>
#include <time.h>
#include <math.h>
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
		for(int j = 0; i > 0 && j < l[i].n_size; j++)
		{
			/* Set the specific w_size. */
			l[i].n[j].w_size = neurons_number[i - 1];
	
			/* Weights.  */
			l[i].n[j].w = (weight_t*)malloc(l[i].n[j].w_size * sizeof(weight_t));

			/* Initializing weights. */
			for(int k = 0; k < l[i].n[j].w_size; k++)
				l[i].n[j].w[k].value = ((float)rand() / (float)((unsigned)RAND_MAX + 1) * 2) - 1;

			/* Initializing biases. */
			l[i].n[j].b.value = ((float)rand() / (float)((unsigned)RAND_MAX + 1) * 2) - 1;
		}
	}
}

/* ReLU activation function.  */
float relu(float input)
{
	/* Returns ReLU's output. */
	return (input > 0 ? input : 0);
}

/* Softmax activation function. */
void softmax()
{
	/* Sum of logits. */
	float logits_sum = 0;

	/* Compute sum of logits. */
	for(int i = 0; i < l[l_size - 1].n_size; i++)
		logits_sum += exp(l[l_size - 1].n[i].z);

	/* Compute each element of the distribution. */
	for(int i = 0; i < l[l_size - 1].n_size; i++)
		l[l_size - 1].n[i].a = exp(l[l_size - 1].n[i].z) / logits_sum;
}

/* Cross entropy loss function.  */
float cross_entropy(float label)
{
	/* Loss value. */
	float loss = 0;

	/* Compute loss. */
	for(int i = 0; i < l[l_size - 1].n_size; i++)
		
		/* Check if i is equal to label. */
		if(i == (int)label)

			/* Update loss. */
			loss += log(l[l_size - 1].n[i].a) / log(2);

	/* Return loss value. */
	return (loss * (-1));
}

/* Computes forward pass. */
void compute_forward(float* image)
{
	/* Copy image to input layer. */
	for(int i = 0; i < l[0].n_size; i++)
		l[0].n[i].a = image[i];

	/* Iterate through the remaining layers. */
	for(int i = 1; i < l_size; i++)
	{
		/* Compute z values and a values. */
		for(int j = 0; j < l[i].n_size; j++)
		{
			/* Compute z for each neuron. */
			for(int k = 0; k < l[i].n[j].w_size; k++)
				l[i].n[j].z += l[i].n[j].w[k].value * l[i - 1].n[k].a;
				
			/* Add the bias to z. */
			l[i].n[j].z += l[i].n[j].b.value;

			/* Check if current layer is not output layer. */
			if(i != l_size - 1)

				/* Compute a for each neuron. */
				l[i].n[j].a = relu(l[i].n[j].z);
		}
	}

	/* Compute a for the output layer. */
	softmax();
}

/* Computes backward pass. */
void compute_backward(float label)
{
	/* Compute output layer's error. */
	for(int i = 0; i < l[l_size - 1].n_size; i++)

		/* delta^L = a^L - y. */
		l[l_size - 1].n[i].err = l[l_size - 1].n[i].a - (i == (int)label ? 1 : 0);

	/* Compute hidden layers' error. */
	for(int i = l_size - 2; i > 0; i--)
	{
		/* Iterate through neurons of the (i + 1)th layer. */
		for(int j = 0; j < l[i + 1].n_size; j++)

			/* Iterate through weights of the (i + 1)th layer. */
			for(int k = 0; k < l[i + 1].n[j].w_size; k++)

				/* Compute partial error. */
				l[i].n[k].err += l[i + 1].n[j].w[k].value * l[i + 1].n[j].err;

		/* Iterate through neurons of the ith layer. */
		for(int j = 0; j < l[i].n_size; j++)

			/* delta^l = (delta^(i + 1) * (w^(i + 1)^T) Hadamard ReLU'(z^l)) */
			l[i].n[j].err *= (l[i].n[j].z < 0 ? 0 : 1);
	}

	/* Compute dC_db and update bias, compute dC_dw and update weights. Iterate through layers. */
	for(int i = 1; i < l_size; i++)

		/* Iterate through neurons. */
		for(int j = 0; j < l[i].n_size; j++)
		{
			/* dC_db^l_j = delta^l_j. */
			l[i].n[j].b.dC_db = l[i].n[j].err;

			/* Update bias. */
			l[i].n[j].b.value -= ETA * l[i].n[j].b.dC_db;

			/* Iterate through weights. */
			for(int k = 0; k < l[i].n[j].w_size; k++)
			{
				/* dC_dw^l_jk = a^(l - 1)_k * err^l_j. */
				l[i].n[j].w[k].dC_dw = l[i - 1].n[k].a * l[i].n[j].err;

				/* Update weight. */
				l[i].n[j].w[k].value -= ETA * l[i].n[j].w[k].dC_dw; 
			}
		}
}

/* Reset function.  */
void reset_neural_network()
{
	/* Iterate through layers. */
	for(int i = 0; i < l_size; i++)

		/* Iterate through neurons. */
		for(int j = 0; j < l[i].n_size; j++)
		{
			/* Reset z, a. */
			l[i].n[j].z = 0;
			l[i].n[j].a = 0;

			/* Reset dC_db. */
			l[i].n[j].b.dC_db = 0;

			/* Iterate through weights. */
			for(int k = 0; k < l[i].n[j].w_size; k++)

				/* Reset dC_dw. */
				l[i].n[j].w[k].dC_dw = 0;
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

			/* Check if there exist an i + 1 layer. */
			if(i < l_size - 1)

				/* Free w. */
				free(l[i].n[j].w);

		/* Free n. */
		free(l[i].n);
	}

	/* Free l. */
	free(l);
}
