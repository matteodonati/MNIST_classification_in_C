/**
 *	Symbolic constants.
 */

/* Number of neurons in the input layer. */
#define N_INPUT 784

/* Number of neurons in the output layer. */
#define N_OUTPUT 10

/**
 *	Types definition.
 */

/* bias_t type. */
typedef struct bias
{
	/* Bias value. */
	double value;

	/* Derivative of the loss function with respect to the bias. */
	double dC_db;
} bias_t;

/* weight_t type. */
typedef struct weight
{
	/* Weight value. */
	double value;

	/* Derivative of the loss function with respect to the weight. */
	double dC_dw;
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
	double z;

	/* Activation value. */
	double a;

	/* Derivative of the loss function with respect to the z value. */
	double err;
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

/* ReLU activation function. */
extern double relu(double);

/* Softmax activation function. */
extern void softmax();

/* Cross entropy loss function.  */
extern double cross_entropy(double);

/* Computes forward pass. */
extern void compute_forward(double*);

/* Computes backward pass. */
extern void compute_backward(double, float);

/* Reset function. */
extern void reset_neural_network();

/* Frees memory. */
extern void free_neural_network_memory();
