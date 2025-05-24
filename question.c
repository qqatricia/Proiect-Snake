#include "question.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_QUESTIONS 100
#define MAX_LINE_LENGTH 256

static Question questions[MAX_QUESTIONS];
static int totalQuestions = 0;
static int usedIndexes[MAX_QUESTIONS];
static int usedCount = 0;

void LoadQuestions(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Eroare la deschiderea fisierului de intrebari!\n");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    totalQuestions = 0;

    while (fgets(line, sizeof(line), file) && totalQuestions < MAX_QUESTIONS) {
        line[strcspn(line, "\n")] = 0;  // eliminare newline
        char *token = strtok(line, "|");
        if (!token) continue;
        strncpy(questions[totalQuestions].text, token, sizeof(questions[totalQuestions].text));

        token = strtok(NULL, "|");
        if (!token) continue;
        strncpy(questions[totalQuestions].option1, token, sizeof(questions[totalQuestions].option1));

        token = strtok(NULL, "|");
        if (!token) continue;
        strncpy(questions[totalQuestions].option2, token, sizeof(questions[totalQuestions].option2));

        token = strtok(NULL, "|");
        if (!token) continue;
        questions[totalQuestions].correctOption = atoi(token);

        totalQuestions++;
    }

    fclose(file);
    srand(time(NULL));
}

Question GetRandomQuestion() {
    if (totalQuestions == 0) {
        printf("Nu exista intrebari incarcate.\n");
        exit(1);
    }

    if (usedCount == totalQuestions) {
        usedCount = 0; // Resetare când s-au folosit toate întrebările
    }

    int index;
    int alreadyUsed;
    do {
        index = rand() % totalQuestions;
        alreadyUsed = 0;
        for (int i = 0; i < usedCount; i++) {
            if (usedIndexes[i] == index) {
                alreadyUsed = 1;
                break;
            }
        }
    } while (alreadyUsed);

    usedIndexes[usedCount++] = index;
    return questions[index];
}
