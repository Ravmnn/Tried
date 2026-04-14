#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <tried/node.h>



void validate_input(const char* const input);




char* read_input()
{
  char* buffer = malloc(MAX_WORD_LENGTH + 1);

  if (!fgets(buffer, MAX_WORD_LENGTH + 1, stdin))
    return NULL;

  validate_input(buffer);

  return buffer;
}


void validate_input(const char* const input)
{
  char* const newline = strchr(input, '\n');

  if (newline)
    *newline = '\0';
  else
    printf("Max input size is %d characters\n", MAX_WORD_LENGTH);
}





int main(void)
{
  Node* sources[4] = { node_create_from_word("projeto"),
                      node_create_from_word("progresso"),
                      node_create_from_word("profundo"),
                      node_create_from_word("proposta") };

  Node* main_node = node_create_from_word("programa");
  node_merge(main_node, sources, 5);

  return 0;
}
