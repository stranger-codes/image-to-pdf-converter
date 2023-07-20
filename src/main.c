#include <stdio.h>
#include <string.h>
#include "getdata.h"
#include "dataprocessing.h"

int main() {
    char files[MAX_FILES][MAX_FILENAME_LENGTH] = {0}; // Initialize the array with zeros

    int numFiles = getfilenum(files);
    printf("getfilenum completed successfully.\n");

    for (int i = 0; i < numFiles; i++) {
        printf("File %d: %s\n", i + 1, files[i]);
    }

    for (int i = 0; i < numFiles; i++) {
        if (!isSupportedFileType(files[i])) {
            printf("Unsupported file: %s\n", files[i]);
            printf("Please choose different files with supported extensions (.jpg, .jpeg, .png).\n");
            return -1;
        }
    }
    printf("isSupportedFileType completed successfully.\n");
    for (int i = 0; i < numFiles; i++) {
        printf("File %d: %s\n", i + 1, files[i]);
    }

    // Process data and store the encoded images
    processdata(files, numFiles); // This will encode the images and store them in the Encoded_Images array.
    
    for (int i = 0; i < numFiles; i++) {
        printf("File %d: %s\n", i + 1, files[i]);
    }
    
    // Print or use the encoded images as needed
    printf("Encoded Images:\n");
    int numEncodedImages = getNumEncodedImages();
    for (int i = 0; i < numEncodedImages; i++) {
        const char* encodedImage = getEncodedImage(i);
        printf("Encoded Image %d:\n%s\n", i + 1, encodedImage);
    }

    printf("getdata completed successfully.\n");

    return 0;
}
