#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define max_res 20
#define max_keys 10// Maximum number of synonyms per response

typedef struct {
    char keywords[max_keys][100];  // Array of synonyms or related keywords
    char response[255];               // Response associated with the keywords
} FAQ;

FAQ faq_list[max_res] = {
    {{"return", "give back", "reissue", "return book", "returning"}, "To return a book, log in as a user and select 'Return Book' from the menu.\n You can enter 1 to login and 2 to signup as a new user."},
    {{"search", "find", "lookup", "locate", "look for"}, "Use the 'Search Book' feature to find books by title, author, or ID.\n You can enter 1 to login and 2 to signup as a new user."},
    {{"admin", "administrator", "librarian", "manager", "admin tasks"}, "Admins can add, update, or delete book records through the admin menu.\n You can enter 1 to login and 2 to signup as a new user."},
    {{"lost", "missing", "misplaced", "cannot find", "lose"}, "Please contact the library admin immediately if you have lost a book.\n You can enter 1 to login and 2 to signup as a new user."},
    {{"overdue", "late", "delay", "due date", "penalty"}, "Overdue books must be returned as soon as possible to avoid penalties.\n You can enter 1 to login and 2 to signup as a new user."},
    {{"max", "maximum", "limit", "book count", "how many books"}, "You can borrow up to 5 books at a time. Faculty may have special privileges.\n You can enter 1 to login and 2 to signup as a new user."},
    {{"copies", "availability", "stock", "number", "books available"}, "Books with less than 3 copies are prioritized for faculty members.\n You can enter 1 to login and 2 to signup as a new user."},
    {{"duration", "time", "period", "borrow time", "how many days","days"}, "The borrowing period depends on availability. More copies mean a longer duration.\n You can enter 1 to login and 2 to signup as a new user."},
    {{"password", "reset", "forgot password", "change password", "login issue"}, "To reset your password, contact the library admin.\n You can enter 1 to login and 2 to signup as a new user."},
    {{"borrow", "lend", "issue", "take book", "get book"}, "To borrow a book, log in as a user and select 'Borrow Book' from the menu.\n You can enter 1 to login and 2 to signup as a new user."},
    {{"reissue"}, "We do not have a system for reissuing books. However you can borrow it again after returning.\n You can enter 1 to login and 2 to signup as a new user." },
    {{"hello", "hi"},"Hi! Hope you're having a nice day.How may I help you today? \n You can enter 1 to login and 2 to signup as a new user."}
};

void to_lowercase(char *str) 
{
    for (int i = 0; str[i]; i++) 
    {
        str[i] = tolower(str[i]);
    }
}

void chatbot(char *input) 
{
    int match_found = 0;  // Flag to indicate if a match was found
    if(isdigit(*input))
    {int x=*input-'0';
    switch (x)
        {
        case 1:
        {
            regis();    
            break;
        }
        case 2:
        {
            signin();
            break;
        }
        default:

            break;
        }
    }
    else
    {
        to_lowercase(input);  // Convert input to lowercase for case-insensitive matching
        for (int i = 0; i < max_res; i++) {
            for (int j = 0; j < max_keys; j++) {
                if (faq_list[i].keywords[j][0] != '\0' && strstr(input, faq_list[i].keywords[j]) != NULL) 
                {
                printf("Libby: %s\n", faq_list[i].response);
                match_found = 1;
                break;  // Exit inner loop on match
                }
            }
            if (match_found)
            {
                break;  // Exit outer loop as well
            }
        }

    if (!match_found) {  // Correctly handle unmatched input
        printf("Libby: I'm sorry, I couldn't find any relevant information. Could you be more specific? \n You can enter 1 to login and 2 to signup as a new user.");
    }
}
}

int main(){
    char input[255];
    printf("Welcome to the Library Chatbot, Libby!\n");
    printf("Type 'exit' to quit.\n");
    printf("Libby: Hi! Hope you're having a nice day.How may I help you today?");

    while (1) {
        printf("\nYou: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';  // Remove newline character

        if (strcmp(input, "exit") == 0) {
            printf("Libby: Goodbye!\n");
            break;
        }

        chatbot(input);
    }

    return 0;
}
