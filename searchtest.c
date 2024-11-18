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

typedef struct userpass {
    char username[20];
    char password[20];
} USER;


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

// Function to issue a book to a user
void fileIssue(const char *username, char *bookID) {
    // 1. Open the book database file to find book details
    FILE *bookDB = fopen("bookdata.txt", "r+b");
    if (bookDB == NULL) {
        printf("Error opening book database!\n");
        exit(1);
    }
    //create the filename based on the username
    char filename[256];
    sprintf(filename, "%s.txt", username);
    FILE *userFile = fopen(filename, "r+");

    // Search for the book by ID
    BOOK book;
    BOOKUSER countbook;
    int countissued=0;
    while (fread(&countbook, sizeof(BOOKUSER), 1, userFile)){
        countissued+=1;
    }
    //printf("%d",countissued);
    fclose(userFile);
    if (countissued>4){
        printf("\n5 books have been issued already! Please return at least one before issuing more.\n");
        return;
    }
    rewind(bookDB);
    int found = 0;
    while (fread(&book, sizeof(BOOK), 1, bookDB)) {
        if (strstr(book.id,bookID)!=NULL) {
            found = 1;
            if (book.no >= 3) {
                book.no -= 1; // Decrease stock by 1
                fseek(bookDB, -sizeof(BOOK), SEEK_CUR); // Move back to update the current record
                fwrite(&book, sizeof(BOOK), 1, bookDB); // Write the updated book data
                printf("Stock updated successfully!\n");
            } else if(3>book.no>0){
                printf("Book has very low stock. Only faculty members may issue.\n");
                fclose(bookDB);
                return;
            }
            else{
                printf("Book is out of stock!\n");
                fclose(bookDB);
                return;
            }
            break;
        }
    }
    
    if (!found) {
        printf("Book ID %d not found in the database!\n", bookID);
        fclose(bookDB);
        return;
    }

    fclose(bookDB);

    
    FILE *userFile1 = fopen(filename, "a");
    //Open the user file in append mode to add the book details
    if (userFile1 == NULL) {
        printf("Error opening user file for book issue!\n");
        exit(1);
    }
    //fclose(userFile1);

    //Write book details to the user's file
    BOOKUSER bookuser[1];
    strcpy(bookuser[0].title, book.title);
    strcpy(bookuser[0].id, book.id);
    strcpy(bookuser[0].author,book.author);
    // Calculate due date based on stock
    time_t now = time(NULL);
    int days_to_issue = (book.no + 1) * 7; // Calculate days to issue book for
    now += days_to_issue * 24 * 60 * 60;  // Add the days in seconds

    struct tm due_date = *localtime(&now);

    snprintf(bookuser[0].date, sizeof(bookuser[0].date), "%04d-%02d-%02d", 
             due_date.tm_year + 1900, due_date.tm_mon + 1, due_date.tm_mday);

    printf("Due Date: %s\n", bookuser[0].date);

                FILE *adminl = fopen("adminlog.txt","a");
                time_t now1 = time(NULL);
                struct tm *local = localtime(&now1);
                fprintf(adminl,"\n%02d-%02d-%04d %02d:%02d:%02d : Book ID: %s issued to %s!\n",local->tm_mday, local->tm_mon + 1, local->tm_year + 1900,
           local->tm_hour, local->tm_min, local->tm_sec,bookID,username);
                fclose(adminl);

    // Append to the user's file
    fileWrite(filename, bookuser, 1);
    printf("Book issued to %s successfully!\n", username);
}

