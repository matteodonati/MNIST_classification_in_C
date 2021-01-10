/**
 *	Types definition.
 */

/* bias_t type. */
typedef struct bias
{
	/* Bias value. */
	float value;

	/* Derivative of the loss function with respect to the bias. */
	float dC_db;
} bias_t;

/* weight_t type. */
typedef struct weight
{
	/* Weight value. */
	float value;

	/* Derivative of the loss function with respect to the weight. */
	float dC_dw;
} weight_t;

/* neuron_t type. */
typedef struct neuron
{
	/* Weights. */
	weight_t* w;

	/* Size of weights. */
	int w_size;

	/* Bias. */
	bias_t b;

	/* z value. */
	float z;

	/* Activation value. */
	float a;

	/* Derivative of the loss function with respect to the z value. */
	float err;
} neuron_t;

/* layer_t type. */
typedef struct layer
{
	/* Array of neurons. */
	neuron_t* n;

	/* Size of n. */
	int n_size;
} layer_t;


/**
 *	Global variables.
 */

/* Array of layers. */
extern layer_t* l;

/* Size of l. */
extern int l_size;


/**
 *	Functions' declaration.
 */

/* Initializes layers, neurons, weights and biases. */
extern void init_neural_network(int, int*);

/* Frees memory. */
extern void free_neural_network_memory();
