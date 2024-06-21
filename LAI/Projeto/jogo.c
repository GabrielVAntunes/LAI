#include"jogo.h"

char mapa[23][79];
int linhas = 24, colunas = 80;

//Atualiza health bar
void atualiza_vida(Player *j){
    int x;

    mvaddch((linhas - 1), 0, 'H' | COLOR_PAIR(MENU));//Linha verde que diz HP
    mvaddch((linhas - 1), 1, 'P' | COLOR_PAIR(MENU));
    for(x = 2; x < j->hp * 2 + 2; x += 2){//Pinta linha hp, (dois espaços por hp)
        mvaddch((linhas - 1), x, 'v' | COLOR_PAIR(HP));
        mvaddch((linhas - 1), (x + 1), 'v' | COLOR_PAIR(HP));
    }
    while(x < 22){
        mvaddch((linhas - 1), x, ' ' | COLOR_PAIR(APAGADO));//Pinta vida perdida
        x++;
    }
    for(x = 22; x < 26; x++){ //Separa hp e atk
        mvaddch((linhas - 1), x, ' ' | COLOR_PAIR(MENU));
    }
    //Pinta ATK
    mvaddch((linhas - 1), x, 'A' | COLOR_PAIR(MENU));
    mvaddch((linhas - 1), (++x), 'T' | COLOR_PAIR(MENU));
    mvaddch((linhas - 1), (++x), 'K' | COLOR_PAIR(MENU));
    mvaddch((linhas - 1), (++x), ':' | COLOR_PAIR(MENU));
    mvaddch((linhas - 1), (++x), (j->atk + '0') | COLOR_PAIR(MENU));

    for(x += 1; x < 34; x++){ //Separa atk e def
        mvaddch((linhas - 1), x, ' ' | COLOR_PAIR(MENU));
    }
    //Pinta DEF
    mvaddch((linhas - 1), x, 'D' | COLOR_PAIR(MENU));
    mvaddch((linhas - 1), (++x), 'E' | COLOR_PAIR(MENU));
    mvaddch((linhas - 1), (++x), 'F' | COLOR_PAIR(MENU));
    mvaddch((linhas - 1), (++x), ':' | COLOR_PAIR(MENU));
    mvaddch((linhas - 1), (++x), (j->def + '0') | COLOR_PAIR(MENU));

    for(x += 1; x < colunas; x++){ //Pinta resto da linha Verde
        mvaddch((linhas - 1), x, ' ' | COLOR_PAIR(MENU));
    }
}

int main(){
    int input, new_xy[2], boss_anda = 0;
    Player *jogador = malloc(sizeof(Player));
    Mobs *goblins = malloc(8 * sizeof(Mobs));
    Boss *boss = malloc(sizeof(Boss));

    initscr(); //Inicia jogo
    noecho(); //Previne que o programa escreva input no ecra
    curs_set(0); //Apaga underscore que pisca

    start_color(); //Ativa uso de cores 
    init_pair(ILUMINADO, COLOR_YELLOW, COLOR_YELLOW); // associa cores a APAGADO (cor da frente, cor de fundo)
    init_pair(APAGADO, COLOR_BLACK, COLOR_BLACK); //associa cores a ILUMINADO
    init_pair(PAREDE, COLOR_WHITE, COLOR_WHITE); //associa cores a PAREDE
    init_pair(JOGADOR, COLOR_BLACK, COLOR_YELLOW); //associa cores a JOGADOR
    init_pair(HP, COLOR_RED, COLOR_RED); //associa cores a HP
    init_pair(MENU, COLOR_WHITE, COLOR_GREEN); //associa cores a MENU
    init_pair(GOBLIN, COLOR_BLACK, COLOR_GREEN); //associa cores a GOBLIN
    init_pair(VIDA, COLOR_WHITE, COLOR_MAGENTA); //associa cores a poçoes
    init_pair(ITEMS, COLOR_WHITE, COLOR_BLUE); //associa cores a ITEMS
    init_pair(BOSS, COLOR_BLACK, COLOR_RED); //associa cores a BOSS

    srand(time(NULL));//Gera seed para a função rand, metodo comum de fazer um "randomizador"
    fazMapa(mapa, linhas, colunas);//Constroi o mapa
    createPlayer(jogador, linhas, colunas);//Inicializa jogador
    mvaddch(jogador->y, jogador->x, jogador->sprite | COLOR_PAIR(JOGADOR)); //Imprime jogador na sua pos inicial
    createMob(goblins, 8, linhas, colunas);
    createBoss(boss, linhas, colunas);
    createItems();
    criaFOV(jogador);
    atualiza_vida(jogador);

    while(jogador->hp > 0 && boss->hp > 0 && (input = getch()) != 'q'){
        apagaFOV(jogador);
        
        if(!movimento(jogador, input, new_xy)) //Trata da ação do jogador consoante o input
            combate(jogador, goblins, boss, 8, new_xy);
        mvaddch(jogador->y, jogador->x, jogador->sprite | COLOR_PAIR(JOGADOR)); //Atualiza pos (func pede y primeiro)
        
        movimento_mobs(goblins, jogador, 8);
        
        if(boss_anda == 1){
            movimento_boss(boss, jogador);
            boss_anda = 0;
        }else boss_anda = 1;
        
        criaFOV(jogador);
        atualiza_vida(jogador);
    }

    clear();
    mvprintw(6, 7, "-------------------------------------------------------------------");
    if(boss->hp <= 0) mvprintw(11, 11, "Parabéns guerreiro destemido, venceste a gangue de goblins!");
    else if(jogador->hp <= 0) mvprintw(11, 21, "Foste comido pela gangue de goblins -_-'");
    mvprintw(16, 7, "-------------------------------------------------------------------");

    getch();
    endwin(); //Fecha jogo
    free(jogador); //Liberta memoria do jogador quando fecha o jogo
    

    return 0;
}