#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

int main() {
    char words[][20] = {"apple", "banana", "orange", "mango", "grapes"};
    int numWords = sizeof(words) / sizeof(words[0]);

    srand(time(NULL));

    while (1) {   // ===== GAME LOOP =====

        int index = rand() % numWords;
        char word[20];
        strcpy(word, words[index]);

        int len = strlen(word);
        char hidden[20];
        char guessed[26] = {0};
        char wrong[26] = {0};
        int wrongCount = 0;

        for (int i = 0; i < len; i++)
            hidden[i] = '_';
        hidden[len] = '\0';

        int life = 6;
        char guess;
        int correct;

        printf("\n--- HANGMAN GAME STARTED ---\n");

        while (life > 0) {
            correct = 0;

            printf("\nWord: ");
            for (int i = 0; i < len; i++)
                printf("%c ", hidden[i]);

            printf("\nLives left: %d\n", life);

            if (wrongCount > 0) {
                printf("Wrong guesses: ");
                for (int i = 0; i < wrongCount; i++)
                    printf("%c ", wrong[i]);
                printf("\n");
            }

            printf("Enter a letter: ");
            scanf(" %c", &guess);
            guess = tolower(guess);

            if (!isalpha(guess)) {
                printf("Invalid input. Enter a letter only.\n");
                continue;
            }

            if (guessed[guess - 'a']) {
                printf("You already guessed '%c'. Try another.\n", guess);
                continue;
            }

            guessed[guess - 'a'] = 1;

            for (int i = 0; i < len; i++) {
                if (word[i] == guess) {
                    hidden[i] = guess;
                    correct = 1;
                }
            }

            if (!correct) {
                wrong[wrongCount++] = guess;
                life--;
                printf("Wrong guess!\n");
            } else {
                printf("Correct guess!\n");
            }

            if (strcmp(hidden, word) == 0) {
                printf("\nYou guessed the word: %s\n", word);
                printf("You WIN!\n");
                break;
            }
        }

        // ===== LOSS HANDLING =====
        if (life == 0) {
            char choice;
            printf("\nYou LOST!\n");
            printf("The word was: %s\n", word);
            printf("Do you want to play again? (y/n): ");
            scanf(" %c", &choice);

            if (choice == 'y' || choice == 'Y') {
                continue;   // restart game
            } else {
                printf("\nThanks for playing!\n");
                break;      // exit program
            }
        }
    }

    return 0;
}
