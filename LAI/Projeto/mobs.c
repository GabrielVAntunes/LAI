#include"jogo.h"

//Dá spawn aos mobs
void createMob(Mobs *goblins, int n, int linhas, int colunas){
    
    for(int i = 0; i < n; i++){
        int spawn_x = 0, spawn_y = 0;
        //Randomiza Spawn do mob
        //Randomiza até não estar numa parede
        while(mapa[spawn_y][spawn_x] != '.'){
            int a = rand();
            spawn_x = a % colunas;
            spawn_y = a % (linhas - 1);
        }
        goblins[i].x = spawn_x;
        goblins[i].y = spawn_y;
        goblins[i].hp = 2;
        mapa[spawn_y][spawn_x] = 'G';
    }
}

void movimento_mobs(Mobs *goblins, Player *j, int n){
    
    for(int i = 0; i < n; i++){
        if(goblins[i].hp > 0){
            int dist_x = goblins[i].x - j->x;
            int dist_y = goblins[i].y - j->y;
            if(sqrt((dist_x * dist_x) + (dist_y * dist_y)) < 7){
                int direçao_x, direçao_y;
                
                if(dist_x < 0) direçao_x = 1;
                else direçao_x = -1;
                
                if(dist_y < 0) direçao_y = 1;
                else direçao_y = -1;

                dist_x = abs(dist_x);
                dist_y = abs(dist_y);

                if(dist_y > dist_x){
                    if(mapa[(goblins[i].y + direçao_y)][goblins[i].x] == '.'){
                        mapa[goblins[i].y][goblins[i].x] = '.';
                        goblins[i].y += direçao_y;
                        mapa[goblins[i].y][goblins[i].x] = 'G';
                    }
                }else{
                    if(mapa[goblins[i].y][(goblins[i].x + direçao_x)] == '.'){
                        mapa[goblins[i].y][goblins[i].x] = '.';
                        goblins[i].x += direçao_x;
                        mapa[goblins[i].y][goblins[i].x] = 'G';
                    }
                }

            }else{
                
                    int a = rand();
                    a = a % 4;
                    switch(a){
                        case 0:
                            if(mapa[(goblins[i].y - 1)][goblins[i].x] == '.'){
                                mapa[goblins[i].y][goblins[i].x] = '.';
                                goblins[i].y--;
                                mapa[goblins[i].y][goblins[i].x] = 'G';
                            }
                            break;
                        case 1:
                            if(mapa[(goblins[i].y + 1)][goblins[i].x] == '.'){
                                mapa[goblins[i].y][goblins[i].x] = '.';
                                goblins[i].y++;
                                mapa[goblins[i].y][goblins[i].x] = 'G';
                            }
                            break;
                        case 2:
                            if(mapa[goblins[i].y][(goblins[i].x - 1)] == '.'){
                                mapa[goblins[i].y][goblins[i].x] = '.';
                                goblins[i].x--;
                                mapa[goblins[i].y][goblins[i].x] = 'G';
                            }
                            break;
                        case 3:
                            if(mapa[goblins[i].y][(goblins[i].x + 1)] == '.'){
                                mapa[goblins[i].y][goblins[i].x] = '.';
                                goblins[i].x++;
                                mapa[goblins[i].y][goblins[i].x] = 'G';
                            }
                            break;
                    default:
                        break;
                    }
            }
        }    
    }
}

void createBoss(Boss *b, int linhas, int colunas){
    int spawn_x = 0, spawn_y = 0;
        //Randomiza Spawn do Boss
        //Randomiza até não estar numa parede
        while(mapa[spawn_y][spawn_x] != '.'){
            int a = rand();
            spawn_x = a % colunas;
            spawn_y = a % (linhas - 1);
        }
        b->x = spawn_x;
        b->y = spawn_y;
        b->hp = 5;
        mapa[spawn_y][spawn_x] = '&';
}

void movimento_boss(Boss *b, Player *j){
    
    
    if(b->hp > 0){
        int dist_x = b->x - j->x;
        int dist_y = b->y - j->y;
        if(sqrt((dist_x * dist_x) + (dist_y * dist_y)) < 7){
            int direçao_x, direçao_y;
            
            if(dist_x < 0) direçao_x = 1;
            else direçao_x = -1;
            
            if(dist_y < 0) direçao_y = 1;
            else direçao_y = -1;

            dist_x = abs(dist_x);
            dist_y = abs(dist_y);

            if(dist_y > dist_x){
                if(mapa[(b->y + direçao_y)][b->x] == '.'){
                    mapa[b->y][b->x] = '.';
                    b->y += direçao_y;
                    mapa[b->y][b->x] = '&';
                }
            }else{
                if(mapa[b->y][(b->x + direçao_x)] == '.'){
                    mapa[b->y][b->x] = '.';
                    b->x += direçao_x;
                    mapa[b->y][b->x] = '&';
                }
            }

        }else{
            
                int a = rand();
                a = a % 4;
                switch(a){
                    case 0:
                        if(mapa[(b->y - 1)][b->x] == '.'){
                            mapa[b->y][b->x] = '.';
                            b->y--;
                            mapa[b->y][b->x] = '&';
                        }
                        break;
                    case 1:
                        if(mapa[(b->y + 1)][b->x] == '.'){
                            mapa[b->y][b->x] = '.';
                            b->y++;
                            mapa[b->y][b->x] = '&';
                        }
                        break;
                    case 2:
                        if(mapa[b->y][(b->x - 1)] == '.'){
                            mapa[b->y][b->x] = '.';
                            b->x--;
                            mapa[b->y][b->x] = '&';
                        }
                        break;
                    case 3:
                        if(mapa[b->y][(b->x + 1)] == '.'){
                            mapa[b->y][b->x] = '.';
                            b->x++;
                            mapa[b->y][b->x] = '&';
                        }
                        break;
                default:
                    break;
                }
        }
    }    
}
