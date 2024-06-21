#include "jogo.h"

//FOV

//calcula distância entre jogador e ponto do mapa (usa teorema de pitagoras)
int calc_distancia(int x, int y, int tile_x, int tile_y){
    double dist_x = x - tile_x; 
    double dist_y = y - tile_y;
    dist_x *= dist_x;
    dist_y *= dist_y;

    int distancia = floor(sqrt(dist_x + dist_y)); //floor converte para inteiro
    return distancia;
}

//Verifica se o ponto está dentro do mapa
int is_in_bounds(int tile_x, int tile_y){
    int r = 0;
    if(tile_y > 0 && tile_y < (linhas - 1) && tile_x > 0 && tile_x < colunas) r = 1;
    return r;
}

/* Faz uma linha imaginaria do jogador ao ponto do mapa e caso a mesma encontre uma parede
   antes do ponto, retorna 0 (false) de modo a que o ponto nao seja iluminado */
int linha_de_visao(int x, int y, int tile_x, int tile_y){
    int direçao_x, direçao_y, caminho, r = 0;
    int dist_x = x - tile_x;
    int dist_y = y - tile_y;

    if(dist_x < 0) direçao_x = -1;
    else direçao_x = 1;
    if(dist_y < 0) direçao_y = -1;
    else direçao_y = 1;

    dist_x = abs(dist_x); //Modulo da distância entre x e tile_x
    dist_y = abs(dist_y); //Moludo da distância entre y e tile_y

    // Caminho guarda algoritmo responsável por direcionar a deslocação da linha entre tile e jogador
    if(dist_x > dist_y){
        caminho = dist_y * 2 - dist_x;
        while(mapa[tile_y][tile_x] != '#'){
            if(caminho >= 0){
                tile_y += direçao_y;
                caminho -= dist_x * 2;
            }
            if(mapa[tile_y][tile_x] != '#'){    
                tile_x += direçao_x;
                caminho += dist_y * 2;
                if(tile_x == x && tile_y == y) r = 1;
            }
        }
    }else{
        caminho = dist_x * 2 - dist_y;
        while(mapa[tile_y][tile_x] != '#'){
            if(caminho >= 0){
                tile_x += direçao_x;
                caminho -= dist_y * 2;
            }
            if(mapa[tile_y][tile_x] != '#'){
                tile_y += direçao_y;
                caminho += dist_x * 2;
                if(tile_x == x && tile_y == y) r = 1;
            }
        }
    }
    return r;
}

//Cria campo de visão
void criaFOV(Player *j){
    int raio = 7;
    for(int tile_y = (j->y) - raio; tile_y <= (j->y) + raio; tile_y++){
        for(int tile_x = (j->x) - raio; tile_x <= (j->x) + raio; tile_x++){
            
            int distancia = calc_distancia(j->x, j->y, tile_x, tile_y);
            if(distancia <= raio && is_in_bounds(tile_x, tile_y) && linha_de_visao(j->x, j->y, tile_x, tile_y)){
                if(mapa[tile_y][tile_x] == '.')    
                    mvaddch(tile_y, tile_x, mapa[tile_y][tile_x] | COLOR_PAIR(ILUMINADO));
                else if(mapa[tile_y][tile_x] == 'G')
                    mvaddch(tile_y, tile_x, mapa[tile_y][tile_x] | COLOR_PAIR(GOBLIN));
                else if(mapa[tile_y][tile_x] == 'H')
                    mvaddch(tile_y, tile_x, mapa[tile_y][tile_x] | COLOR_PAIR(VIDA));
                else if(mapa[tile_y][tile_x] == 'A' || mapa[tile_y][tile_x] == 'S')
                    mvaddch(tile_y, tile_x, mapa[tile_y][tile_x] | COLOR_PAIR(ITEMS));
                else if(mapa[tile_y][tile_x] == '&')
                    mvaddch(tile_y, tile_x, mapa[tile_y][tile_x] | COLOR_PAIR(BOSS));
            }
        }
    }
}

//Apaga FOV (para depois ser formado novo FOV após movimento do jogador)
void apagaFOV(Player *j){
    int raio = 7;
    for(int tile_y = (j->y) - raio; tile_y <= (j->y) + raio; tile_y++){
        for(int tile_x = (j->x) - raio; tile_x <= (j->x) + raio; tile_x++){
            if(is_in_bounds(tile_x, tile_y)){
                if(mapa[tile_y][tile_x] != '#')
                    mvaddch(tile_y, tile_x, mapa[tile_y][tile_x] | COLOR_PAIR(APAGADO));
            }
        }
    }
}