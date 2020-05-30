// program which implements a pendu game
// the player must guess a word by proposing letters in less than 10 trials

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "pendu.h"

#define WORD_LENGTH 40 //maximum length of string to hold a word
#define DICTIONARY "dictionary.txt"

int main (int argc, char *argv[]) {

    // get secret word from a dictionary
    char secretWord[WORD_LENGTH];
    getSecretWord(secretWord);

    // make the string to be displayed
    // first it is only made of asterisks
    // but will be progressively replaced by letters found by the user
    char displayedWord[WORD_LENGTH] = {0};
    short i = 0;
    for (i = 0; i < strlen(secretWord); i++)
        displayedWord[i] = '*';

    // array to store previously input letter
    char pastLetters[WORD_LENGTH] = {0};

    // mainloop where player inputs a character
    // if the character is present in the secret word, letters are revealed
    // else the count decrements by 1
    short trials = 10;
    short solved = 0; // boolean : did the player found all letters?
    char input = 0; // input character from player

    printf("Welcome to the hungman!\n");

    while (trials > 0 && solved == 0) {

        if (trials > 1)
            printf("\nYou have %d remaining trials.\n", trials);
        else
            printf("\nThis is your last trial!\n");
        
        printf("What is the secret word? %s\n", displayedWord);
        printf("Please enter a letter : ");

        readCharacter(&input);

        // if the input was not previously tried
        if (strchr(pastLetters, input) == NULL) {
            // to copy a character in a chain using strcat(),
            // I first need to put the character in a chain
            char temp[2];
            sprintf(temp, "%c", input);
            strcat(pastLetters, temp);
        }
        else {
            printf("You've already tried \"%c\"!\n", input);
            continue;
        }

        // check if the input character is in the secret word
        char *inSecretWord = NULL;
        inSecretWord = strchr(secretWord, input);

        // if the input letter is in the secret word
        if (inSecretWord != NULL)
                revealCharacters(secretWord, displayedWord, input);

        else {
            printf("\"%c\" is not in the secret word.\n", input);
            trials--;
        }

        // check if secret word was found
        if (strchr(displayedWord, '*') == NULL)
            solved = 1;

    }

    if (solved)
        printf("\n%s\nCongratulations! You've found the secret word!\n", displayedWord);
    else
        printf("\nSorry! You exhausted all your trials!\n");

    return 0;
}

void getSecretWord (char *secretWord) {

    FILE *file = NULL;
    int numberWords = 0; // number of words in the dictionary
    char currentWord[WORD_LENGTH]; // stores the word currently being read
    int randomNumber = 0;
    int i = 0; //iterator when reading the dictionary file

    file = fopen(DICTIONARY, "r");

    if (file == NULL) {
        printf("Error when reading dictionary.txt, exiting program.\n");
        exit(0);
    }

    // calculate the length of the dictionary (one word per line)
    while (fgets(currentWord, WORD_LENGTH, file) != NULL)
        numberWords++;

    // come back to the beginning of the file
    fseek(file, 0, SEEK_SET);

    // read a word at random in the dictionary by choosing a number at random
    // and iterating this number of times when reading lines
    srand(time(NULL));
    randomNumber = rand() % (numberWords + 1);
    for (i = 0; i <= randomNumber; i++) {
        fgets(currentWord, WORD_LENGTH, file);
    }

    fclose(file);

    // remove the new line character at the end of the string
    for (i = 0; i < strlen(currentWord); i++) {
        if (currentWord[i] == '\n')
            currentWord[i] = '\0';
    }
    
    strcpy(secretWord, currentWord);
}

void revealCharacters (char *secretWord, char *displayedWord, char input) {
    int n = strlen(secretWord);
    int i = 0;

    // loop over characters of secret word and reveal input in display word
    for (i = 0; i < n; i++) {
        if (secretWord[i] == input)
            displayedWord[i] = input;
    }
}

void readCharacter (char *inputPtr) {
    *inputPtr = getchar();
    while (getchar() != '\n');
}
