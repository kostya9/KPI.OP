#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "text.h"
#include <string.h>
#include <malloc.h>
int main(void)
 {
	char * buffer_words = malloc(sizeof(char) * BUFFER_SIZE);
	buffer_words[0] = '\0';
	text_t * text = text_from_file("text.txt");
	text = text_sentence_filter(text);
	list_t * sentences = sentence_list_from_text(text);
	size_t sentence_count = list_getSize(sentences);
	for (unsigned int i = 0; i < sentence_count; i++)
	{
		sentence_t * sentence = list_get(sentences, i);
		list_t * words = word_list_from_sentence(sentence);
		size_t word_count = list_getSize(words);
		for (unsigned int k = 0; k < word_count; k++)
		{
			word_t * word = list_get(words, k);
			char * word_str = word_to_string(word);
			strcat(buffer_words, word_str);
			strcat(buffer_words, ", ");
			free(word_str);
		}
		list_free(words);
	}
	list_free(sentences);
	text_delete(text);
	buffer_words[strlen(buffer_words) + 2] = '\0';

	FILE * f = fopen("output.txt", "w+");
	fwrite(buffer_words, sizeof(char), strlen(buffer_words), f);
	fclose(f);
	free(buffer_words);
	_getch();
	return EXIT_SUCCESS;
}