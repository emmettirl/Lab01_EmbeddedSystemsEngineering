// Lab 1, Question 1
// Emmett Fitzharris, R00222357

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "id.h"

// Define a struct to store the id_struct, the line number it was found on and the occurenceCount of occurrences
struct id_struct {
    char identifier[200]; //assume max 200 characters
    int originalLineIndices[100]; //assume max 100 occurences
    int occurenceCount;
};

int id_main(){
    // Create an array of id_struct structures,
    // with an arbitrary size limit assumed of 1000 structs.
    struct id_struct identifiers[1000];

    char buf[200];
    FILE *fp;
    fp=fopen("test.txt","r");

    if (fp == NULL) {
        printf("Error: Could not open file\n");

        // find current working directory, so I know where to put txt file if not found
        // (needs to be in cmake-build-debug)
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("Current working directory: %s\n", cwd);
            fflush(stdout);
        } else {
            perror("getcwd() error");
            fflush(stdout);
        }
        return -1;  // Return an error code if the file can't be opened
    }

    int i, j;
    int lineCount = 1;
    int idCount = 0;

    // Read from file
    while (fgets(buf,100,fp)){
        unsigned long len = strlen(buf);
        for (j=0,i=0;i<len;i++){
            // If the character is a letter or an underscore we know it is an ID
            if (isalpha(buf[i]) || buf[i]=='_'){
                // Create a new id_struct struct to store the ID and the line it was found on
                struct id_struct currentId;
                currentId.occurenceCount = 0;

                // Copy the ID into the struct
                while (buf[i] && (isalnum(buf[i]) || buf[i]=='_')) {
                    currentId.identifier[j++] = buf[i++];
                }
                currentId.identifier[j] = '\0';

                // Check if the id_struct is already in the array
                int found = 0;
                for (int k = 0; k < idCount; k++) {
                    if (strcmp(identifiers[k].identifier, currentId.identifier) == 0) {
                        // If the id_struct is already in the array,
                        // add the line number to the list of lines and increment the occurenceCount
                        identifiers[k].originalLineIndices[identifiers[k].occurenceCount++] = lineCount;
                        found = 1;
                        break;
                    }
                }

                // If the id_struct is not in the array, add it
                if (!found) {
                    // Check if we have too many identifiers already
                    if (idCount < 100) {
                        strcpy(identifiers[idCount].identifier, currentId.identifier);
                        identifiers[idCount].originalLineIndices[0] = lineCount;
                        identifiers[idCount].occurenceCount = 1;
                        idCount++;
                    } else {
                        printf("Error: Too many identifiers\n");
                        fflush(stdout);
                        return -1;
                    }

                }
                j=0;
            }
        }
        lineCount++;
    }

    // Sort the identifiers by the id_struct alphabetically using strcmp and a bubble sorting algorithm
    for (i = 0; i < idCount; i++) {
        for (j = i + 1; j < idCount; j++) {
            // If the current id_struct is greater than the next one, swap them
            if (strcmp(identifiers[i].identifier, identifiers[j].identifier) > 0) {
                // Swap the identifiers using a temporary struct
                struct id_struct temp = identifiers[i];
                identifiers[i] = identifiers[j];
                identifiers[j] = temp;
            }
        }
    }

    // Print out the identifiers
    for (i = 0; i < idCount; i++) {
        printf("id_struct = %s, lines = ", identifiers[i].identifier);
        // Print out the line numbers for each id_struct
        for (j = 0; j < identifiers[i].occurenceCount; j++) {
            printf("%d ", identifiers[i].originalLineIndices[j]);
        }
        printf("\n");
        fflush(stdout);
    }

    fclose(fp);
    return 0;
}




