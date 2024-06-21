#include"jogo.h"

// Gera parede ou chão aleatoriamente, 35% chances de criar parede
int generate_wall(void){
    int a = rand();
    int r = a % 100 + 1;
    if(r > 35) r = 0;
    else r = 1;
    return r;
}

// Conta número de paredes há volta de uma celula (quadrado há sua volta)
int check_n1_walls(char mapa[23][79], int x, int y){
    int n1_walls = 0;
    for(int yy = y - 1; yy <= (y + 1); yy++){ // Inicia na linha acima do ponto (x, y) 
        for(int xx = x - 1; xx <= (x + 1); xx++){
            if(mapa[yy][xx] == '#') n1_walls++;
            if(yy == y) xx++; //Avança verificaçao do ponto (x,y)
        }
    }
    return n1_walls;
}

// Constroi mapa
void fazMapa(char mapa[23][79], int linhas, int colunas){
    // Constroi parede no limite superior e inferior do mapa
    for(int y = 0; y < linhas; y += linhas - 2){
        for(int x = 0; x < colunas; x++){
            mapa[y][x] = '#';
            mvaddch(y, x, '#' | COLOR_PAIR(PAREDE));
        }
    }
    // Constroi parede no limite esquerdo e direito do mapa
    for(int x = 0; x < colunas; x += colunas - 1){
        for(int y = 0; y < linhas - 1; y++){
            mapa[y][x] = '#';
            mvaddch(y, x, '#' | COLOR_PAIR(PAREDE));
        }
    }
    // Gera mapa constituido de paredes ou chão colocados aleatoriamente, exeto nos limites
    for(int y = 1; y < linhas - 2; y++){
        for(int x = 1; x < colunas - 1; x++){
            if(generate_wall()){
                mapa[y][x] = '#';
                mvaddch(y, x, '#');   
            }else{
                mapa[y][x] = '.';
                mvaddch(y, x, '.');
            }
        }
    }
    //Geração do mapa final inspirado no principio da partição de celulas.
    for(int i = 0; i < 2; i++){
        for(int y = 1; y < linhas - 2; y++){
            for(int x = 1; x < colunas - 1; x++){
                int n1_walls = check_n1_walls(mapa, x, y);
                if(mapa[y][x] == '#'){
                    if(n1_walls < 3){
                        mapa[y][x] = '.';
                        mvaddch(y, x, '.' | COLOR_PAIR(APAGADO));
                    }else{
                        mapa[y][x] = '#';
                        mvaddch(y, x, '#' | COLOR_PAIR(PAREDE));
                    }
                }else{
                    if(n1_walls > 4){
                        mapa[y][x] = '#';
                        mvaddch(y, x, '#' | COLOR_PAIR(PAREDE));
                    }else{
                        mapa[y][x] = '.';
                        mvaddch(y, x, '.' | COLOR_PAIR(APAGADO));
                    }
                }
            }
        }
    }
    //Gera linha de chão horizontal para garantir ligação de todo o mapa
    for(int x = 4, y = (linhas / 2); x < colunas - 4; x++){
            mapa[y][x] = '.';
            mvaddch(y, x, '.' | COLOR_PAIR(APAGADO));
        }
}