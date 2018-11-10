#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

int main(int argc, char **argv){
	srand((unsigned int)time(NULL));
	// argv:  program_name matrix_width block_width
	if (argc != 3){ 
		//Describe usage of program
		fprintf(stderr, 
			"Wrong number of command-line arguments\n");
		fprintf(stderr, 
			"Usage: program_name matrix_width block_width\n");
		return -1;
	}
	struct timeval t0, t1;
	gettimeofday(&t0, 0); //Start timer

	int rowsize = atoi(argv[1]);
	int blockW = atoi(argv[2]);
	int matsize = rowsize * rowsize;
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
	
	for (k = 0; k < rowsize/blockW; k++){
		for (z = 0; z < rowsize/blockW; z++){
		//for all blocks
			for (i = 0; i < blockW; i++){
			//for all rows in block
				for(j = 0; j < blockW; j++){
				//for all cols in block
					outputPos = (z*blockW * rowsize)+(k*blockW)+(j*rowsize + i);
					matrixPos = (k*blockW * rowsize)+(z*blockW)+(i*rowsize + j);
					//Height of above block(s)*rowsize * (width of left blocks) + (row, column)
					output[outputPos] = matrix[matrixPos];
				}
			}
		}
	}
	//FREE / CLOSE (✓)
	free(matrix);
	free(output);

	gettimeofday(&t1, 0); //End timer
	long elapsedMs = (t1.tv_sec-t0.tv_sec)*1000000 + t1.tv_usec-t0.tv_usec;
	long elapsed = t1.tv_sec-t0.tv_sec;
	printf("Microseconds: %lu\nSeconds: %lu\n", elapsedMs, elapsed);
}