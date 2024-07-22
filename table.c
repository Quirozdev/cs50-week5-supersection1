#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 26

typedef struct node
{
    string phrase;
    struct node *next;
}
node;

node *table[SIZE];

int hash(string phrase);
bool unload(node *table[SIZE]);
void visualizer(node *table[SIZE]);

int main(void)
{
    // Add items
    for (int i = 0; i < 3; i++)
    {
        string phrase = get_string("Enter a new phrase: ");

        // Find phrase bucket
        int bucket = hash(phrase);
        printf("%s hashes to %i\n", phrase, bucket);

        node *n = malloc(sizeof(node));
        n->phrase = phrase;
        n->next = table[bucket];
        table[bucket] = n;
    }
    visualizer(table);
    unload(table);
}

// TODO: return the correct bucket for a given phrase
int hash(string phrase)
{
    return tolower(phrase[0]) - 'a';
}

bool unload(node *table[SIZE]) 
{
    node* ptr;
    for (int i = 0; i < SIZE; i++) {
        while (table[i] != NULL) {
            ptr = table[i]->next;
            free(table[i]);
            table[i] = ptr;
        }
    }
    return true;
}

void visualizer(node *table[SIZE])
{
    node* ptr;
    for (int i = 0; i < SIZE; i++) {
        printf("[%i]\t->\t", i);
        ptr = table[i];
        while (ptr != NULL) {
            printf("%s, ", ptr->phrase);
            ptr = ptr->next;
        }
        printf("\n");
    }
    printf("\n");
}
