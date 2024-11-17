#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>

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
        //printf("Current position: %ld  \n", ftell(fptr));
        printf("\n");

    }

    fclose(fptr);
}

void fileReadUser(char *filename)
{
    FILE *fptr;
    BOOKUSER bookuser;

    printf("\nReading from file %s:\n\n", filename);

    fptr = fopen(filename, "r+");

    if(fptr == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    while(fread(&bookuser, sizeof(BOOKUSER), 1, fptr)) 
    {

        printf ("Title = %s \nid = %s \nAuthor = %s\nDue Date = %s\n", bookuser.title, 
        bookuser.id, bookuser.author, bookuser.date); 
        //printf("Current position: %ld  \n", ftell(fptr));
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
            printf("Title = %s\nID = %s\nAuthor = %s\nStock = %d\n\n", book.title, book.id, book.author, book.no);
            //printf("Current position: %ld\n\n", ftell(fptr));
            c++;
        }
    }

    if (c == 0) {
        printf("No matching entries found. Please check your search criteria.\n");
    }

    fclose(fptr);
}


void fileWrite(char *filename, BOOKUSER* books, int no_of_records)
{
    FILE *fptr;
    int i;

    printf("\nWriting in file %s:\n\n", filename);

    fptr = fopen(filename, "a");

    if(fptr == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    for(i = 0 ; i < no_of_records ; i++)
    {
        fwrite(&books[i], sizeof(BOOKUSER), 1, fptr);        
    }
    
    

    fclose(fptr);


}

void userDeleteEntry(char *filename, char *deleteID)
{
    FILE *fptr;
    BOOKUSER bookuser, *books;
    int no_of_rec = 0, i;

     printf("\nReading from file %s:\n\n", filename);

    fptr = fopen(filename, "r+");

    if(fptr == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    while(fread(&bookuser, sizeof(BOOKUSER), 1, fptr)) 
    {
        
        
        no_of_rec++;//count the number of records (each record is a BOOK type variable)

    }
    
    books = (BOOKUSER*)malloc((no_of_rec-1)*sizeof(BOOKUSER));//allocating dynamically space for the number of records in the file to be read
    
    rewind(fptr);//going to the beginning of the file
    
    i = 0;
    int countdel=0;
    while(fread(&bookuser, sizeof(BOOKUSER), 1, fptr)) //reading each record
    {
        //printf("Current position: %ld  ", ftell(fptr));
        //printf ("Title = %s id = %s stock = %d\n", book.title, 
        //book.id, book.no); 
        
    	if(strcmp(bookuser.id, deleteID) != 0)//check if this is the record to be updated
        {
            strcpy(books[i].title, bookuser.title);
    	    strcpy(books[i].id, bookuser.id);
    	    strcpy(books[i].author, bookuser.author);
            strcpy(books[i].date, bookuser.date);
            i++;
		}
        else{
            countdel+=1;
        }
    	
    }  
    /*
    printf("After update:\n\n");
	
	for(i = 0 ; i < no_of_rec; i++)
	{
		printf ("Title = %s id = %s stock = %d\n", books[i].title, books[i].id, books[i].no);
	}  */

    fclose(fptr);
    
    //printf("\nWriting in file %s:\n\n", filename);

    fptr = fopen(filename, "w");

    if(fptr == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    for(i = 0 ; i < (no_of_rec-1) ; i++)
    {
        fwrite(&books[i], sizeof(BOOKUSER), 1, fptr); //overwriting the file with the updated record (even the unchanged records are overwritten)       
    }
    
    fclose(fptr);

    FILE *adminl = fopen("adminlog.txt","a");
                time_t now = time(NULL);
                struct tm *local = localtime(&now);
                fprintf(adminl,"\n%02d-%02d-%04d %02d:%02d:%02d : Book ID: %s returned by %s!\n",local->tm_mday, local->tm_mon + 1, local->tm_year + 1900,
           local->tm_hour, local->tm_min, local->tm_sec,deleteID,filename);
                fclose(adminl);

    if(countdel==0){
        printf("Book not found!\n");
    }
    else{
        printf("Book has been returned!\n");
    }    

}

void fileWriteBook(char *filename, BOOK* books, int no_of_records)
{
    FILE *fptr;
    int i;

    printf("\nWriting in file %s:\n\n", filename);

    fptr = fopen(filename, "a");

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


void deleteBookEntry( char *deleteID)
{
    FILE *fptr;
    BOOK book, *books;
    int no_of_rec = 0, i;
    char *filename="bookdata.txt";

    printf("\nReading from file %s:\n\n", filename);

    fptr = fopen(filename, "r+");

    if(fptr == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    while(fread(&book, sizeof(BOOK), 1, fptr)) 
    {
        
        
        no_of_rec++;//count the number of records (each record is a BOOK type variable)

    }
    
    books = (BOOK*)malloc((no_of_rec-1)*sizeof(BOOK));//allocating dynamically space for the number of records in the file to be read
    
    rewind(fptr);//going to the beginning of the file
    
    i = 0;
    int countdel=0;
    while(fread(&book, sizeof(BOOK), 1, fptr)) //reading each record
    {
        //printf("Current position: %ld  ", ftell(fptr));
        //printf ("Title = %s id = %s stock = %d\n", book.title, 
        //book.id, book.no); 
        
    	if(strcmp(book.id, deleteID) != 0)//check if this is the record to be updated
        {
            strcpy(books[i].title, book.title);
    	    strcpy(books[i].id, book.id);
    	    strcpy(books[i].author, book.author);
            books[i].no=book.no;
            i++;
		}
        else{
            countdel+=1;
        }
    	
    }  
    /*
    printf("After update:\n\n");
	
	for(i = 0 ; i < no_of_rec; i++)
	{
		printf ("Title = %s id = %s stock = %d\n", books[i].title, books[i].id, books[i].no);
	}  */

    fclose(fptr);
    
    //printf("\nWriting in file %s:\n\n", filename);

    fptr = fopen(filename, "w");

    if(fptr == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    for(i = 0 ; i < (no_of_rec-1) ; i++)
    {
        fwrite(&books[i], sizeof(BOOK), 1, fptr); //overwriting the file with the updated record (even the unchanged records are overwritten)       
    }
    
    fclose(fptr);

    if(countdel==0){
        printf("Book not found!\n");
    }
    else{
        printf("Book has been deleted!\n");
        FILE *adminl = fopen("adminlog.txt","a");
                time_t now = time(NULL);
                struct tm *local = localtime(&now);
                fprintf(adminl,"\n%02d-%02d-%04d %02d:%02d:%02d : Book ID: %s, has been deleted by admin!\n",local->tm_mday, local->tm_mon + 1, local->tm_year + 1900,
           local->tm_hour, local->tm_min, local->tm_sec,deleteID);
    }    

}