#include <stdio.h>
#include "hangman.h"
#include <time.h>
#include <stdlib.h>
int main(){
srand(time(NULL));
    char secretnoe_slovo[15];
    int a = get_word(secretnoe_slovo); 
    hangman(secretnoe_slovo);
    return a;
}