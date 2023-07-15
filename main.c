#include <stdio.h>
#include <string.h>
#include "getdata.h"

int main() {
    char files[MAX_FILES][100];
    int numFiles;

    numFiles = getfilenum(files);
    printf("getfilenum completed successfully.\n");
    for (int i = 0; i < numFiles; i++) {
    printf("File %d: %s\n", i + 1, files[i]);}

    for (int i = 0; i < numFiles; i++) {
        if (!isSupportedFileType(files[i])) {
            printf("Unsupported file: %s\n", files[i]);
            printf("Please choose different files with supported extensions (.jpg, .jpeg, .png).\n");
            return -1;
        }
    }
    printf("isSupportedFileType completed successfully.\n");

    printf("files[0]: %s\n", files[0]);
    
    for (int i = 0; i < numFiles; i++) {
    printf("File %d: %s\n", i + 1, files[i]);}

    if (getdata((const char**)files, numFiles) == 0) {
        printf("Data retrieval and processing completed successfully.\n");
    } else {
        printf("Failed to retrieve and process data.\n");
    }
    printf("getdata completed successfully.\n");

    return 0;
}
