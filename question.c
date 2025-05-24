#include "question.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Question questions[MAX_QUESTIONS];
static int questionCount = 0;

void LoadQuestions(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return;

    while (fscanf(file, "%127[^\n]\n%63[^\n]\n%63[^\n]\n%d\n",
                  questions[questionCount].text,
                  questions[questionCount].options[0],
                  questions[questionCount].options[1],
                  &questions[questionCount].correctAnswer) == 4) {
        questionCount++;
    }

    fclose(file);
}

Question GetRandomQuestion(void) {
    return questions[rand() % questionCount];
}
