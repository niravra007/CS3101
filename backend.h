#ifndef SEARCH_H
#define SEARCH_H

// Define the BOOK structure

typedef struct book{
    char title[255];
    char id[50];
    char author[50];
    int no;
    
}BOOK;


typedef struct bookuser{
    char title[255];
    char id[50];
    char author[50];
    char date[50];
    
}BOOKUSER;

typedef struct userpass {
    char username[20];
    char password[20];
} USER;


// Declare the fileRead function
void fileSearch(char *filename, char *usertitle, char *userid, char *userauthor);
void fileWrite(char *filename, BOOKUSER* books, int no_of_records);
void fileReadUser(char *filename);
void userDeleteEntry(char *filename, char *deleteID);
void fileWriteBook(char *filename, BOOK* books, int no_of_records);
void deleteBookEntry( char *deleteID);
void fileUpdateStock(char *updateID, int change);
void fileReadUserNames();
void fileFacultyIssue(const char *username, char *bookID);
void fileIssue(const char *username, char *bookID);


// Declare the search function prototype here if needed
// void searchFunction(...);

#endif // SEARCH_H
