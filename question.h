#ifndef QUESTION_H
#define QUESTION_H

typedef struct {
    char text[128];
    char option1[64];
    char option2[64];
    int correctOption;  // 1 sau 2
} Question;

void LoadQuestions(const char *filename);
Question GetRandomQuestion(void);

#endif
