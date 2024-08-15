#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "hangman.h"
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

int is_word_guessed(const char secret[], const char letters_guessed[]){
    for(int i = 0;i < strlen(secret);i++){
        bool found = 0;
        for(int j = 0;j < strlen(letters_guessed);j++){
            if(secret[i] == letters_guessed[j]){
                found = 1;
                break;
            }
        }
        if(!found){
            return 0;
        }
    }
    return 1;
}

void get_guessed_word(const char secret[], const char letters_guessed[], char guessed_word[]){
    for(int i = 0; i < strlen(secret);i++){
        int found = 0;
        for(int j = 0;j < strlen(letters_guessed);j++){
            if(secret[i]==letters_guessed[j]){
                found = 1;
                guessed_word[i] = secret[i];   
                break;     
            }
            
            }
            if(found == 0){
                guessed_word[i] = '_';
            }
            guessed_word[strlen(secret)] = '\0';
        }
        printf("%s\n",guessed_word);
    }


void get_available_letters(const char letters_guessed[], char available_letters[]){
         int index = 0;
         char alphabet[] = "abcdefghijklmnopqrstuvwxyz"; 

     for (int i = 0; i < strlen(alphabet); i++) {
        bool found = 0;
        for (int j = 0; j < strlen(letters_guessed); j++) {
            if (alphabet[i] == letters_guessed[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            available_letters[index++] = alphabet[i];
        }
    }
    available_letters[index] = '\0';  
}
    void hangman(const char secret[]){
    int guesses_left = 8;
    char letters_guessed[27];
    char guessed_word[100];
    
    printf("Welcome to the game, Hangman!\n");
    printf("I am thinking of a word that is %ld letters long.\n",strlen(secret));
    char available_letters[27] = "abcdefghijklmnopqrstuvwxyz\0";

    while(guesses_left > 0){
        printf("-------------\n");
        printf("You have %d guesses left.\n", guesses_left);

        get_available_letters(letters_guessed, available_letters);
        printf("Available letters: %s\n", available_letters);

        char guess[100];
        printf("Please guess a letter: ");
        scanf("%s", guess);

        if(strlen(guess) > 1){
            if (strcmp(guess, secret) == 0){
                printf("Congratulations, you won!\n");
            } 
            else{
                printf("Sorry, bad guess. The word was %s.\n", secret);
            }
            return;
        }

        char letter = tolower(guess[0]);

        if(!isalpha(letter)){ 
            printf("Oops! '%c' is not a valid letter. Please enter a letter.\n", letter);
            continue;
        }

        if(strchr(letters_guessed, letter)){ 
            printf("Oops! You've already guessed that letter: ");
        } 
            else{
            char letter_str[2] = { letter, '\0' };
            strcat(letters_guessed, letter_str);

            if(strchr(secret, letter)){
                printf("Good guess: ");
            } 
            else{
                printf("Oops! That letter is not in my word: ");
                guesses_left--;
            }
        }
        //printf("%s\n",letters_guessed);
        get_guessed_word(secret, letters_guessed, guessed_word);
       //printf("%s\n", guessed_word);

        if(is_word_guessed(secret, letters_guessed)){ 
            printf("Congratulations, you won!\n");
            break;
        }
    }

    printf("-------------\n");
    printf("Sorry, you ran out of guesses. The word was %s.\n", secret);
}

int get_word(char secret[]){
    // check if file exists first and is readable
    FILE *fp = fopen(WORDLIST_FILENAME, "rb");
    if( fp == NULL ){
        fprintf(stderr, "No such file or directory: %s\n", WORDLIST_FILENAME);
        return 1;
    }

    // get the filesize first
    struct stat st;
    stat(WORDLIST_FILENAME, &st);
    long int size = st.st_size;

    do{
        // generate random number between 0 and filesize
        long int random = (rand() % size) + 1;
        // seek to the random position of file
        fseek(fp, random, SEEK_SET);
        // get next word in row ;)
        int result = fscanf(fp, "%*s %20s", secret);
        if( result != EOF )
            break;
    }while(1);

    fclose(fp);

    return 0;
}
