#ifndef GETDATA_H
#define GETDATA_H

#define MAX_FILES 10          // Define the maximum number of files
#define MAX_FILENAME_LENGTH 200 // Define the maximum length of the filename

int getfilenum(char files[][MAX_FILENAME_LENGTH]);
int isSupportedFileType(const char* filename);
int processdata(char files[][MAX_FILENAME_LENGTH], int numFiles);

#endif  // GETDATA_H

