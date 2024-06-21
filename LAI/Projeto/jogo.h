#ifndef JOGO_H
#define JOGO_H

#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

//Definir cores
#define ILUMINADO 1
#define APAGADO 2
#define PAREDE 3
#define JOGADOR 4
#define HP 5
#define MENU 6
#define GOBLIN 7
#define VIDA 8
#define ITEMS 9
#define BOSS 10

//Struct Player
typedef struct{
    int y;
    int x;
    int hp;
    int def;
    int atk;
    char sprite;
} Player;

//Struct Mobs
typedef struct{
    int y;
    int x;
    int hp;
} Mobs;

//Struct Boss
typedef struct{
    int y;
    int x;
    int hp;
} Boss;

//Funcções do mapa.c
void fazMapa(char mapa[23][79], int linhas, int colunas);

//Funções do fov.c
void criaFOV(Player *j);
void apagaFOV(Player *j);

//Funções de jogador.c
void createPlayer(Player *j, int linhas, int colunas);
int movimento(Player *j ,int input, int new_xy[]);
int colisionCheck(Player *j, int new_x, int new_y);
void combate(Player *j, Mobs *goblins, Boss *b, int n, int new_xy[]);

//Funções de mobs.c
void createMob(Mobs *goblins, int n, int linhas, int colunas);
void movimento_mobs(Mobs *goblins, Player *j, int n);
void createBoss(Boss *b, int linhas, int colunas);
void movimento_boss(Boss *b, Player *j);

//Funções de items
void createItems(void);

//Variaveis externas
extern int linhas, colunas;
extern char mapa[23][79];

#endif