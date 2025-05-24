#ifndef MENU_H
#define MENU_H

#include <stdbool.h>

void InitMenu(void);
void UpdateMenu(void);
void DrawMenu(void);
bool IsGameStarted(void);
bool IsExitRequested(void);

#endif // MENU_H
