#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "searchtest.h"
#include "Chatbot.h"


char user[20];
char pass[20];

void encrypt(char *password, int key) {
    int i;
    for (i = 0; i < strlen(password); ++i) {
        password[i] = password[i] - key;
    }
}

void decrypt(char password[],int key)
{
    unsigned int i;
    for(i=0;i<strlen(password);++i)
    {
        password[i] = password[i] + key;
    }
}

int username_exists(FILE *file, const char *username) {
    USER temp;
    rewind(file);
    while (fread(&temp, sizeof(USER), 1, file)) {
        if (strcmp(temp.username, username) == 0) {
            return 1; // Username already exists
        }
    }
    return 0; // Username is unique
}

void regis() {
    FILE *file = fopen("userpass1.txt", "a+b");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    USER new_user;
    int username_taken;

    do {
        printf("--------------------------------------REGISTERING--------------------------------------");
        printf("\nEnter a username: ");
        scanf("%s", new_user.username);
        
        // Check if the username already exists
        username_taken = username_exists(file, new_user.username);
        if (username_taken) {
            printf("Username already taken, please try again.\n");
        }
    } while (username_taken);

    printf("Enter a password: ");
    scanf("%s", new_user.password);

    // Encrypt the password with a simple encryption method
    encrypt(new_user.password, 0xFACA);

    // Append the new user record to the file
    fwrite(&new_user, sizeof(USER), 1, file);
    printf("Registration successful!\n");

    fclose(file);

    // Create a new file with the username as the file name
    char filename[256];
    sprintf(filename, "%s.txt", new_user.username);

    FILE *user_file = fopen(filename, "w");
    if (user_file == NULL) {
        printf("Error creating file for user!\n");
        exit(1);
    }

    fclose(user_file);
}


