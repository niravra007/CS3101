#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct book{
    char title[255];
    char id[50];
    char author[50];
    int no;
    
}BOOK;

void fileRead(char *filename)
{
    FILE *fptr;
    BOOK book;

    printf("\nReading from file %s:\n\n", filename);

    fptr = fopen(filename, "r+");

    if(fptr == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    while(fread(&book, sizeof(BOOK), 1, fptr)) 
    {

        printf ("Title = %s \nid = %s \nAuthor = %s \nstock = %d\n", book.title, 
        book.id, book.author, book.no); 
        printf("Current position: %ld  \n", ftell(fptr));
        printf("\n");

    }

    fclose(fptr);
}

void fileSearch(char *filename, char *usertitle, char *userauthor, char *userid)
{
    FILE *fptr;
    BOOK book;
    int c = 0;

    printf("\nSearching in file %s:\n", filename);

    fptr = fopen(filename, "r+");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    while (fread(&book, sizeof(BOOK), 1, fptr)) {
        // Lowercase conversions for book fields to ensure case-insensitive matching
        char q1[255], q2[50], q3[50];
        strcpy(q1, book.title);
        strcpy(q2, book.author);
        strcpy(q3, book.id);
        for (int i = 0; q1[i]; i++) q1[i] = tolower(q1[i]);
        for (int i = 0; q2[i]; i++) q2[i] = tolower(q2[i]);
        for (int i = 0; q3[i]; i++) q3[i] = tolower(q3[i]);

        // Match conditions: only check if the field is not empty
        int matchTitle = (strlen(usertitle) == 0) || (strstr(q1, usertitle) != NULL);
        int matchAuthor = (strlen(userauthor) == 0) || (strstr(q2, userauthor) != NULL);
        int matchID = (strlen(userid) == 0) || (strstr(q3, userid) != NULL);

        // If all specified fields match, print the result
        if (matchTitle && matchAuthor && matchID) {
            printf("Title = %s\nID = %s\nAuthor = %s\nStock = %d\n", book.title, book.id, book.author, book.no);
            printf("Current position: %ld\n\n", ftell(fptr));
            c++;
        }
    }

    if (c == 0) {
        printf("No matching entries found. Please check your search criteria.\n");
    }

    fclose(fptr);
}


void fileWrite(char *filename, BOOK* books, int no_of_records)
{
    FILE *fptr;
    int i;

    printf("\nWriting in file %s:\n\n", filename);

    fptr = fopen(filename, "w");

    if(fptr == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    for(i = 0 ; i < no_of_records ; i++)
    {
        fwrite(&books[i], sizeof(BOOK), 1, fptr);        
    }
    
    

    fclose(fptr);


}
