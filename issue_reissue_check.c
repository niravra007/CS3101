#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct userpass{
    char username[20];
    char password[20];
    
}USER;

char user[20];
char pass[20];

void encrypt(char *password,int key)
{
    int i;
    for(i=0;i<strlen(password);++i)
    {
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

void fileWrite(char *filename, USER* userpass, int no_of_records)
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
        fwrite(&userpass[i], sizeof(USER), 1, fptr);        
    }
    
    

    fclose(fptr);


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
        
    }

    fclose(fptr);
}

void regis(){
    USER userpasses[3], userpass;
    FILE *fptr;
    char filename[] = "userpass1.txt";

    char *user;
    char *pass;
    int d=1;
    fptr = fopen(filename, "r+");
    while (d==0){
        while(fread(&userpass, sizeof(USER), 1, fptr)) 
        {
            printf("Enter Desired Username: ");
            scanf("%s",&user);
            printf("%s %d",user,strcmp(userpass.username,user));
            if(strcmp(userpass.username,user)==0){
                printf("Username already taken!");
                d=d+1;
            }
        }
    }
    printf("\n");
    printf("Enter Desired Password: ");
    scanf("%s",&pass);
    rewind(fptr);
    
	//loading the record
    strcpy(userpasses[0].username, user);
    encrypt(pass,0xFACA);
    strcpy(userpasses[0].password, pass);

    fileWrite(filename, userpasses, 1);

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
    }
    else{
        signin();
    }
}

