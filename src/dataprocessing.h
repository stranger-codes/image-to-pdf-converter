#ifndef DATAPROCESSING_H
#define DATAPROCESSING_H

// Function declarations
void processJPEGFile(const char* file);
void processPNGFile(const char* file);
const char* getEncodedImage(int index);
int getNumEncodedImages();

#endif // DATAPROCESSING_H
