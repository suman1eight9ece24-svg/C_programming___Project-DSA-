#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

#define ALPHABET 26
#define MAX_WORD 50

// ===================== TRIE STRUCTURE =====================
typedef struct TrieNode {
    struct TrieNode *child[ALPHABET];
    bool terminal;
} TrieNode;

// ===================== CREATE NODE =====================
TrieNode* createNode() {
    TrieNode *node = (TrieNode*)malloc(sizeof(TrieNode));
    for (int i = 0; i < ALPHABET; i++)
        node->child[i] = NULL;
    node->terminal = false;
    return node;
}

// ===================== INSERT WORD =====================
void insertWord(TrieNode *root, const char *word) {
    TrieNode *temp = root;

    for (int i = 0; word[i]; i++) {
        int idx = word[i] - 'a';
        if (temp->child[idx] == NULL)
            temp->child[idx] = createNode();
        temp = temp->child[idx];
    }
    temp->terminal = true;
}

// ===================== RANDOM WORD FROM TRIE =====================
void getRandomWord(TrieNode *node, char *buffer, int depth) {

    // Stop if word end & random choice
    if (node->terminal && rand() % 3 == 0) {
        buffer[depth] = '\0';
        return;
    }

    int choices[ALPHABET];
    int count = 0;

    for (int i = 0; i < ALPHABET; i++) {
        if (node->child[i] != NULL)
            choices[count++] = i;
    }

    if (count == 0) {
        buffer[depth] = '\0';
        return;
    }

    int pick = choices[rand() % count];
    buffer[depth] = pick + 'a';

    getRandomWord(node->child[pick], buffer, depth + 1);
}

void trieGetRandomWord(TrieNode *root, char *word) {
    getRandomWord(root, word, 0);
}

// ===================== HANGMAN GAME =====================
void playHangman(TrieNode *root) {

    char word[MAX_WORD];
    trieGetRandomWord(root, word);

    int len = strlen(word);
    char hidden[MAX_WORD];
    char guessed[26] = {0};
    char wrong[26];
    int wrongCount = 0;

    for (int i = 0; i < len; i++)
        hidden[i] = '_';
    hidden[len] = '\0';

    int life = 6;
    char guess;

    printf("\n--- HANGMAN GAME ---\n");

    while (life > 0) {

        printf("\nWord: ");
        for (int i = 0; i < len; i++)
            printf("%c ", hidden[i]);

        printf("\nLives: %d\n", life);

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
            printf("Invalid input\n");
            continue;
        }

        if (guessed[guess - 'a']) {
            printf("Already guessed\n");
            continue;
        }

        guessed[guess - 'a'] = 1;
        bool found = false;

        for (int i = 0; i < len; i++) {
            if (word[i] == guess) {
                hidden[i] = guess;
                found = true;
            }
        }

        if (!found) {
            wrong[wrongCount++] = guess;
            life--;
            printf("Wrong!\n");
        }

        if (strcmp(hidden, word) == 0) {
            printf("\nYou WIN! Word: %s\n", word);
            return;
        }
    }

    printf("\nYou LOST! Word was: %s\n", word);
}

// ===================== MAIN =====================
int main() {

    srand(time(NULL));

    TrieNode *root = createNode();

    // Insert words
    insertWord(root, "apple");
    insertWord(root, "banana");
    insertWord(root, "orange");
    insertWord(root, "mango");
    insertWord(root, "grapes");
    insertWord(root, "flower");
    insertWord(root, "happy");

    char choice;

    do {
        playHangman(root);
        printf("\nPlay again? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');

    printf("\nThanks for playing!\n");
    return 0;
}
