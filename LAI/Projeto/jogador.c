#include"jogo.h"
//Init jogador
void createPlayer(Player *j, int linhas, int colunas){
    int spawn_x = 0, spawn_y = 0;
    //Randomiza Spawn do jogador
    //Randomiza até nao estar numa parede
    while(mapa[spawn_y][spawn_x] != '.'){
        int a = rand();
        spawn_x = a % colunas;
        spawn_y = a % (linhas - 1);
    }
    j->x = spawn_x;
    j->y = spawn_y;
    j->hp = 10;
    j->def = 0;
    j->atk = 1;
    j->sprite = '0';
    mapa[spawn_y][spawn_x] = '0';
}
//Calcula nova posição do jogador
int movimento(Player *j ,int input, int new_xy[]){
    int new_x = j->x, new_y = j->y;
    switch(input){
        case 'w':
            new_y--;
            break;
        case 's':
            new_y++;
            break;
        case 'a':
            new_x--;
            break;
        case 'd':
            new_x++;
            break;
        default:
            break;
    }
    int r = colisionCheck(j, new_x, new_y);

    new_xy[0] = new_x;
    new_xy[1] = new_y;
    
    return r;
}
//Verifica se player pode andar ou colide com algo
int colisionCheck(Player *j, int new_x, int new_y){
    int r = 1;
    if(mapa[new_y][new_x] == '.' || mapa[new_y][new_x] == 'H' 
    || mapa[new_y][new_x] == 'A' || mapa[new_y][new_x] == 'S'){

        if(mapa[new_y][new_x] == 'H'){
            for(int i = 0; i < 3 && j->hp < 10; i++)
                j->hp++;
        }
        else if(mapa[new_y][new_x] == 'A') j->def++;
        else if(mapa[new_y][new_x] == 'S') j->atk++;
        
        mapa[j->y][j->x] = '.';
        j->x = new_x;
        j->y = new_y;
        mapa[new_y][new_x] = '0';

    }else if(mapa[new_y][new_x] != '#'){
        /* Verifica se tem goblin na posição do input e deste modo retorna 1
        para depois chamar func de combate */
        if(mapa[new_y][new_x] == 'G') r = 0;
        else if(mapa[new_y][new_x] == '&') r = 0;
    }
    return r;
}

void combate(Player *j, Mobs *goblins, Boss *b, int n, int new_xy[]){
    for(int i = 0; i < n; i++){
        if(new_xy[0] == goblins[i].x && new_xy[1] == goblins[i].y){
            j->hp -= (2 - j->def);
            goblins[i].hp -= j->atk;
            if(goblins[i].hp <= 0) mapa[goblins[i].y][goblins[i].x] = '.';//goblin morre
            i = n;//acaba ciclo for
        }
    }
    if(new_xy[0] == b->x && new_xy[1] == b->y){
        j->hp -= (3 - j->def);
        b->hp -= j->atk;
        if(b->hp <= 0) mapa[b->y][b->x] = '.';//boss morre
    }

}
