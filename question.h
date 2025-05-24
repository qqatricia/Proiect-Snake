#ifndef QUESTION_H
#define QUESTION_H

#define MAX_QUESTIONS 50

typedef struct {
    char text[128];
    char options[2][64];
    int correctAnswer;
} Question;

void LoadQuestions(const char *filename);
Question GetRandomQuestion(void);

#endif
