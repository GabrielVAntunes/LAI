#include"jogo.h"

void createItems(void){

    for(int i = 0; i < 5; i++){
        int spawn_x = 0, spawn_y = 0;
        //Randomiza Spawn da Vida
        //Randomiza até não estar numa parede
        while(mapa[spawn_y][spawn_x] != '.'){
            int a = rand();
            spawn_x = a % colunas;
            spawn_y = a % (linhas - 1);
        }
        mapa[spawn_y][spawn_x] = 'H';
    }
    for(int i = 0; i < 1; i++){
        int spawn_x = 0, spawn_y = 0;
        //Randomiza Spawn da Armadura
        //Randomiza até não estar numa parede
        while(mapa[spawn_y][spawn_x] != '.'){
            int a = rand();
            spawn_x = a % colunas;
            spawn_y = a % (linhas - 1);
        }
        mapa[spawn_y][spawn_x] = 'A';
    }
    for(int i = 0; i < 1; i++){
        int spawn_x = 0, spawn_y = 0;
        //Randomiza Spawn da Espada
        //Randomiza até não estar numa parede
        while(mapa[spawn_y][spawn_x] != '.'){
            int a = rand();
            spawn_x = a % colunas;
            spawn_y = a % (linhas - 1);
        }
        mapa[spawn_y][spawn_x] = 'S';
    }
}