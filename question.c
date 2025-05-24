#include "question.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_QUESTIONS 100

static Question questions[MAX_QUESTIONS];
static int questionsCount = 0;

void LoadQuestions(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Nu am putut incarca intrebari din %s\n", filename);
        return;
    }
    questionsCount = 0;
    srand(time(NULL));

    char line[512];
    while (fgets(line, sizeof(line), f) && questionsCount < MAX_QUESTIONS) {
        char *token = strtok(line, ";");
        if (!token) continue;
        strncpy(questions[questionsCount].question, token, 255);
        token = strtok(NULL, ";");
        if (!token) continue;
        strncpy(questions[questionsCount].option1, token, 99);
        token = strtok(NULL, ";");
        if (!token) continue;
        strncpy(questions[questionsCount].option2, token, 99);
        token = strtok(NULL, ";");
        if (!token) continue;
        questions[questionsCount].correctOption = atoi(token);
        questionsCount++;
    }
    fclose(f);
}

int GetQuestionsCount(void) {
    return questionsCount;
}

Question GetRandomQuestion(int excludeIndex) {
    if (questionsCount == 0) {
        Question q = {"Nicio intrebare disponibila", "N/A", "N/A", 1};
        return q;
    }
    int idx;
    do {
        idx = rand() % questionsCount;
    } while (idx == excludeIndex && questionsCount > 1);
    return questions[idx];
}

void UnloadQuestions(void) {
    questionsCount = 0;
}
