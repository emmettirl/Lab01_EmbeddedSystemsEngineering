// Lab 1, Question 1
// Emmett Fitzharris, R00222357

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "id.h"
#include "tree.h"

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
            // If the current character is a letter or an underscore we know it is an ID,
            if (isalpha(buf[i]) || buf[i]=='_'){
                // Create a new id_struct struct to store the ID and the line it was found on
                struct id_struct currentId;
                currentId.occurrenceCount = 0;

                // Copy the ID into the struct
                // loop until we reach a non-alphanumeric character which will be the end of the ID
                while (buf[i] && (isalnum(buf[i]) || buf[i]=='_')) {
                    currentId.identifier[j++] = buf[i++];
                }
                // Add a null terminator to the end of the ID string
                currentId.identifier[j] = '\0';

                // Check if the id_struct is already in the array
                int found = 0;
                for (int k = 0; k < idCount; k++) {
                    if (strcmp(identifiers[k].identifier, currentId.identifier) == 0) {
                        // If the id_struct is already in the array,
                        // add the line number to the list of lines and increment the occurrenceCount
                        identifiers[k].originalLineIndices[identifiers[k].occurrenceCount++] = lineCount;
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
                        identifiers[idCount].occurrenceCount = 1;
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

    // Sort the identifiers by the id_struct alphabetically and print them using the tree.c functions
    struct Node* root = NULL;
    for (i = 0; i < idCount; i++) {
        root = insert(root, identifiers[i]);
    }
    inorder(root);
    fclose(fp);
    return 0;
}




