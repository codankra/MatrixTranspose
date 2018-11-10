#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>

int main(int argc, char **argv){
	srand((unsigned int)time(NULL));
	// argv:  program_name matrix_height matrix_width block_width
	if (argc != 4){ 
		//Describe usage of program
		fprintf(stderr, 
			"Wrong number of command-line arguments\n");
		fprintf(stderr, 
			"Usage: program_name matrix_height matrix_width block_width\n");
		return -1;
	}
	struct timeval t0, t1;
	gettimeofday(&t0, 0); //Start timer

	int mHeight = atoi(argv[1]);
	int mWidth = atoi(argv[2]);
	int blockW = atoi(argv[3]);
	int matsize = mWidth * mHeight;
	float *matrix = (float*)(malloc(sizeof(float) * (matsize))); //might need +1 for termination
	float *output = (float*)(malloc(sizeof(float) * (matsize)));
	if(matrix == NULL){
		perror("malloc"); //Not malloc'd
		exit(0);
	}
	for (int i = 0; i < matsize; i++){
		//Generate random numbers [0, 200] then subtract by 100.
		float randNum = (float)((((double)rand()/(double)(RAND_MAX)) * 200.0) - 100.0);
		matrix[i] = randNum;
	}
	int outputPos, matrixPos, i, j, z, k;
	
	
	for (k = 0; k < ceil(((float)mHeight)/((float)blockW)); k++){
		for (z = 0; z < ceil(((float)mWidth)/((float)blockW)); z++){
		//for all blocks
			for (i = 0; i < blockW; i++){
			//for all rows in block
				for(j = 0; j < blockW; j++){
				//for all cols in block
					if (k*blockW + i >= mHeight){
						i = blockW;
						j = blockW;
						//Out of height bound
						//printf("Out of height bound\n");
					}
					else if (z*blockW + j >= mWidth){
						j = blockW; //Out of width bound
						//printf("Out of width bound\n");
					}
					else{
						outputPos = (z*blockW * mHeight)+(k*blockW)+(j*mHeight + i);
						matrixPos = (k*blockW * mWidth)+(z*blockW)+(i*mWidth + j);
						//Height of above block(s)*rowsize * (width of left blocks) + (row, column)
						output[outputPos] = matrix[matrixPos];
					}
					
				}
			}
		}
	}
	

	//FREE / CLOSE (✓)
	free(matrix);
	free(output);
	//WOW I added this in a branch
	//The commits before this are me figuring out how to use branches... feel free to disregard

	gettimeofday(&t1, 0); //End timer
	long elapsedMs = (t1.tv_sec-t0.tv_sec)*1000000 + t1.tv_usec-t0.tv_usec;
	int elapsed = t1.tv_sec-t0.tv_sec;
	printf("Microseconds: %lu\nSeconds: %i\n", elapsedMs, elapsed);
}