void adminsignin(){

    int k;
    int runchoice = 1;

    while (runchoice==1){
        printf("What would you like to do today?\n Enter 1 to check user records.\n Enter 2 to edit stock of books.\n Enter 3 to add a new book.\n Enter 4 to delete a book.\n Enter 5 to read admin log.\n Enter 6 to quit.\n");
        scanf("%d",&k);
        if(k==1){
            char tempuser[20];
            char filename[256];
            fileReadUserNames();
            printf("Enter the user ID: ");
            scanf("%s",&tempuser);
            sprintf(filename, "%s.txt", tempuser);
            fileReadUser(filename);
            fflush(stdin);

        }
        else if(k==6){
            runchoice -=1; 
        }
        else if(k==2){
            char *filename1 = "bookdata.txt";
        char p[256], c[256], d[256];
        char *q, *a, *b;
        int seag=1;
        while (seag==1){
        fflush(stdin);
        printf("\nIf the field is not known in any of the following entries, enter '-' instead.\n");
        printf("Enter Title: ");
        fgets(p, sizeof(p), stdin);
        p[strcspn(p, "\n")] = 0;  // Remove newline character
        q = strdup(p);

        printf("Enter Author: ");
        fgets(c, sizeof(c), stdin);
        c[strcspn(c, "\n")] = 0;
        a = strdup(c);

        printf("Enter ID: ");
        fgets(d, sizeof(d), stdin);
        d[strcspn(d, "\n")] = 0;
        b = strdup(d);

        for (int i=0; i < strlen(p); ++i) {
            q[i] = tolower(p[i]);
        }
        for (int i=0; i < strlen(c); ++i) {
            a[i] = tolower(c[i]);
        }
        for (int i=0; i < strlen(d); ++i) {
            b[i] = tolower(d[i]);
        }

        //reading
        //fileRead(filename);
        //printf("%s %s %s",q,a,b);
        //printf("%s \n",k1);
        
        printf("\n");
        char *emp="  -  ";
        if (strstr(emp,q)!=NULL){
            strcpy(q,"");
        }
        if (strstr(emp,a)!=NULL){
            strcpy(a,"");
        }
        if (strstr(emp,b)!=NULL){
            strcpy(b,"");
        }
        //printf("%s %s %s",q,a,b);
        fileSearch(filename1,q,a,b);
        printf("\nWould you like to search again? Type 1 if yes, 0 if no: ");
        scanf("%d",&seag);
        }
        
        fflush(stdin);
        printf("\nPlease enter ID of the book you wish to change stock of: ");
        char de[256];
        char *be;
        char *ke="";
        int changi=0;
        fgets(de, sizeof(de), stdin);
        de[strcspn(de, "\n")] = 0;
        be = strdup(de);
        fflush(stdin);
        printf("\nPlease enter how many books you want to add or delete (Use positive integer to add, negative to delete): ");
        scanf("%d",&changi);
        fileUpdateStock(be,changi);
        fflush(stdin);
        }
        else if (k==3){
            char temptitle[255];
            char tempid[50];
            char tempauthor[50];
            int tempno;
            fflush(stdin);
            printf("\nEnter Title of New Book: ");
            fgets(temptitle, sizeof(temptitle), stdin);
            temptitle[strcspn(temptitle, "\n")] = 0;  // Remove newline character
            fflush(stdin);
            printf("\nEnter Author of New Book: ");
            fgets(tempauthor, sizeof(tempauthor), stdin);
            tempauthor[strcspn(tempauthor, "\n")] = 0;  // Remove newline character
            fflush(stdin);
            printf("\nEnter ID of New Book: ");
            fgets(tempid, sizeof(tempid), stdin);
            tempid[strcspn(tempid, "\n")] = 0;  // Remove newline character
            fflush(stdin);
            printf("\nEnter Stock/Quantity of New Book: ");
            scanf("%d",&tempno);
            fflush(stdin);
            BOOK books[1];
            strcpy(books[0].title,temptitle);
            strcpy(books[0].author,tempauthor);
            strcpy(books[0].id,tempid);
            books[0].no=tempno;
            //printf("%s %s %s %d",books[0].title,books[0].author,books[0].id,books[0].no);
            fileWriteBook("bookdata.txt",books,1);
            FILE *adminl = fopen("adminlog.txt","a");
                time_t now = time(NULL);
                struct tm *local = localtime(&now);
                fprintf(adminl,"\n%02d-%02d-%04d %02d:%02d:%02d : Book ID: %s, Title: %s has been added by admin!\n",local->tm_mday, local->tm_mon + 1, local->tm_year + 1900,
           local->tm_hour, local->tm_min, local->tm_sec,books[0].id,books[0].title);
                fclose(adminl);

        }
        else if(k==4){
            char *filename1 = "bookdata.txt";
            char p[256], c[256], d[256];
            char *q, *a, *b;
            int seag=1;
            while (seag==1){
            fflush(stdin);
            printf("\nIf the field is not known in any of the following entries, enter '-' instead.\n");
            printf("Enter Title: ");
            fgets(p, sizeof(p), stdin);
            p[strcspn(p, "\n")] = 0;  // Remove newline character
            q = strdup(p);

            printf("Enter Author: ");
            fgets(c, sizeof(c), stdin);
            c[strcspn(c, "\n")] = 0;
            a = strdup(c);

            printf("Enter ID: ");
            fgets(d, sizeof(d), stdin);
            d[strcspn(d, "\n")] = 0;
            b = strdup(d);

            for (int i=0; i < strlen(p); ++i) {
                q[i] = tolower(p[i]);
            }
            for (int i=0; i < strlen(c); ++i) {
                a[i] = tolower(c[i]);
            }
            for (int i=0; i < strlen(d); ++i) {
                b[i] = tolower(d[i]);
            }

            //reading
            //fileRead(filename);
            //printf("%s %s %s",q,a,b);
            //printf("%s \n",k1);
            
            printf("\n");
            char *emp="  -  ";
            if (strstr(emp,q)!=NULL){
                strcpy(q,"");
            }
            if (strstr(emp,a)!=NULL){
                strcpy(a,"");
            }
            if (strstr(emp,b)!=NULL){
                strcpy(b,"");
            }
            //printf("%s %s %s",q,a,b);
            fileSearch(filename1,q,a,b);
            printf("\nWould you like to search again? Type 1 if yes, 0 if no: ");
            scanf("%d",&seag);
            }
            
            fflush(stdin);
            printf("\nPlease enter ID of the book you wish to delete: ");
            char de[256];
            char *be;
            char *ke="";
            int changi=0;
            fgets(de, sizeof(de), stdin);
            de[strcspn(de, "\n")] = 0;
            be = strdup(de);
            fflush(stdin);
            deleteBookEntry(be);
        }
        else if(k==5){
            FILE *file = fopen("adminlog.txt", "r");
            if (file == NULL) {
                printf("Error opening file for reading.\n");
            }

            char buffer[100];
            printf("Contents of the file:\n");
            while (fgets(buffer, sizeof(buffer), file)) {
                printf("%s", buffer); // Print each line
            }

            fclose(file);
        }

    }

}

