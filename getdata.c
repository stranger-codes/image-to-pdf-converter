#include <stdio.h>
#include <string.h>
#include <jpeglib.h>
#include <png.h>
#include <ctype.h>

#define MAX_FILES 10
#define MAX_FILENAME_LENGTH 200

typedef enum {
    JPEG_FILE,
    PNG_FILE,
    UNKNOWN_FILE
} FileType;


#define MAX_FILES 10

int getfilenum(char files[][MAX_FILENAME_LENGTH]) {
    int numFiles = 0;
    char filename[MAX_FILENAME_LENGTH];

    // Input the filenames
    printf("Enter the filenames (including the extension):\n");

    // Read filenames until "stop" is entered or the maximum number of files is reached
    for (int i = 0; i < MAX_FILES; i++) {
        printf("File %d (or enter 'stop' to finish): ", i + 1);
        fgets(filename, sizeof(filename), stdin);

        // Remove the newline character from the end of the string
        filename[strcspn(filename, "\n")] = '\0';
        printf("Filename: %s\n", filename);
        // Check if the entered filename is "stop"
        if (strcmp(filename, "stop") == 0) {
            break;
        }

        // Copy the filename into the files array
        strncpy(files[i], filename, MAX_FILENAME_LENGTH - 1);
        files[i][MAX_FILENAME_LENGTH - 1] = '\0';  // Ensure null-termination

        numFiles++;
    }
    for (int i = 0; i < numFiles; i++) {
    printf("File %d: %s\n", i + 1, files[i]);}


    return numFiles;
}


int isSupportedFileType(const char* filename) {
    const char* supportedFileExtensions[] = {".jpg", ".jpeg", ".png"};
    int numSupportedFileExtensions = sizeof(supportedFileExtensions) / sizeof(supportedFileExtensions[0]);

    const char* extension = strrchr(filename, '.');
    if (extension == NULL) {
        printf("Extension not found: %s\n", filename);
        return 0;
    }

    printf("Checking file extension: %s\n", extension);

    for (int i = 0; i < numSupportedFileExtensions; i++) {
        if (strcasecmp(extension, supportedFileExtensions[i]) == 0) {
            return 1;
        }
    }


    printf("Unsupported file: %s\n", filename);
    printf("Please choose different files with supported extensions (.jpg, .jpeg, .png).\n");

    return 0;
}



int getdata(const char* files[], int numFiles) {
    printf("files[0]: %s\n", files[0]);

    for (int i = 0; i < numFiles; i++) {
        const char* file = files[i];

        printf("Processing file: %s\n", file); // Print the filename for verification

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
                // Process JPEG file
                printf("Processing JPEG file: %s\n", file);
                // Add code here to handle JPEG file processing
                break;
            case PNG_FILE:
                // Process PNG file
                printf("Processing PNG file: %s\n", file);
                // Add code here to handle PNG file processing
                break;
            default:
                break;
        }
    }

    printf("Finished processing files.\n");

    // Continue with other operations or return success
    return 0;
}



