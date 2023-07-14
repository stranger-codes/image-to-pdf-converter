#include <stdio.h>
#include <string.h>
#include <jpeglib.h>
#include <png.h>

#define MAX_FILES 10

typedef enum {
    JPEG_FILE,
    PNG_FILE,
    UNKNOWN_FILE
} FileType;

int getfilenum(char files[][100]) {
    int numFiles = 0;

    // Input the filenames
    printf("Enter the filenames (including the extension):\n");

    // Read filenames until maximum number of files is reached
    while (numFiles < MAX_FILES) {
        printf("File %d (or enter blank to finish): ", numFiles + 1);
        scanf("%s", files[numFiles]);

        // Check if the entered filename is blank (empty string)
        if (strcmp(files[numFiles], "") == 0) {
            break;
        }

        numFiles++;
    }

    return numFiles;
}

int isSupportedFileType(const char* filename) {
    const char* supportedFileExtensions[] = {".jpg", ".jpeg", ".png"};
    int numSupportedFileExtensions = sizeof(supportedFileExtensions) / sizeof(supportedFileExtensions[0]);

    const char* extension = strrchr(filename, '.');
    if (extension == NULL) {
        return 0;
    }

    for (int i = 0; i < numSupportedFileExtensions; i++) {
        if (strcmp(extension, supportedFileExtensions[i]) == 0) {
            return 1;
        }
    }

    return 0;
}

int getdata(const char* files[], int numFiles) {
    // Validate the number of files
    if (numFiles < 1 || numFiles > MAX_FILES) {
        printf("Invalid number of files. Please provide between 1 and %d files.\n", MAX_FILES);
        return -1;
    }

    // Check if all files have supported file extensions
    for (int i = 0; i < numFiles; i++) {
        const char* file = files[i];

        if (!isSupportedFileType(file)) {
            printf("Unsupported file: %s\n", file);
            printf("Please choose different files with supported extensions (.jpg, .jpeg, .png).\n");
            return -1;
        }

        // Process the file based on its type
        FileType fileType = UNKNOWN_FILE;
        if (strstr(file, ".jpg") || strstr(file, ".jpeg")) {
            fileType = JPEG_FILE;
        } else if (strstr(file, ".png")) {
            fileType = PNG_FILE;
        }

        switch (fileType) {
            case JPEG_FILE:
                // Use jpeglib to encode JPEG
                printf("Processing JPEG file: %s\n", file);
                // Add code here to handle JPEG file processing with jpeglib
                break;
            case PNG_FILE:
                // Use pnglib to encode PNG
                printf("Processing PNG file: %s\n", file);
                // Add code here to handle PNG file processing with pnglib
                break;
            default:
                break;
        }
    }

    // Continue with other operations or return success
    return 0;
}
