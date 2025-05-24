#ifndef QUESTION_H
#define QUESTION_H

#include <stdbool.h>

typedef struct Question {
    char question[256];
    char option1[100];
    char option2[100];
    int correctOption; // 1 or 2
} Question;

void LoadQuestions(const char *filename);
int GetQuestionsCount(void);
Question GetRandomQuestion(int excludeIndex);
void UnloadQuestions(void);

#endif
