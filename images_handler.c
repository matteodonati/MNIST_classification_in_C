/**
 *	Libraries.
 */

#include <dirent.h>
#include <string.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "images_handler.h"


/**
 *	Global variables.
 */

/* Width, height and number of channels of a single image. */
int width, height, channels;

/* Training images. */
float* training_images[TRAINING_SAMPLES];

/* Training labels. */
float training_labels[TRAINING_SAMPLES];

/* Testing images. */
float* testing_images[TESTING_SAMPLES];

/* Testing labels. */
float testing_labels[TESTING_SAMPLES];


/**
 *	Functions' definition.
 */

/* Loads every image in the dataset. */
void read_images()
{
	/* Pointer to directory. */
	DIR *d;
	
	/* New struct dirent. */
	struct dirent *dir;
	
	/* Location of files. */
	char location[32];
	
	/* Iterate through commands. */
	for(int cmd = 0; cmd < TESTING_CMD + 1; cmd++)
	{
		/* Index of dataset array. */
		int i = 0;
		
		/* Iterate through labels. */
		for(char label = '0'; label < ':'; label++)
		{
			/* Reset of the location string. */
			reset_location(location, label, cmd);
			
			/* Opening the directory. */
			d = opendir(location);
				 
			 /* Iterate through files. */
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
							
							/* Storing image. */
							training_images[i] = read_image_from_location(location);
							
							/* Storing label. */
							training_labels[i] = (float)(label - '0');
							
							break;
						case TESTING_CMD:
						
							/* Storing image. */
							testing_images[i] = read_image_from_location(location);
							
							/* Storing label. */
							testing_labels[i] = (float)(label - '0');
						
							break;
					}
					
					/* Reset of the location string. */
					reset_location(location, label, cmd);
					
					/* Increasing index. */
					i++;
				}
					
			}
			
			/* Closing the directory. */
			closedir(d);
		}
	}
}

/* Load a single image from a specific location. */
float* read_image_from_location(char* location)
{
	/* Image reading. The dataset contains RGB images. These need to be copied to a single-channel buffer. */
	uint8_t* tmp_rgb_image = stbi_load(location, &width, &height, &channels, 0);
	
	/* Allocation of image. */
	float* image = (float*)malloc(width * height * sizeof(float));
	
	/* Parsing of the three-channels image. */
	for(int i = 0; i < width * height * channels; i++)
		if(i % 3 == 0)
			image[i / 3] = (float)tmp_rgb_image[i] / 255;
	
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

/* Deallocates memory. */
void free_images_memory()
{	
	/* Freeing each element of training_images. */
	for(int i = 0; i < TRAINING_SAMPLES; i++)
		free(training_images[i]);
	
	/* Freeing each element of testing_images. */
	for(int i = 0; i < TESTING_SAMPLES; i++)
		free(testing_images[i]);
}