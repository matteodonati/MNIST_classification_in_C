/**
 *	Symbolic constants.
 */

/* Location of the training images. */					
#define TRAINING_DIR "./dataset/training/"

/* Location of the testing images. */
#define TESTING_DIR "./dataset/testing/"

/* Constant associated with training. */
#define TRAINING_CMD 0

/* Constant associated with testing. */
#define TESTING_CMD 1

/* Number of training samples. */
#define N_TRAINING_SAMPLES 60000

/* Number of testing samples. */
#define N_TESTING_SAMPLES 10000


/**
 *	Global variables.
 */

/* Width, height and number of channels of a single image. */
extern int width, height, channels;

/* Training samples. */
extern double* training_samples[];

/* Testing samples. */
extern double* testing_samples[];


/**
 *	Functions' declarations.
 */

/* Loads every image in the dataset. */
extern void read_data();

/* Load a single image from a specific location. */
extern double* read_image_from_location(char*, char);

/* Resets the location string. */
extern void reset_location(char*, char, int);

/* Shuffles images. */
extern void shuffle_data();

/* Deallocates memory. */
extern void free_data_memory();
