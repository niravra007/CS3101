#ifndef CHATBOT_H
#define CHATBOT_H

#define max_res 20
#define max_keys 10// Maximum number of synonyms per response

typedef struct {
    char keywords[max_keys][100];  // Array of synonyms or related keywords
    char response[255];               // Response associated with the keywords
} FAQ;

void to_lowercase(char *str);
void chatbot(char *input);
int libby();

#endif