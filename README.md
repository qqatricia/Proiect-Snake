# Proiect-Snake
Colaborantii acestui proiect sunt Stancu Patricia-Ioana(312AC), Mitea Roberta Elena(314AC), Sardaru Miruna-Andreea(314AC), Paraschiv Simona-Georgiana(314AC), Dumitrescu Laura (314AC), Flores-Botezatu Edyra (314AC).

Pentru a rula acest joc tastati in terminal comanda "./main.exe" dupa compilare sau comanda "gcc main.c game.c menu.c snake.c food.c question.c -o main.exe -I. -lraylib -lmingw32 -lgdi32 -lopengl32 -std=c99
" pentru compilare, urmata de comanda "./main.exe".

Distractie placuta!

I. Obiectivele Proiectului
Scopul principal al acestui proiect a fost dezvoltarea unui joc educativ de tip Snake, folosind limbajul de programare C și biblioteca grafică raylib. Jocul adaugă o componentă de tip quiz: de fiecare dată când șarpele mănâncă o bucată de mâncare, utilizatorul trebuie să răspundă la o întrebare pentru a putea continua. Astfel, proiectul combină distracția jocului clasic cu elemente de învățare și testare rapidă a cunoștințelor.

II. Analiză / Documentare („State of the Art”)
Jocul original Snake a fost popularizat de telefoanele mobile Nokia, dar și-a păstrat relevanța în dezvoltarea de jocuri educaționale și interactive, fiind des utilizat ca exercițiu introductiv pentru programare.

În paralel, jocurile de tip quiz au fost aplicate cu succes în educație, pentru a stimula învățarea prin joc. Integrarea celor două tipuri de gameplay (arcade și quiz) este relativ rară, dar oferă oportunități interesante în sfera edutainmentului (educație + divertisment).

III. Justificarea Soluției
Soluția aleasă – implementarea unui joc Snake extins cu întrebări educative – este justificată de:

Simplitatea și popularitatea mecanicii de bază a jocului Snake

Ușurința integrării funcționalităților noi (ex. întrebări) într-un mediu controlat

Accesibilitatea limbajului C și a bibliotecii raylib pentru dezvoltare grafică 2D

Valoarea educativă adăugată prin quiz-uri, care impun pauze de gândire în timpul jocului

IV. Descrierea Implementării
Structura proiectului:
Proiectul este împărțit în mai multe fișiere sursă și antet, pentru modularitate:

main.c
Conține funcția principală main(), care inițializează fereastra grafică cu raylib, încarcă resursele și rulează bucla principală a jocului. Controlează schimbarea între stările de meniu, joc și terminare.

menu.c / menu.h
Gestiune pentru meniul de start. Oferă funcționalitatea de afișare a ecranului de start și de interpretare a comenzilor de pornire (ENTER) sau ieșire (ESC).

game.c / game.h
Implementarea logicii principale a jocului. Aici se întâmplă actualizarea poziției șarpelui, verificarea coliziunilor, afișarea scorului, detectarea coliziunilor cu pereții și integrarea întrebărilor.

snake.c / snake.h
Gestiunea șarpelui: mișcarea acestuia în funcție de direcție, desenarea segmentelor, creșterea în lungime și resetarea jocului în caz de coliziune.

food.c / food.h
Conține funcțiile pentru generarea mâncării în poziții aleatorii, afișarea acesteia pe ecran și verificarea dacă a fost colectată de către șarpe.

question.c / question.h
Se ocupă cu citirea întrebărilor din fișierul questions.txt, afișarea aleatorie a întrebărilor și interpretarea răspunsurilor (prin tastele 1 și 2). Răspunsurile corecte permit continuarea jocului, cele greșite duc la Game Over.

utils.c / utils.h
Include funcții de utilitate, cum ar fi Vector2Equals, folosită pentru compararea pozițiilor. S-a avut grijă să nu se dubleze funcții deja incluse în raylib.

config.h
Fișier de configurare globală. Definește constante precum: SCREEN_WIDTH, SCREEN_HEIGHT, CELL_SIZE, utile pentru dimensionarea graficii și scalarea jocului.

questions.txt
Fișier text extern care conține lista de întrebări în format simplu (întrebare, două opțiuni, răspunsul corect). Acesta este citit dinamic în timpul jocului pentru a genera quiz-ul.

Mecanici de joc:
Jocul începe din meniu, controlat cu tastele ENTER (Start) și ESC (Exit).

Șarpele este controlat cu tastele săgeți.

Când șarpele mănâncă, jocul este pus pe pauză și apare o întrebare.

Jucătorul răspunde apăsând tasta 1 sau 2.

Dacă răspunsul este corect, jocul continuă și șarpele crește.

Dacă răspunsul este greșit, jocul se încheie.

Jocul se oprește și dacă șarpele se lovește de margini sau de el însuși.

V. Concluzii
Proiectul „Snake cu întrebări” combină cu succes o mecanică de joc clasică cu elemente educative, oferind o experiență interactivă și stimulativă. Folosirea limbajului C și a bibliotecii raylib a oferit un bun echilibru între controlul detaliat asupra codului și o interfață grafică accesibilă.

Modularizarea codului a permis o dezvoltare clară și extensibilă, iar separarea logicii de joc, grafică, interacțiune cu utilizatorul și întrebări face ca proiectul să fie ușor de extins sau adaptat în viitor (ex. adăugarea mai multor opțiuni, nivele de dificultate sau categorii de întrebări).
