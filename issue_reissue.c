#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "searchtest.h"

typedef struct userpass {
    char username[20];
    char password[20];
} USER;

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
        printf("Enter a username: ");
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
    printf("What would you like to do today?\n Enter 1 to issue a new book.\n Enter 2 to view issued books, with due dates.\n Enter 3 to return a book.\n Enter 4 to quit.\n");
    scanf("%d",&k);

    if (k==1){
        char *filename1 = "bookdata.txt";
        char p[256], c[256], d[256];
        char *q, *a, *b;
        fflush(stdin);
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
        
        printf("Please enter ID of the book you wish to issue: ");
        char de[256];
        char *be;
        char *ke="";
        fgets(de, sizeof(de), stdin);
        de[strcspn(de, "\n")] = 0;
        be = strdup(de);
        //printf("%s %s",ke,be);
        fileSearch(filename1,ke,ke,be);
    }
}

void main(){
    char c[10];
    char *q;
    while ((strcmp(q,"y")!=0) && (strcmp(q,"n")!=0)){
        printf("Are you a new user? (Y/N): ");
        gets(c);
        q = strdup(c);
        for (int i=0; i < strlen(c); ++i) {
            q[i] = tolower(c[i]);
        }
        //printf("%s",c);
    }
    
    if (strcmp(q,"y")==0){
        regis();
        signin();
    }
    else{
        signin();
    }
}

