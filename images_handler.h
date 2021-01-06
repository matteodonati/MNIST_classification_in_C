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
#define TRAINING_SAMPLES 50

/* Number of testing samples. */
#define TESTING_SAMPLES 10


/**
 *	Global variables.
 */

/* Width, height and number of channels of a single image. */
extern int width, height, channels;

/* Training images. */
extern float* training_images[];

/* Training labels. */
extern float training_labels[];

/* Testing images. */
extern float* testing_images[];

/* Testing labels. */
extern float testing_labels[];


/**
 *	Functions' declarations.
 */

/* Loads every image in the dataset. */
extern void read_images();

/* Load a single image from a specific location. */
extern float* read_image_from_location(char*);

/* Resets the location string. */
extern void reset_location(char*, char, int);

/* Deallocates memory. */
extern void free_images_memory();