void signin(){
    FILE *fptr;
    USER userpass;

    //printf("\nReading from file %s:\n\n", "userpass1.txt");

    fptr = fopen("userpass1.txt", "r+");

    if(fptr == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    int c=0;

    while(c==0){
        printf("\n--------------------------------------SIGNING IN--------------------------------------\n");
        printf("Enter Username: ");
        scanf("%s",&user);
        //printf("%s \n",user);
        printf("Enter Password: ");
        scanf("%s",&pass);
        //printf("%s \n",pass);

        while(fread(&userpass, sizeof(USER), 1, fptr) && c==0) 
        {
            decrypt(userpass.password,0xFACA);
            //printf("%s %s %s %s \n",user, pass, userpass.username,userpass.password);
            if (strcmp(user,userpass.username)==0 && strcmp(pass,userpass.password)==0){
                printf("\nHello user %s! Welcome to the Library.\n",userpass.username);
                c=c+1;
                //printf("%d",c);
            }
	        printf("\n");
        
        }
        if(c==0){
            printf("Please re-enter credentials.\n");
            rewind(fptr);
        }

    }
    int k;
    int runchoice = 1;

    while (runchoice==1){
        printf("\nWhat would you like to do today?\n Enter 1 to issue a new book.\n Enter 2 to view issued books, with due dates.\n Enter 3 to return a book.\n Enter 4 to speak to the Library Chatbot, Libby!\n Enter 5 to quit.\n");
    scanf("%d",&k);
    switch(k){
        case 1: {
            char *filename1 = "bookdata.txt";
        char p[256], c[256], d[256];
        char *q, *a, *b;
        int seag=1;
        while (seag==1){
        fflush(stdin);
        printf("\nIf the field is not known in any of the following entries, enter '-' instead.\n");
        printf("Enter Title: ");
        fgets(p, sizeof(p), stdin);
        p[strcspn(p, "\n")] = 0;  // Remove newline character
        q = strdup(p);

        printf("Enter Author: ");
        fgets(c, sizeof(c), stdin);
        c[strcspn(c, "\n")] = 0;
        a = strdup(c);

        printf("Enter ID: ");
        fgets(d, sizeof(d), stdin);
        d[strcspn(d, "\n")] = 0;
        b = strdup(d);

        for (int i=0; i < strlen(p); ++i) {
            q[i] = tolower(p[i]);
        }
        for (int i=0; i < strlen(c); ++i) {
            a[i] = tolower(c[i]);
        }
        for (int i=0; i < strlen(d); ++i) {
            b[i] = tolower(d[i]);
        }

        //reading
        //fileRead(filename);
        //printf("%s %s %s",q,a,b);
        //printf("%s \n",k1);
        
        printf("\n");
        char *emp="  -  ";
        if (strstr(emp,q)!=NULL){
            strcpy(q,"");
        }
        if (strstr(emp,a)!=NULL){
            strcpy(a,"");
        }
        if (strstr(emp,b)!=NULL){
            strcpy(b,"");
        }
        //printf("%s %s %s",q,a,b);
        fileSearch(filename1,q,a,b);
        printf("Would you like to search again? Type 1 if yes, 0 if no: ");
        scanf("%d",&seag);
        }
        
        fflush(stdin);
        printf("Please enter ID of the book you wish to issue: ");
        char de[256];
        char *be;
        char *ke="";
        fgets(de, sizeof(de), stdin);
        de[strcspn(de, "\n")] = 0;
        be = strdup(de);
        char filename[256];
        sprintf(filename, "%s", user);
        //printf("%s %s",filename,be);
        fileIssue(filename,be);
        fflush(stdin);
        }
        break;

        case 2: {
            char filename[256];
            sprintf(filename, "%s.txt", user);
            fileReadUser(filename);
            fflush(stdin);
        }
        break;

        case 3: {
            char filename[256];
            sprintf(filename, "%s.txt", user);
            fileReadUser(filename);
            fflush(stdin);
            printf("Which book would you like to return? Please enter the ID: ");
            char de[256];
            char *be;
            char *ke="";
            fgets(de, sizeof(de), stdin);
            de[strcspn(de, "\n")] = 0;
            be = strdup(de);

            userDeleteEntry(filename,be);
            FILE *bookDB = fopen("bookdata.txt", "r+b");
            if (bookDB == NULL) {
                printf("Error opening file!\n");
                exit(1);
            }

                BOOK book;
                int found = 0;

                while (fread(&book, sizeof(BOOK), 1, bookDB) == 1) {
                // Check if the book ID matches
                if (strcmp(book.id, be) == 0) { // Assuming `book.id` and `be` are strings
                //printf("Before Update: ID=%s, Stock=%d\n", book.id, book.no);

                // Update stock
                book.no += 1;
                fseek(bookDB, -sizeof(BOOK), SEEK_CUR);

                if (fwrite(&book, sizeof(BOOK), 1, bookDB) != 1) {
                printf("Error writing updated record!\n");
                }       

                found = 1;
                break;
            }
            }

            if (!found) {
            printf("Book ID not found in the database.\n");
            }

            fclose(bookDB);
        }
        break;

        case 4: fflush(stdin);
                libby();
                break;

        case 5: runchoice -=1; 
                break;
        
        default:
            break;


    }
    }
    
}

void faculty(char* facuser){
    printf("--------------------------------------------------------------------------------------");
    printf("\nHello faculty user %s! Welcome to the Library.\n",facuser); 
    int k;
    int runchoice = 1;

    while (runchoice==1){
        printf("\nWhat would you like to do today?\n Enter 1 to issue a new book.\n Enter 2 to view issued books, with due dates.\n Enter 3 to return a book.\n Enter 4 to speak to the Library Chatbot, Libby!\n Enter 5 to quit.\n");
        scanf("%d",&k);

        if (k==1){
            char *filename1 = "bookdata.txt";
            char p[256], c[256], d[256];
            char *q, *a, *b;
            int seag=1;
            while (seag==1){
            fflush(stdin);
            printf("\nIf the field is not known in any of the following entries, enter '-' instead.\n");
            printf("Enter Title: ");
            fgets(p, sizeof(p), stdin);
            p[strcspn(p, "\n")] = 0;  // Remove newline character
            q = strdup(p);

            printf("Enter Author: ");
            fgets(c, sizeof(c), stdin);
            c[strcspn(c, "\n")] = 0;
            a = strdup(c);

            printf("Enter ID: ");
            fgets(d, sizeof(d), stdin);
            d[strcspn(d, "\n")] = 0;
            b = strdup(d);

            for (int i=0; i < strlen(p); ++i) {
                q[i] = tolower(p[i]);
            }
            for (int i=0; i < strlen(c); ++i) {
                a[i] = tolower(c[i]);
            }
            for (int i=0; i < strlen(d); ++i) {
                b[i] = tolower(d[i]);
            }

            //reading
            //fileRead(filename);
            //printf("%s %s %s",q,a,b);
            //printf("%s \n",k1);
            
            printf("\n");
            char *emp="  -  ";
            if (strstr(emp,q)!=NULL){
                strcpy(q,"");
            }
            if (strstr(emp,a)!=NULL){
                strcpy(a,"");
            }
            if (strstr(emp,b)!=NULL){
                strcpy(b,"");
            }
            //printf("%s %s %s",q,a,b);
            fileSearch(filename1,q,a,b);
            printf("Would you like to search again? Type 1 if yes, 0 if no: ");
            scanf("%d",&seag);
            }
            
            fflush(stdin);
            printf("Please enter ID of the book you wish to issue: ");
            char de[256];
            char *be;
            char *ke="";
            fgets(de, sizeof(de), stdin);
            de[strcspn(de, "\n")] = 0;
            be = strdup(de);
            char filename[256];
            sprintf(filename, "%s", facuser);
            //printf("%s %s",filename,be);
            fileFacultyIssue(filename,be);
            fflush(stdin);
        }
        else if(k==2){
            char filename[256];
            sprintf(filename, "%s.txt", facuser);
            fileReadUser(filename);
            fflush(stdin);
        }
        else if(k==3){
            char filename[256];
            sprintf(filename, "%s.txt", facuser);
            fileReadUser(filename);
            fflush(stdin);
            printf("Which book would you like to return? Please enter the ID: ");
            char de[256];
            char *be;
            char *ke="";
            fgets(de, sizeof(de), stdin);
            de[strcspn(de, "\n")] = 0;
            be = strdup(de);

            userDeleteEntry(filename,be);
            FILE *bookDB = fopen("bookdata.txt", "r+b");
        if (bookDB == NULL) {
            printf("Error opening file!\n");
            exit(1);
        }

            BOOK book;
            int found = 0;

            while (fread(&book, sizeof(BOOK), 1, bookDB) == 1) {
            // Check if the book ID matches
            if (strcmp(book.id, be) == 0) { // Assuming `book.id` and `be` are strings
            //printf("Before Update: ID=%s, Stock=%d\n", book.id, book.no);

            // Update stock
            book.no += 1;
            fseek(bookDB, -sizeof(BOOK), SEEK_CUR);

            if (fwrite(&book, sizeof(BOOK), 1, bookDB) != 1) {
            printf("Error writing updated record!\n");
            }       

            found = 1;
            break;
            }
            }

            if (!found) {
            printf("Book ID not found in the database.\n");
            }

            fclose(bookDB);
        }
        else if(k==4){
            fflush(stdin);
            libby();
        }
        else if(k==5){
            runchoice -=1; 
        }
        else{
            
        }
        }
   
}

void main(){
    int wholeprog=0;
    while (wholeprog==0){
        char c[10];
        char *q;
        fflush(stdin);
        while ((strcmp(q,"y")!=0) && (strcmp(q,"n")!=0) && (strcmp(q,"e")!=0)){
            printf("Are you admin? (Y/N)\nTo exit, type E: ");
            gets(c);
            q = strdup(c);
            for (int i=0; i < strlen(c); ++i) {
                q[i] = tolower(c[i]);
            }
            //printf("%s",c);
        }
        
        if (strcmp(q,"y")==0){
                int flip=0;
                char adpass[50];
                char adminpass[50] = "haringhataITcell";
                while(flip==0){
                    printf("\n--------------------------------------SIGNING IN--------------------------------------\n");
                    printf("\nEnter Password: ");
                    scanf("%s",&adpass);
                    //printf("%s %s\n",adminpass,adpass);
                    if(strcmp(adpass,adminpass)==0){
                        printf("\n--------------------------------------------------------------------------------------\n");
                        printf("\nWelcome administrator!\n");
                        flip+=1;
                        adminsignin();
                        strcpy(q,"lol");
                    }
                    else{
                        printf("Incorrect Password! Please try again.\n");
                    }
                }
        }
        else if(strcmp(q,"e")==0){
            wholeprog+=1;
        }
        else{
            int checkad=1;
            printf("To register as a new user, type 0.\nTo login as a Student User, type 1.\nTo login as a Faculty User, type 2: ");
            scanf("%d",&checkad);
            // if(checkad==0){
            //     int flip=0;
            //     char adpass[50];
            //     char adminpass[50] = "haringhataITcell";
            //     while(flip==0){
            //         printf("\n--------------------------------------SIGNING IN--------------------------------------\n");
            //         printf("\nEnter Password: ");
            //         scanf("%s",&adpass);
            //         //printf("%s %s\n",adminpass,adpass);
            //         if(strcmp(adpass,adminpass)==0){
            //             printf("\nWelcome administrator!\n");
            //             flip+=1;
            //             adminsignin();
            //         }
            //         else{
            //             printf("Incorrect Password! Please try again.\n");
            //         }
            //     }
                

            // }
            if(checkad==1){
                signin();
                strcpy(q,"lol");
            }
            else if (checkad==0){
                regis();
                signin();
                strcpy(q,"lol");
            }
            else if(checkad==2){
                int facchk=0;
                while (facchk==0){
                    printf("\n--------------------------------------SIGNING IN--------------------------------------\n");
                    printf("Enter Username: ");
                    scanf("%s",&user);
                    //printf("%s \n",user);
                    printf("Enter Password: ");
                    scanf("%s",&pass);
                    //printf("%s \n",pass)
                    if ((strcmp(user,"kripa")==0 && strcmp(pass,"hello")==0) || (strcmp(user,"laal")==0 && strcmp(pass,"beast")==0) || (strcmp(user,"koushikd")==0 && strcmp(pass,"appreciate")==0)){
                        faculty(user);
                        strcpy(q,"lol");
                        facchk+=1;
                    }
                    else{
                        printf("\nPlease recheck credentials!\n");
                    }
                }
            }
        }
    }
    
}

