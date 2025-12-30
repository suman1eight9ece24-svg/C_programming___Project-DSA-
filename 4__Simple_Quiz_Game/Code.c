#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include<stdlib.h>
#include<time.h>
//------------------
#ifdef _WIN32
#include <windows.h>
#endif
//------------------
void wrongSound() {
#ifdef _WIN32
    Beep(1000, 80);
#else
    printf("\a");
#endif
}
//------------------

//============================ Stop Watch Code ====================================
void displayTime(long seconds) {
    int h = seconds / 3600;
    int m = (seconds % 3600) / 60;
    int s = seconds % 60;
    printf("Time Taken: %02d:%02d:%02d\n", h, m, s);
}
//=================================================================================

#define MAX_Q 50    // max number of questions
#define MAX_LEN 200 // max lengtha of each line

typedef struct {
    char question[MAX_LEN];
    char options[4][MAX_LEN];
    char answer;
} Quiz;

int main() {
    FILE *fp = fopen("questions.txt", "r");
    if (!fp) {
        printf("Error: Cannot open file!\n");
        return 1;
    }

    Quiz quiz[MAX_Q];
    int count = 0;
    char line[MAX_LEN];

    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "Question:", 9) == 0) {
            strcpy(quiz[count].question, line + 10);

            for (int i = 0; i < 4; i++) {
                fgets(line, sizeof(line), fp);
                strcpy(quiz[count].options[i], line);
            }

            fgets(line, sizeof(line), fp); // Answer line
            sscanf(line, "Answer: %c", &quiz[count].answer);
            count++;
        }
    }
    fclose(fp);

    // Quiz loop
    int score = 0;
    char userAns;
    printf("===== QUIZ GAME =====\n");
    // START STOPWATCH
    time_t startTime = time(NULL);

    for (int i = 0; i < count; i++) {
        printf("\nQ%d: %s", i + 1, quiz[i].question);
        for (int j = 0; j < 4; j++) {
            printf("%s", quiz[i].options[j]);
        }
        printf("Your answer (A/B/C/D): ");
        scanf(" %c", &userAns);

        if (toupper(userAns) == toupper(quiz[i].answer)) {
            printf("Correct!\n");
            score++;
        } else {
            wrongSound(); // Beep sound
            printf("Wrong! Correct answer: %c\n", quiz[i].answer);
            Sleep(500);
        }
    }
        // STOP STOPWATCH
    time_t endTime = time(NULL);

        long totalSeconds = (long)difftime(endTime, startTime);

    printf("\n=====================\n");
    printf("Quiz Finished!\n");
    printf("Score: %d / %d\n", score, count);
    displayTime(totalSeconds);
    return 0;
}
