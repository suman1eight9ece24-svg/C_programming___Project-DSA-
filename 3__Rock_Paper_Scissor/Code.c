#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

// Function prototypes
int get_user_choice();
int get_computer_choice();
void determine_winner(int user, int computer, int *user_score, int *computer_score);
void print_choices(int choice);
void print_final_result(int user_score, int computer_score);

int main() {
    int user_choice, computer_choice;
    int user_score = 0, computer_score = 0;
    char play_again;
    int rounds = 0;
    
    srand(time(0));
    
    printf("=============== Welcome to Rock-Paper-Scissors ===============\n");
    printf("!! Enter  :-\n 1 for Rock,\n 2 for Paper,\n 3 for Scissors\n");
    printf("--------------------------------------------------------------\n");
    do {
        rounds++;
        printf("\nRound %d\n", rounds);
        
        user_choice = get_user_choice();
        computer_choice = get_computer_choice();
        
        printf("\nYou chose: ");
        print_choices(user_choice);
        printf("Computer chose: ");
        print_choices(computer_choice);
        
        determine_winner(user_choice, computer_choice, &user_score, &computer_score);
        
        printf("\nCurrent Scores - You: %d, Computer: %d\n", user_score, computer_score);
        
        printf("\nDo you want to play again? (y/n): ");
        scanf(" %c", &play_again);
        play_again = tolower(play_again); // make the charcter Lower Alphabet 
        
        while (getchar() != '\n');
        
    } while (play_again == 'y');
    
    print_final_result(user_score, computer_score);
    
    return 0;
}

int get_user_choice() {
    int choice;
    
    while (1) {
        printf("Your choice (1=Rock, 2=Paper, 3=Scissors): ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }
        
        if (choice >= 1 && choice <= 3) {
            return choice;
        } else {
            printf("Invalid choice. Please enter 1, 2, or 3.\n");
        }
    }
}

int get_computer_choice() {
    return rand() % 3 + 1; // Returns 1, 2, or 3
}

void determine_winner(int user, int computer, int *user_score, int *computer_score) {
    if (user == computer) {
        printf("It's a tie!\n");
        return;
    }
    
    // Rock (1) <- Scissors (3)
    // Paper (2) <- Rock (1)
    // Scissors (3) <- Paper (2)
    if (user == 1 && computer == 3){
        printf("You win this round!\n");
        (*user_score)++;
    } 
    else if (user == 2 && computer == 1){
        printf("You win this round!\n");
        (*user_score)++;
    }
    else if (user == 3 && computer == 2){
        printf("You win this round!\n");
        (*user_score)++;
    } 
    else {
        printf("Computer wins this round!\n");
        (*computer_score)++;
    }
}

void print_choices(int choice) {
    switch (choice) {
        case 1: printf("Rock\n"); break;
        case 2: printf("Paper\n"); break;
        case 3: printf("Scissors\n"); break;
        default: printf("Unknown choice\n");
    }
}

void trophy(){
#define GOLD   "\033[1;33m"   // Bright Yellow (Gold)
#define RESET  "\033[0m"

printf(GOLD "      _______\n");
printf(GOLD "     |       |\n");
printf(GOLD "   __|  WIN  |__\n");
printf(GOLD "  |  \\_____/   |\n");
printf(GOLD "  \\            /\n");
printf(GOLD "   \\__________/\n");
printf(GOLD "         |\n");
printf(GOLD "       __|__\n");
printf(GOLD "      |_____|\n" RESET);

}

void lose(){
#define WHITE  "\033[1;37m"
#define RESET  "\033[0m"

printf(WHITE "#         ####    ####    ####\n");
printf(WHITE "#        #    #  #    #  #\n");
printf(WHITE "#        #    #  #    #   ###\n");
printf(WHITE "#        #    #  #    #      #\n");
printf(WHITE "######    ####    ####    ####\n" RESET);
}

void Draw(){
#define RED    "\033[1;31m"
#define RESET  "\033[0m"

printf(RED "  ###   ###\n");
printf(RED " ##### #####\n");
printf(RED " ###########\n");
printf(RED "  #########\n");
printf(RED "    #####\n");
printf(RED "      #\n" RESET);

}

void print_final_result(int user_score, int computer_score) {
    printf("\nFinal Scores - You: %d, Computer: %d\n", user_score, computer_score);
    
    if (user_score > computer_score) {
        printf("Congratulations! You are the overall winner!\n");
        trophy();
    } else if (computer_score > user_score) {
        printf("The computer is the overall winner. Better luck next time!\n");
        lose();
    } else {
        printf("The game ended in a tie!\n");
        Draw();
    }
    
    printf("\nThanks for playing!\n");
}
