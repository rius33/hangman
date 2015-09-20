#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>


/*
 * linked list data structure definitions
 */
struct _wordnode {
    char word[256];
    struct _wordnode *next;
};
typedef struct _wordnode wordnode;


/*
 * Be happy you didn't have to write this function.
 * Prints a low-tech ASCII gallows.  Max number of misses
 * is 7 (i.e., if there are 7 misses, the player loses and
 * the poor sap gets hung).  
 */
void print_gallows(int num_missed) {
    // make sure that we got called in a reasonable way
    assert(num_missed >= 0 && num_missed <= 7);

    printf("\n\n       |||========|||\n");
    if (num_missed > 0) {
        printf ("       |||         |\n");
    } else {
        printf ("       |||          \n");
    }

    if (num_missed > 1) {
        printf ("       |||         O\n");
    } else {
        printf ("       |||          \n");
    }

    if (num_missed > 2) {
        if (num_missed > 4) {
            printf ("       |||        /|\\\n");
        } else if (num_missed > 3) {
            printf ("       |||        /| \n");
        } else {
            printf ("       |||        /  \n");
        }
    } else {
        printf ("       |||           \n");
    }

    if (num_missed > 5) {
        if (num_missed > 6) {
            printf ("       |||        / \\\n");
        } else {
            printf ("       |||        /  \n");
        }
    } else {
        printf ("       |||           \n");
    }

    printf ("       |||\n");
    printf ("       |||\n");
    printf ("     =================\n\n");
}

/*
 * Play one game of Hangperson.  The secret word is passed as a
 * parameter.  The function should return true if the player won,
 * and false otherwise.
 */
bool one_game(const char *word) {

    
}

/* 
 * wordbank-related functions. please don't change the
 * function prototypes for these three functions.
 * load_words takes the name of the file that should be
 * opened and words read from, and a pointer to an int
 * that should be indirectly modified to store the number
 * of words loaded from the file.  The function should 
 * return the linked list of words.
 */
wordnode *load_words(const char *filename, int *num_words) {
        num_words = 0;
        FILE * fp = fopen(filename, "r");
        wordnode * list;
        wordnode * head = NULL;
        char str[256];
        while (fgets(str, 256, fp) != NULL) {
            str[strlen(str) - 1] = '\0';
            int alpha = 1;
            for (int i = 0; i < strlen(str); i++){ 
                if (!isalpha(str[i])) {
                    alpha = 0;
                }
                str[i] = toupper(str[i]);
            }
            if (alpha == 1) {
                if (head == NULL){
                    head = malloc(sizeof(char) *257);
                    strcpy(head->word,str);
                    list = head;
                    }
                else{
                    strcpy(list->word,str);
                    list->next = malloc(sizeof(char)*257);
                    list=list->next;
                    }
                //printf("%s\n", str);
                num_words++;
            }
        }
        printf("%d\n", num_words);
        printf("%s\n", head->word);
        printf("%s\n", list->word);
        list = head;
        while (list != NULL) {
            printf("%s\n", list->word);
        }
        return head;
    }

wordnode * list_append(char name, wordnode *list) {
    wordnode *newnode = malloc(sizeof(char)*257);
    strcpy(newnode->word, name);
    newnode->next = NULL;
    wordnode *head = list;
    if (head == NULL) {
        head = newnode;
        return head;
    }
    while (list->next != NULL) {
        list = list->next;
    }
    list->next = newnode;
    return head;
    
}

/*
 * Completely free and deallocate the linked list of words.
 */
void free_words(wordnode *wordlist) {
    while (wordlist != NULL) {
        wordnode *tmp = wordlist;
        wordlist = wordlist->next;
        free(tmp);
    }
}

/*
 * Choose one random word from the linked list and return it.
 */
const char *choose_random_word(wordnode *wordlist, int num_words) {
    
}


/*
 * The main function is where everything starts.  Choose a random
 * word and call one_game.  Start first on getting the word-loading
 * to work correctly, then handle the game playing capabilities.
 */
#ifndef AUTOTEST
int main() {
    srandom(time(NULL));
    int num_words = 0;
    wordnode *words = load_words("/usr/share/dict/words", &num_words);
    if (num_words == 0) {
        printf("Didn't load any words?!\n");
        return 0;
    }
    char *word = choose_random_word(words, num_words);
    one_game(word);
    free_words(words);
    return 0;
}
#endif
