#ifndef QUESTION_H
#define QUESTION_H

#include <stdbool.h>

typedef struct Question {
    char text[256];
    char option1[128];
    char option2[128];
    int correctOption; // 1 sau 2
    bool active;
    bool answered;
} Question;

void InitQuestions(void);
bool IsQuestionActive(void);
void ShowQuestion(void);
void DrawQuestion(void);
bool HandleQuestionInput(void);
bool IsQuestionAnswered(void);

#endif // QUESTION_H
