#ifndef GETDATA_H
#define GETDATA_H
#define MAX_FILES 10  // Define the maximum number of files

int getfilenum(char files[][100]);
int isSupportedFileType(const char* filename);
int getdata(const char* files[], int numFiles);

#endif  // GETDATA_H
