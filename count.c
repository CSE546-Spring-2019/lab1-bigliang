#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[])
{

    if ( argc < 4) {
        printf("Missing parameters! Please provide three parameters");
        exit(1);
    }
    if (argc > 4) {
        printf("Too many parameters! Please provide three parameters");
        exit(1);
    }
    FILE *inputFile; // File to Search
    FILE *outputFile; // File to write output
    if ((inputFile = fopen(argv[1],"rb")) == NULL) {
        printf("Can't open file %s \n", argv[1]);
        printf("The program will exit, please rerun it with correct input file name \n");
        return 0;
    }
    if ((outputFile = fopen(argv[3],"wb+")) == NULL) {
        printf("Can't open file %s \n", argv[3]);
        printf("The program will exit, please rerun it with correct output file name \n");
        return 0;
    }

    int len = (int)strlen(argv[2]); // the length of the search string
    char *searchString = malloc(len);
    stpcpy(searchString,argv[2]);
    if (len > 20) {
        printf("The search string must less than 20 byte \n");
        exit(1);
    }
    long size = 0; // size of the file
    long numbers = 0;
    char *readString = malloc(100);
    fseek (inputFile, 0, SEEK_SET); // put the pointer on the top of the file
    int readSize = (int)fread(readString,1,100,inputFile); // the number of byte for each time
    size = (long)readSize;
   
    while (readSize >= len) {
        for (int i = 0; i < readSize && readSize - i >= len; i++) {
            if (readString[i] == (searchString[0] & 0xff)) { // if match the first chracter then scan
                int matched = 1;
                for (int j = 0; j < len; j++) {
                    if (readString[i+j] != (searchString[j]& 0xff) ) {
                        matched = 0;
                        break;
                    }
                }
                if (matched == 1) numbers++;
            }
        }
        if (readSize < 100) break;
        int moved = -len + 1; // we move backward the pointers of the Search file
        fseek(inputFile,moved,SEEK_CUR);
        readSize = (int)fread(readString,1,100,inputFile);
        
    }
    fseek(inputFile, 0, SEEK_END);
    size = (long)ftell(inputFile);
    
    fclose(inputFile);
    fseek (outputFile, 0, SEEK_SET);
    fprintf(outputFile,"Size of file is %ld \n",size);
    printf("Size of file is %ld \n",size);
    fprintf(outputFile, "number of the matches = %ld \n", numbers);
    printf("number of the matches = %ld \n", numbers);
   
    fclose(outputFile);
    return 0;
}
