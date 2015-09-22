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

int checkguess(char guess[], char guessed[], char word[]){
    if(strlen(guess)>1){
        printf("Just one letter, silly anxious player\n");
        return 0;
    } else if(!isalpha(guess[0])){
        printf("How about a letter. Seriously.\n");
        return 0;
    } else if((strcasestr(guessed, guess)) != NULL){
        printf("You already guessed %c\n", guess[0]);
        return 0;
    } else if ((strcasestr(word, guess)) == NULL){
        printf("Bad guess. You stink\n");
        return 1;
    } else {
        return 2;
    }
    
}

/*
 * Play one game of Hangperson.  The secret word is passed as a
 * parameter.  The function should return true if the player won,
 * and false otherwise.
 */
bool one_game(const char *word) {
    int secret_len = strlen(word);
    int num_missed = 0;
    char secret[secret_len];
    for (int i = 0; i < secret_len; i++){
        secret[i] = 95;
    }
    secret[secret_len] = '\0';
    char guessed[27] = "";
    while (num_missed < 7) {
        printf("%s\nMissed: %d\n", word, num_missed);
        print_gallows(num_missed);
        for (int i = 0; i < strlen(secret); i++){
            printf("%c ", secret[i]);
        }
        printf("\n");
        if (strlen(guessed) == 0) {
            printf("Already guessed: (none)\n");
        } else {
            printf("Already guessed: %s\n", guessed);
        }
        printf("Enter your guess: ");
        char guess[128];
        fgets(guess, 128, stdin);
        guess[strlen(guess) - 1] = '\0';
        int guessres =  checkguess(guess, guessed, word);
        if (guessres == 2) {
            strcat(guessed, guess);
            for (int i = 0; i < strlen(word); i++){
                if (toupper(guess[0]) == word[i]) {
                    secret[i] = toupper(guess[0]);
                }
            }
        } else if (guessres == 1) {
            num_missed++;
            strcat(guessed, guess);
        }
        int endif = 0;
        for (int j = 0; j < strlen(secret); j++){
            if (secret[j] == '_'){
                endif++;
            }   
        }
        if (endif == 0) {
            printf("Congratulations, you've won! The word was %s.\n", word);
            return true;
        }
    }
    print_gallows(7);
    printf("Sorry, you've lost...The word was %s.\n", word);
    return false;
}

bool checkword(char str[]) {
    str[strlen(str) - 1] = '\0';
    for (int i = 0; i < strlen(str); i++) {
       if (!isalpha(str[i])) return false;
       str[i] = toupper(str[i]);
    }
    return true;
}

wordnode * append_to_list(wordnode * list, char str[256]) {
    wordnode * new = malloc(sizeof(char)*257);
    strcpy(new->word, str);
    new->next = NULL;
    list->next = new;
    return list->next;
}

void print_list(wordnode * head) {
    wordnode * list = head;
    while (list != NULL) {
        printf("%s\n", list->word);
        list = list-> next;
    }
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
        FILE * fp = fopen(filename, "r");
        char str[256];
        wordnode * head = malloc(sizeof(char)*257);
        fgets(str,256, fp);
        checkword(str);
        strcpy(head->word, str);
        head->next = NULL;
        wordnode * list = head;
        while (fgets(str, 256, fp) != NULL){
            if (checkword(str)) {
                *num_words += 1;
                list = append_to_list(list, str);    
            }
        }
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
    int rand = random();
    rand = rand % num_words;
    for (int i = 0; i < rand; i++){
        wordlist = wordlist->next;
    }
    const char * word[256];
    strcpy(word, wordlist->word);
    return word;
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
