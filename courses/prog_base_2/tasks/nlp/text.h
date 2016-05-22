#pragma once
#include "list/list.h"
#define BUFFER_SIZE 10000
typedef struct sentence_s sentence_t;
typedef struct word_s word_t;
typedef struct text_s text_t;

text_t * text_from_file(char * fileName);
text_t * text_sentence_filter(text_t * text);

list_t * sentence_list_from_text(text_t * text);
list_t * word_list_from_sentence(sentence_t * sentence);
char * word_to_string(word_t  *word);

void text_delete(text_t * text);
void sentence_delete(sentence_t * sentence);
void word_delete(word_t  * word);