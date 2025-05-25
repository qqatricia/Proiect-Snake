#include "question.h"
#include <raylib.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX_QUESTIONS 50

static Question questions[MAX_QUESTIONS];
static int currentQuestionIndex = 0;
static int totalQuestions = 0;

// Implementare funcție Clamp
static float Clamp(float value, float min, float max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

void InitQuestions(void) {
    srand((unsigned int)time(NULL));
    
    // Cultura generala
    strcpy(questions[totalQuestions].text, "Care este capitala Romaniei?");
    strcpy(questions[totalQuestions].option1, "Cluj");
    strcpy(questions[totalQuestions].option2, "Bucuresti");
    questions[totalQuestions].correctOption = 2;
    totalQuestions++;

    strcpy(questions[totalQuestions].text, "Cine a scris 'Luceafarul'?");
    strcpy(questions[totalQuestions].option1, "Ion Creanga");
    strcpy(questions[totalQuestions].option2, "Mihai Eminescu");
    questions[totalQuestions].correctOption = 2;
    totalQuestions++;

    strcpy(questions[totalQuestions].text, "Care este cel mai inalt varf muntos din Romania?");
    strcpy(questions[totalQuestions].option1, "Omu");
    strcpy(questions[totalQuestions].option2, "Moldoveanu");
    questions[totalQuestions].correctOption = 2;
    totalQuestions++;

    strcpy(questions[totalQuestions].text, "In ce an a intrat Romania in UE?");
    strcpy(questions[totalQuestions].option1, "2004");
    strcpy(questions[totalQuestions].option2, "2007");
    questions[totalQuestions].correctOption = 2;
    totalQuestions++;

    strcpy(questions[totalQuestions].text, "Care este cel mai lung fluviu din Europa?");
    strcpy(questions[totalQuestions].option1, "Dunarea");
    strcpy(questions[totalQuestions].option2, "Volga");
    questions[totalQuestions].correctOption = 2;
    totalQuestions++;

    // Stiinta
    strcpy(questions[totalQuestions].text, "Care este cel mai abundent element din univers?");
    strcpy(questions[totalQuestions].option1, "Heliul");
    strcpy(questions[totalQuestions].option2, "Hidrogenul");
    questions[totalQuestions].correctOption = 2;
    totalQuestions++;

    strcpy(questions[totalQuestions].text, "Care este cea mai apropiata stea de Pamant?");
    strcpy(questions[totalQuestions].option1, "Proxima Centauri");
    strcpy(questions[totalQuestions].option2, "Soarele");
    questions[totalQuestions].correctOption = 2;
    totalQuestions++;

    strcpy(questions[totalQuestions].text, "Care este cel mai rapid animal terestru?");
    strcpy(questions[totalQuestions].option1, "Leul");
    strcpy(questions[totalQuestions].option2, "Ghepardul");
    questions[totalQuestions].correctOption = 2;
    totalQuestions++;

    // Tehnologie
    strcpy(questions[totalQuestions].text, "Cine a fondat Microsoft?");
    strcpy(questions[totalQuestions].option1, "Steve Jobs");
    strcpy(questions[totalQuestions].option2, "Bill Gates");
    questions[totalQuestions].correctOption = 2;
    totalQuestions++;

    strcpy(questions[totalQuestions].text, "In ce an a fost lansat primul iPhone?");
    strcpy(questions[totalQuestions].option1, "2005");
    strcpy(questions[totalQuestions].option2, "2007");
    questions[totalQuestions].correctOption = 2;
    totalQuestions++;

    // Sport
    strcpy(questions[totalQuestions].text, "Care tara a castigat cele mai multe Cupe Mondiale la fotbal?");
    strcpy(questions[totalQuestions].option1, "Germania");
    strcpy(questions[totalQuestions].option2, "Brazilia");
    questions[totalQuestions].correctOption = 2;
    totalQuestions++;

    strcpy(questions[totalQuestions].text, "Cate cercuri are logo-ul Jocurilor Olimpice?");
    strcpy(questions[totalQuestions].option1, "4");
    strcpy(questions[totalQuestions].option2, "5");
    questions[totalQuestions].correctOption = 2;
    totalQuestions++;

    // Geografie
    strcpy(questions[totalQuestions].text, "Care este cel mai mare ocean?");
    strcpy(questions[totalQuestions].option1, "Atlantic");
    strcpy(questions[totalQuestions].option2, "Pacific");
    questions[totalQuestions].correctOption = 2;
    totalQuestions++;

    strcpy(questions[totalQuestions].text, "Care este cel mai mare desert din lume?");
    strcpy(questions[totalQuestions].option1, "Gobi");
    strcpy(questions[totalQuestions].option2, "Sahara");
    questions[totalQuestions].correctOption = 2;
    totalQuestions++;

    // Istorie
    strcpy(questions[totalQuestions].text, "In ce an s-a terminat al Doilea Razboi Mondial?");
    strcpy(questions[totalQuestions].option1, "1944");
    strcpy(questions[totalQuestions].option2, "1945");
    questions[totalQuestions].correctOption = 2;
    totalQuestions++;

    strcpy(questions[totalQuestions].text, "Cine a fost primul om pe Luna?");
    strcpy(questions[totalQuestions].option1, "Buzz Aldrin");
    strcpy(questions[totalQuestions].option2, "Neil Armstrong");
    questions[totalQuestions].correctOption = 2;
    totalQuestions++;

    // Matematica
    strcpy(questions[totalQuestions].text, "Cat face radical din 144?");
    strcpy(questions[totalQuestions].option1, "14");
    strcpy(questions[totalQuestions].option2, "12");
    questions[totalQuestions].correctOption = 2;
    totalQuestions++;

    strcpy(questions[totalQuestions].text, "Care este valoarea lui Pi (primele 2 zecimale)?");
    strcpy(questions[totalQuestions].option1, "3.16");
    strcpy(questions[totalQuestions].option2, "3.14");
    questions[totalQuestions].correctOption = 2;
    totalQuestions++;

    // Muzica
    strcpy(questions[totalQuestions].text, "Ce instrument canta Gheorghe Zamfir?");
    strcpy(questions[totalQuestions].option1, "Vioara");
    strcpy(questions[totalQuestions].option2, "Nai");
    questions[totalQuestions].correctOption = 2;
    totalQuestions++;

    // Adaugam intrebari noi cu raspunsuri variate
    strcpy(questions[totalQuestions].text, "Care este capitala Frantei?");
    strcpy(questions[totalQuestions].option1, "Paris");
    strcpy(questions[totalQuestions].option2, "Lyon");
    questions[totalQuestions].correctOption = 1;
    totalQuestions++;

    strcpy(questions[totalQuestions].text, "Care este cel mai mare mamifer?");
    strcpy(questions[totalQuestions].option1, "Balena albastra");
    strcpy(questions[totalQuestions].option2, "Elefantul african");
    questions[totalQuestions].correctOption = 1;
    totalQuestions++;

    strcpy(questions[totalQuestions].text, "Cine a pictat Capela Sixtina?");
    strcpy(questions[totalQuestions].option1, "Michelangelo");
    strcpy(questions[totalQuestions].option2, "Leonardo da Vinci");
    questions[totalQuestions].correctOption = 1;
    totalQuestions++;

    strcpy(questions[totalQuestions].text, "Care este cea mai apropiata planeta de Soare?");
    strcpy(questions[totalQuestions].option1, "Mercur");
    strcpy(questions[totalQuestions].option2, "Venus");
    questions[totalQuestions].correctOption = 1;
    totalQuestions++;

    strcpy(questions[totalQuestions].text, "In ce an a fost descoperita America?");
    strcpy(questions[totalQuestions].option1, "1492");
    strcpy(questions[totalQuestions].option2, "1498");
    questions[totalQuestions].correctOption = 1;
    totalQuestions++;

    strcpy(questions[totalQuestions].text, "Care este cel mai mare numar prim sub 10?");
    strcpy(questions[totalQuestions].option1, "7");
    strcpy(questions[totalQuestions].option2, "5");
    questions[totalQuestions].correctOption = 1;
    totalQuestions++;

    strcpy(questions[totalQuestions].text, "Care este viteza sunetului in aer (m/s)?");
    strcpy(questions[totalQuestions].option1, "343");
    strcpy(questions[totalQuestions].option2, "293");
    questions[totalQuestions].correctOption = 1;
    totalQuestions++;

    strcpy(questions[totalQuestions].text, "Care este cel mai mare continent?");
    strcpy(questions[totalQuestions].option1, "Asia");
    strcpy(questions[totalQuestions].option2, "Africa");
    questions[totalQuestions].correctOption = 1;
    totalQuestions++;

    // Adaugam mai multe intrebari noi
    strcpy(questions[totalQuestions].text, "Care este cel mai inalt munte din lume?");
    strcpy(questions[totalQuestions].option1, "K2");
    strcpy(questions[totalQuestions].option2, "Everest");
    questions[totalQuestions].correctOption = 2;
    totalQuestions++;

    strcpy(questions[totalQuestions].text, "Care este cel mai mare animal carnivor terestru?");
    strcpy(questions[totalQuestions].option1, "Ursul polar");
    strcpy(questions[totalQuestions].option2, "Ursul grizzly");
    questions[totalQuestions].correctOption = 1;
    totalQuestions++;

    strcpy(questions[totalQuestions].text, "Care este cel mai lung fluviu din lume?");
    strcpy(questions[totalQuestions].option1, "Amazon");
    strcpy(questions[totalQuestions].option2, "Nil");
    questions[totalQuestions].correctOption = 2;
    totalQuestions++;

    strcpy(questions[totalQuestions].text, "In ce tara se afla Taj Mahal?");
    strcpy(questions[totalQuestions].option1, "India");
    strcpy(questions[totalQuestions].option2, "Pakistan");
    questions[totalQuestions].correctOption = 1;
    totalQuestions++;

    strcpy(questions[totalQuestions].text, "Care este cea mai mare pasare din lume?");
    strcpy(questions[totalQuestions].option1, "Condorul");
    strcpy(questions[totalQuestions].option2, "Strutul");
    questions[totalQuestions].correctOption = 2;
    totalQuestions++;

    strcpy(questions[totalQuestions].text, "Care este cel mai mare peste?");
    strcpy(questions[totalQuestions].option1, "Rechinul alb");
    strcpy(questions[totalQuestions].option2, "Rechinul balena");
    questions[totalQuestions].correctOption = 2;
    totalQuestions++;

    strcpy(questions[totalQuestions].text, "Cine a inventat becul electric?");
    strcpy(questions[totalQuestions].option1, "Thomas Edison");
    strcpy(questions[totalQuestions].option2, "Nikola Tesla");
    questions[totalQuestions].correctOption = 1;
    totalQuestions++;

    strcpy(questions[totalQuestions].text, "Care este cel mai mic stat din lume?");
    strcpy(questions[totalQuestions].option1, "Monaco");
    strcpy(questions[totalQuestions].option2, "Vatican");
    questions[totalQuestions].correctOption = 2;
    totalQuestions++;

    strcpy(questions[totalQuestions].text, "Care este capitala Australiei?");
    strcpy(questions[totalQuestions].option1, "Canberra");
    strcpy(questions[totalQuestions].option2, "Sydney");
    questions[totalQuestions].correctOption = 1;
    totalQuestions++;

    strcpy(questions[totalQuestions].text, "Care este cel mai vandut joc video din istorie?");
    strcpy(questions[totalQuestions].option1, "Tetris");
    strcpy(questions[totalQuestions].option2, "Minecraft");
    questions[totalQuestions].correctOption = 2;
    totalQuestions++;

    strcpy(questions[totalQuestions].text, "Care este elementul chimic cu numarul atomic 1?");
    strcpy(questions[totalQuestions].option1, "Hidrogen");
    strcpy(questions[totalQuestions].option2, "Heliu");
    questions[totalQuestions].correctOption = 1;
    totalQuestions++;

    strcpy(questions[totalQuestions].text, "Care este cea mai populata tara din lume?");
    strcpy(questions[totalQuestions].option1, "India");
    strcpy(questions[totalQuestions].option2, "China");
    questions[totalQuestions].correctOption = 2;
    totalQuestions++;

    strcpy(questions[totalQuestions].text, "Care este cel mai rapid avion din lume?");
    strcpy(questions[totalQuestions].option1, "SR-71 Blackbird");
    strcpy(questions[totalQuestions].option2, "F-22 Raptor");
    questions[totalQuestions].correctOption = 1;
    totalQuestions++;

    strcpy(questions[totalQuestions].text, "Care este cel mai adanc punct din ocean?");
    strcpy(questions[totalQuestions].option1, "Groapa Marianelor");
    strcpy(questions[totalQuestions].option2, "Groapa Java");
    questions[totalQuestions].correctOption = 1;
    totalQuestions++;

    strcpy(questions[totalQuestions].text, "Care este cea mai lunga zi a anului?");
    strcpy(questions[totalQuestions].option1, "22 iunie");
    strcpy(questions[totalQuestions].option2, "21 iunie");
    questions[totalQuestions].correctOption = 2;
    totalQuestions++;

    // Initializam toate intrebarile ca inactive si neraspunse
    for(int i = 0; i < totalQuestions; i++) {
        questions[i].active = false;
        questions[i].answered = false;
    }
}

bool IsQuestionActive(void) {
    return questions[currentQuestionIndex].active;
}

void ShowQuestion(void) {
    // Selectam o intrebare aleatorie
    currentQuestionIndex = rand() % totalQuestions;
    questions[currentQuestionIndex].active = true;
    questions[currentQuestionIndex].answered = false;
}

void DrawQuestion(void) {
    if (!questions[currentQuestionIndex].active) return;

    // Desenăm un fundal semi-transparent cu efect de fade
    static float fadeIn = 0.0f;
    fadeIn = Clamp(fadeIn + GetFrameTime() * 2, 0.0f, 1.0f);
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), 
                 (Color){0, 0, 0, (unsigned char)(200 * fadeIn)});
    
    // Desenăm un panou pentru întrebare cu efect de apariție
    int panelWidth = 600;
    int panelHeight = 300;
    int panelX = (GetScreenWidth() - panelWidth) / 2;
    int panelY = (GetScreenHeight() - panelHeight) / 2;
    
    // Efect de slide-in pentru panou
    float slideOffset = (1.0f - fadeIn) * 200;
    panelY += (int)slideOffset;
    
    // Fundal pentru panou cu gradient și bordură strălucitoare
    DrawRectangle(panelX, panelY, panelWidth, panelHeight, 
                 (Color){20, 20, 20, (unsigned char)(255 * fadeIn)});
    
    // Bordură animată
    float time = (float)GetTime();
    Color borderColor = (Color){
        0,
        (unsigned char)(200 + sinf(time * 4) * 55),
        0,
        (unsigned char)(255 * fadeIn)
    };
    DrawRectangleLines(panelX, panelY, panelWidth, panelHeight, borderColor);
    
    // Desenăm textul întrebării cu efect de fade
    DrawText(questions[currentQuestionIndex].text, 
            panelX + 20, panelY + 30, 25, 
            (Color){255, 255, 255, (unsigned char)(255 * fadeIn)});
    
    // Desenăm opțiunile cu efecte de hover
    Vector2 mousePos = GetMousePosition();
    Rectangle option1Bounds = {panelX + 20, panelY + 100, panelWidth - 40, 40};
    Rectangle option2Bounds = {panelX + 20, panelY + 150, panelWidth - 40, 40};
    
    // Verificăm hover pentru opțiuni
    Color option1Color = WHITE;
    Color option2Color = WHITE;
    
    if (CheckCollisionPointRec(mousePos, option1Bounds)) {
        option1Color = (Color){200, 255, 200, 255};
    }
    if (CheckCollisionPointRec(mousePos, option2Bounds)) {
        option2Color = (Color){200, 255, 200, 255};
    }
    
    // Desenăm fundalul pentru opțiuni
    DrawRectangleRec(option1Bounds, (Color){40, 40, 40, (unsigned char)(200 * fadeIn)});
    DrawRectangleRec(option2Bounds, (Color){40, 40, 40, (unsigned char)(200 * fadeIn)});
    
    // Desenăm textul opțiunilor
    option1Color.a = (unsigned char)(255 * fadeIn);
    option2Color.a = (unsigned char)(255 * fadeIn);
    
    DrawText("1) ", panelX + 30, panelY + 110, 25, DARKGRAY);
    DrawText(questions[currentQuestionIndex].option1,
             panelX + 60, panelY + 110, 25, option1Color);
    
    DrawText("2) ", panelX + 30, panelY + 160, 25, DARKGRAY);
    DrawText(questions[currentQuestionIndex].option2,
             panelX + 60, panelY + 160, 25, option2Color);
    
    // Instrucțiuni
    Color instructionColor = (Color){
        255, 
        255, 
        255, 
        (unsigned char)((0.7f + sinf(time * 2) * 0.3f) * 255 * fadeIn)
    };
    const char* instructionText = "Apasa tasta 1 sau 2 pentru a raspunde";
    int textWidth = MeasureText(instructionText, 20);
    DrawText(instructionText,
             panelX + (panelWidth - textWidth) / 2,
             panelY + panelHeight - 40,
             20, instructionColor);
}

bool HandleQuestionInput(void) {
    if (!questions[currentQuestionIndex].active) return false;

    if (IsKeyPressed(KEY_ONE)) {
        questions[currentQuestionIndex].answered = true;
        questions[currentQuestionIndex].active = false;
        return questions[currentQuestionIndex].correctOption == 1;
    }
    else if (IsKeyPressed(KEY_TWO)) {
        questions[currentQuestionIndex].answered = true;
        questions[currentQuestionIndex].active = false;
        return questions[currentQuestionIndex].correctOption == 2;
    }
    return false;
}

bool IsQuestionAnswered(void) {
    return questions[currentQuestionIndex].answered;
}
