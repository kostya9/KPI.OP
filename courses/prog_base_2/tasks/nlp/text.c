#define _CRT_SECURE_NO_WARNINGS
#include "text.h"
#include <stdio.h>
#include <string.h>
#define BUFFER_SENTENCES_COUNT 1000
#define SENTENCE_WORD_BUFFER 10000
#define WORD_BUFFER 100
typedef struct word_s
{
	char * string;
} word_s;

typedef struct sentence_s {
	list_t * words;
} sentence_s;

typedef struct text_s {
	list_t * sentences;
} text_s;

text_t * text_from_file(char * fileName)
{
	text_t * text = malloc(sizeof(text_t));
	text->sentences = list_new();
	// Read from file
	char * buffer_text = malloc(sizeof(char) * BUFFER_SIZE);
	FILE * f = fopen("text.txt", "r");
	int sz = fread(buffer_text, sizeof(char), BUFFER_SIZE, f);
	fclose(f);
	buffer_text[sz] = '\0';

	// Parse sentences
	int count = 0;
	char * buffer = malloc(sizeof(char) * BUFFER_SIZE);
	char ** sentences = malloc(sizeof(char *) * BUFFER_SENTENCES_COUNT);
	for (int i = 0; i < BUFFER_SENTENCES_COUNT; i++)
		sentences[i] = malloc(sizeof(char) * SENTENCE_WORD_BUFFER);
	char * sentence_endings = ".!?";
	strcpy(buffer, buffer_text);

	char * tok = strtok(buffer, sentence_endings);
	while (tok != NULL)
	{
		strcpy(sentences[count], tok);
		count++;
		tok = strtok(NULL, sentence_endings);
	}
	free(buffer);
	// Parse words and build text
	char * word_endings = ", ()\n\'\"";
	for (int i = 0; i < count; i++)
	{
		sentence_t * sentence = malloc(sizeof(sentence_t));
		sentence->words = list_new();
		tok = strtok(sentences[i], word_endings);
		while (tok != NULL)
		{
			if (strlen(tok) == 0)
			{
				tok = strtok(NULL, word_endings);
				continue;
			}
			word_t * word = malloc(sizeof(word_t));
			word->string = malloc(sizeof(char) * WORD_BUFFER);
			strcpy(word->string, tok);
			list_push_back(sentence->words, word);
			tok = strtok(NULL, word_endings);
		}
		list_push_back(text->sentences, sentence);
	}
	for (int i = 0; i < BUFFER_SENTENCES_COUNT; i++)
		free(sentences[i]);
	free(sentences);
	free(buffer_text);
	return text;
}

text_t * text_sentence_filter(text_t * text)
{
	int sentence_count = list_getSize(text->sentences);
	for (int i = 0; i < sentence_count; i++)
	{
		sentence_t * sentence = list_get(text->sentences, i);
		if (list_getSize(sentence->words) < 5)
		{
			sentence_delete(sentence);
			list_remove(text->sentences, i);
			i--;
			sentence_count--;
		}
	}
	return text;
}

list_t * sentence_list_from_text(text_t * text)
{
	return list_new_copy(text->sentences);
}

list_t * word_list_from_sentence(sentence_t * sentence)
{
	return list_new_copy(sentence->words);
}

char * word_to_string(word_t * word)
{
	char * out = malloc(strlen(word->string) + 1);
	strcpy(out, word->string);
	return out;
}

void text_delete(text_t * text)
{
	int count_sentences = list_getSize(text->sentences);
	for (int i = 0; i < count_sentences; i++)
	{
		sentence_t * sentence = list_pop_back(text->sentences);
		sentence_delete(sentence);
	}
	list_free(text->sentences);
}

void sentence_delete(sentence_t * sentence)
{
	int count_words = list_getSize(sentence->words);
	for (int i = 0; i < count_words; i++)
	{
		word_t * word = list_pop_back(sentence->words);
		word_delete(word);
	}
	list_free(sentence->words);
}

void word_delete(word_t * word)
{
	free(word->string);
	free(word);
}
