#include <stdio.h>
#include <string.h>
#include "getdata.h"  // Include the header file that declares the functions

int main() {
    char files[MAX_FILES][100];
    int numFiles;

    // Call the getfilenum function to get the number of files and populate the files array
    numFiles = getfilenum(files);

    // Check if all files have supported file extensions using the isSupportedFileType function
    for (int i = 0; i < numFiles; i++) {
        if (!isSupportedFileType(files[i])) {
            printf("Unsupported file: %s\n", files[i]);
            printf("Please choose different files with supported extensions (.jpg, .jpeg, .png).\n");
            return -1;
        }
    }

    // Call the getdata function to process the files
    if (getdata((const char**)files, numFiles) == 0) {
        printf("Data retrieval and processing completed successfully.\n");
    } else {
        printf("Failed to retrieve and process data.\n");
    }

    return 0;
}

