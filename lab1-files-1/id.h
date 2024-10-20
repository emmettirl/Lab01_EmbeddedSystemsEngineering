#ifndef LAB01_EMBDEDDEDSYSTEMSENGINEERING_ID_H
#define LAB01_EMBDEDDEDSYSTEMSENGINEERING_ID_H

// Define a struct to store the id_struct, the line number it was found on and the count of occurrences
struct id_struct {
    char identifier[200]; //assume max 200 characters
    int originalLineIndices[100]; //assume max 100 occurrences
    int occurrenceCount;
};

int id_main();

#endif //LAB01_EMBDEDDEDSYSTEMSENGINEERING_ID_H

