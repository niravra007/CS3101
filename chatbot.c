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
    {{"return", "give back", "reissue", "return book", "returning"}, "To return a book, log in as a user and select 'Return Book' from the menu. \n"},
    {{"search", "find", "lookup", "locate", "look for"}, "Use the 'Search Book' feature to find books by title, author, or ID. \n"},
    {{"admin", "administrator", "librarian", "manager", "admin tasks"}, "Admins can add, update, or delete book records through the admin menu. \n"},
    {{"lost", "missing", "misplaced", "cannot find", "lose"}, "Please contact the library admin immediately if you have lost a book. \n"},
    {{"overdue", "late", "delay", "due date", "penalty"}, "Overdue books must be returned as soon as possible to avoid penalties. \n"},
    {{"max", "maximum", "limit", "book count", "how many books"}, "You can borrow up to 5 books at a time. Faculty may have special privileges. \n"},
    {{"copies", "availability", "stock", "number", "books available"}, "Books with less than 3 copies are prioritized for faculty members.\n \n"},
    {{"duration", "time", "period", "borrow time", "how many days","days"}, "The borrowing period depends on availability. More copies mean a longer duration. \n"},
    {{"password", "reset", "forgot password", "change password", "login issue"}, "To reset your password, contact the library admin. \n"},
    {{"borrow", "lend", "issue", "take book", "get book"}, "To borrow a book, log in as a user and select 'Borrow Book' from the menu.\n"},
    {{"reissue"}, "We do not have a system for reissuing books. However you can borrow it again after returning.\n " },
    {{"hello", "hi"},"Hi! Hope you're having a nice day.How may I help you today? \n "}
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
        printf("Libby: I'm sorry, I couldn't find any relevant information. Could you be more specific? \n \n");
    }
}

int libby(){
    char input[255];
    printf("\n--------------------------------------------------------------------------------------\n");
    printf("\nWelcome to the Library Chatbot, Libby!\n");
    printf("Type 'exit' to quit.\n");
    printf("Libby: Hi! Hope you're having a nice day.How may I help you today?");

    while (1) {
        printf("\nYou: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';  // Remove newline character

        if (strcmp(input, "exit") == 0) {
            printf("Libby: Goodbye!\n");
            printf("--------------------------------------------------------------------------------------\n");
            break;
        }

        chatbot(input);
    }

    return 0;
}
