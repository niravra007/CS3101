#ifndef SEARCH_H
#define SEARCH_H

// Define the BOOK structure
typedef struct book {
    char title[255];
    char id[50];
    char author[50];
    int no;
} BOOK;

// Declare the fileRead function
void fileSearch(char *filename, char *usertitle, char *userid, char *userauthor);

// Declare the search function prototype here if needed
// void searchFunction(...);

#endif // SEARCH_H