void fileFacultyIssue(const char *username, char *bookID) {
    // 1. Open the book database file to find book details
    FILE *bookDB = fopen("bookdata.txt", "r+b");
    if (bookDB == NULL) {
        printf("Error opening book database!\n");
        exit(1);
    }
    //create the filename based on the username
    char filename[256];
    sprintf(filename, "%s.txt", username);
    FILE *userFile = fopen(filename, "r+");

    // Search for the book by ID
    BOOK book;
    BOOKUSER countbook;
    int countissued=0;
    while (fread(&countbook, sizeof(BOOKUSER), 1, userFile)){
        countissued+=1;
    }
    //printf("%d",countissued);
    fclose(userFile);
    if (countissued>9){
        printf("\n10 books have been issued already! Please return at least one before issuing more.\n");
        return;
    }
    rewind(bookDB);
    int found = 0;
    while (fread(&book, sizeof(BOOK), 1, bookDB)) {
        if (strstr(book.id,bookID)!=NULL) {
            found = 1;
            if (book.no >= 0) {
                book.no -= 1; // Decrease stock by 1
                fseek(bookDB, -sizeof(BOOK), SEEK_CUR); // Move back to update the current record
                fwrite(&book, sizeof(BOOK), 1, bookDB); // Write the updated book data
                printf("Stock updated successfully!\n");
            }
            else{
                printf("Book is out of stock!\n");
                fclose(bookDB);
                return;
            }
            break;
        }
    }
    
    if (!found) {
        printf("Book ID %d not found in the database!\n", bookID);
        fclose(bookDB);
        return;
    }

    fclose(bookDB);

    
    FILE *userFile1 = fopen(filename, "a");
    //Open the user file in append mode to add the book details
    if (userFile1 == NULL) {
        printf("Error opening user file for book issue!\n");
        exit(1);
    }
    //fclose(userFile1);

    //Write book details to the user's file
    BOOKUSER bookuser[1];
    strcpy(bookuser[0].title, book.title);
    strcpy(bookuser[0].id, book.id);
    strcpy(bookuser[0].author,book.author);
    // Calculate due date based on stock
    time_t now = time(NULL);
    int days_to_issue = (book.no + 1) * 7; // Calculate days to issue book for
    now += days_to_issue * 24 * 60 * 60;  // Add the days in seconds

    struct tm due_date = *localtime(&now);

    snprintf(bookuser[0].date, sizeof(bookuser[0].date), "%04d-%02d-%02d", 
             due_date.tm_year + 1900, due_date.tm_mon + 1, due_date.tm_mday);

    printf("Due Date: %s\n", bookuser[0].date);

                FILE *adminl = fopen("adminlog.txt","a");
                time_t now1 = time(NULL);
                struct tm *local = localtime(&now1);
                fprintf(adminl,"\n%02d-%02d-%04d %02d:%02d:%02d : Book ID: %s issued to %s!\n",local->tm_mday, local->tm_mon + 1, local->tm_year + 1900,
           local->tm_hour, local->tm_min, local->tm_sec,bookID,username);
                fclose(adminl);

    // Append to the user's file
    fileWrite(filename, bookuser, 1);
    printf("Book issued to %s successfully!\n", username);
}


void fileReadUserNames()
{
    FILE *fptr;
    USER user;

    printf("\nReading from file %s:\n\n", "userpass1.txt");

    fptr = fopen("userpass1.txt", "r+");

    if(fptr == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    while(fread(&user, sizeof(USER), 1, fptr)) 
    {

        printf ("Username: %s", user.username); 
        //printf("Current position: %ld  \n", ftell(fptr));
        printf("\n");

    }

    fclose(fptr);
}

void fileUpdateStock(char *updateID, int change)
{
   FILE *bookDB = fopen("bookdata.txt", "r+b");
    if (bookDB == NULL) {
        printf("Error opening book database!\n");
        exit(1);
    }

    // Search for the book by ID
    BOOK book;
    int found = 0;
    while (fread(&book, sizeof(BOOK), 1, bookDB)) {
        if (strstr(book.id,updateID)!=NULL) {
                //printf("%s %s",book.id,updateID);
                //printf("\n%d\n",book.no);
                book.no +=change; // increment/decrement stock
                //printf("\n%d\n",book.no);
                fseek(bookDB, -sizeof(BOOK), SEEK_CUR); // Move back to update the current record
                fwrite(&book, sizeof(BOOK), 1, bookDB); // Write the updated book data
                printf("\nStock updated successfully!\n");
                FILE *adminl = fopen("adminlog.txt","a");
                time_t now = time(NULL);
                struct tm *local = localtime(&now);
                fprintf(adminl,"\n%02d-%02d-%04d %02d:%02d:%02d : Stock of Book ID: %s updated to %d!\n",local->tm_mday, local->tm_mon + 1, local->tm_year + 1900,
           local->tm_hour, local->tm_min, local->tm_sec,updateID,book.no);
                fclose(adminl);
                found+=1;
                break;
        }
    }
    
    if (!found) {
        printf("\nBook ID %d not found in the database!\n", updateID);
        fclose(bookDB);
        return;
    }

    fclose(bookDB);
}