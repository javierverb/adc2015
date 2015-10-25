#ifndef __HELPERS__
#define __HELPERS__

typedef unsigned char uchar;

// This function reads in a text file and stores it as a char pointer. Usage:
// const char* source = readSource("rotation.cl");
// cl_program program;
// program = clCreateProgramWithSource(context, 1, &source, NULL, NULL);
char* readSource(char* kernelPath);

// Read bmp image and convert to byte array. Also output the width and height. Usage:
// int imageHeight, imageWidth;
// const char* inputFile = "input.bmp";
// float* inputImage = readImage(inputFile, &imageWidth, &imageHeight);
// int dataSize = imageHeight*imageWidth*sizeof(float);
float* readImage(const char *filename, int* widthOut, int* heightOut);

// Writes bmp image. Usage:
// float* outputImage = NULL;
// outputImage = (float*)malloc(dataSize);
// const char* outputFile = "output.bmp";
// storeImage(outputImage, outputFile, imageHeight, imageWidth, outputFile);
void storeImage(float *imageOut, const char *filename, int rows, int cols, const char* refFilename);

#endif
