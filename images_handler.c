/**
 *	Libraries.
 */

#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "images_handler.h"


/**
 *	Global variables.
 */

/* Width, height and number of channels of a single image. */
int width, height, channels;

/* Training samples. */
double* training_samples[N_TRAINING_SAMPLES];

/* Testing samples. */
double* testing_samples[N_TESTING_SAMPLES];


/**
 *	Functions' definition.
 */

/* Loads every image in the dataset. */
void read_data()
{
	/* Pointer to directory. */
	DIR *d;
	
	/* New struct dirent. */
	struct dirent *dir;
	
	/* Location of files. */
	char location[32];
	
	/* Iterate over commands. */
	for(int cmd = 0; cmd < TESTING_CMD + 1; cmd++)
	{
		/* Index of dataset array. */
		int i = 0;
		
		/* Iterate over labels. */
		for(char label = '0'; label < ':'; label++)
		{
			/* Reset of the location string. */
			reset_location(location, label, cmd);

			/* Print the name of the current direcotyr. */
			printf("Reading %s files.\n", location);
			
			/* Open the directory. */
			d = opendir(location);
				 
			/* Iterate over files. */
			while((dir = readdir(d)) != NULL)
			{
				/* Check if dir points to a regular file. */
				if(strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0)
				{
					/* Concatenation of location and dir->d_name. */
					strcat(location, dir->d_name);
					
					/* Store image and label based on cmd. */
					switch(cmd)
					{
						case TRAINING_CMD:
							
							/* Store image and label. */
							training_samples[i] = read_image_from_location(location, label); 
							
							break;

						case TESTING_CMD:
						
							/* Store image and label. */
							testing_samples[i] = read_image_from_location(location, label);
						
							break;
					}
					
					/* Reset of the location string. */
					reset_location(location, label, cmd);
					
					/* Increase index. */
					i++;
				}
					
			}
			
			/* Close the directory. */
			closedir(d);
		}
	}
}

/* Load a single image from a specific location. */
double* read_image_from_location(char* location, char label)
{
	/* Image reading. The dataset contains RGB images. These need to be copied to a single-channel buffer. */
	uint8_t* tmp_rgb_image = stbi_load(location, &width, &height, &channels, 0);
	
	/* Allocation of image. */
	double* image = (double*)malloc((width * height + 1) * sizeof(double));
	
	/* Parsing of the three-channels image. */
	for(int i = 0; i < width * height * channels; i++)
	{
		if(i % 3 == 0)
		{
			image[i / 3] = (double)tmp_rgb_image[i] / 255;
		}
	}

	/* Add label as last element of image. */
	image[width * height] = (double)(label - '0');
	
	/* Deallocation of tmp_rgb_image. */
	stbi_image_free(tmp_rgb_image);
	
	/* Returning image. */
	return image;
}

/* Resets the location string. */
void reset_location(char* location, char label, int cmd)
{
	/* Length of training or testing directory. */
	size_t len;
	
	/* Location reset based on cmd. */
	switch(cmd)
	{
		case TRAINING_CMD:
			
			/* Copy of TRAINING_DIR into location. */
			strcpy(location, TRAINING_DIR); 
			
			/* Get size of TRAINING_DIR. */
			len = strlen(TRAINING_DIR);
			
			break;

		case TESTING_CMD:
		
			/* Copy of TESTING_DIR into location. */
			strcpy(location, TESTING_DIR);
			
			/* Get size of TESTING_DIR. */
			len = strlen(TESTING_DIR);
			
			break;
	}
	
	/* Concatenation of the label character. */
	location[len] = label;
	
	/* Concatenation of the separator character. */
	location[len + 1] = '/';
	
	/* Concatenation of the null-terminator. */
	location[len + 2] = '\0';
}

/* Shuffles images. */
void shuffle_data()
{
	/* Print information message. */
	printf("Shuffling samples.\n");

	/* Temporary index. */
	int tmp_index;

	/* Temporary image. */
	double tmp_image[width * height + 1];

	/* Initialize seed. */
	srand(time(NULL));

	/* Shuffle images. */
	for(int i = 0; i < N_TRAINING_SAMPLES - 1; i++)
	{
		/* Generate tmp_index. */
		tmp_index = i + rand() / (RAND_MAX / (N_TRAINING_SAMPLES - i) + 1);

		/* Copy training_samples[tmp_index] into tmp_image. */
		for(int j = 0; j < width * height + 1; j++)
		{
			tmp_image[j] = training_samples[tmp_index][j];
		}

		/* Copy training_samples[i] into training_samples[tmp_index]. */
		for(int j = 0; j < width * height + 1; j++)
		{
			training_samples[tmp_index][j] = training_samples[i][j];
		}

		/* Copy tmp_image into training_samples[i]. */
		for(int j = 0; j < width * height + 1; j++)
		{
			training_samples[i][j] = tmp_image[j];
		}
	}
}

/* Deallocates memory. */
void free_data_memory()
{	
	/* Free each element of training_samples. */
	for(int i = 0; i < N_TRAINING_SAMPLES; i++)
	{
		free(training_samples[i]);
	}
	
	/* Free each element of testing_samples. */
	for(int i = 0; i < N_TESTING_SAMPLES; i++)
	{
		free(testing_samples[i]);
	}
}
