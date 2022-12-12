//
//  main.c
//  Compiler
//
//  Created by Anna Danot Sanchez on 21/10/22.
//

#include <stdio.h>
#include <stdlib.h>


#include "minimax.h"
#include "main.h"

// ------------------------------------ INTERFACE -----------------------------------------

void red(void){
    printf("\033[1;31m");
}

void blue(void){
    printf("\033[1;34m");
}

void reset(void){
    printf("\033[0m");
}

void clean(void){
    printf("\e[1;1H\e[2J");
}

// ----------------------------------- FUNCIONS ----------------------------------------

void imprimirTauler(char p[BOARD_DIM][BOARD_DIM]){
    printf("\n\n ");
    for(int k=0; k<BOARD_DIM; k++) printf("_____");
    printf("\n");
    for(int i=0; i<BOARD_DIM; i++){
        for(int j=0; j<BOARD_DIM; j++){
            if(p[i][j]==0){printf(" |   ");}
            else {
                printf(" | ");
                if(p[i][j]==1){blue();}
                if(p[i][j]==2){red();}
                printf("o ");
                reset();
            }
        }
        printf(" |\n ");
        for(int k=0; k<BOARD_DIM; k++) printf("_____");
        printf("\n");
    }
    for(int m=0; m<BOARD_DIM; m++)printf(" %*i",4,m+1);
    printf("\n");
}

void aplicarJugada(int jug, int col, char tauler[BOARD_DIM][BOARD_DIM]){
    for (int i=BOARD_DIM-1;i>=0;i--){
        if(tauler[i][col]==0){
            tauler[i][col] = (char)jug;
            return;
        }
    }
}

int tornJugador(char tauler[BOARD_DIM][BOARD_DIM]){
    int jug=1;
    printf("Quin es el moviment del Jugador %i? ",jug);
    int col;
    scanf("%i",&col);
    
    // Error tipus 2: ESC return 2;
       if (col==0){
           clean();
           printf("\nSortint del joc...\n");
           return 2;
       }
    // Error tipus 3: Out of range
        while(col>BOARD_DIM){
            printf("Ha d'escollir una columna dins el tauler! Torna a itentar-ho:\n");
            printf("Quin es el moviment del Jugador %i? ",jug);
            scanf("%i",&col);
        }
    // Error tipus 1: llocOcupat return 1;
        while(tauler[0][col-1]!=0){
            printf("La columna esta plena! Torna a internar-ho:\n");
            printf("Quin es el moviment del Jugador %i? ",jug);
            scanf("%i",&col);
        }

    col=col-1; // -1 perque la columna 0(logica) es la 1 pel jugador
    
    // Torn normal:
    clean();
    aplicarJugada(jug,col,tauler);
    imprimirTauler(tauler);
    return 0;
}

int tornOrdinador(Node* arrel){
    int jug=2;
    crearArbre(arrel, 0);
    int ind_fill=returnMiniMax(arrel,miniMax(arrel,0));
    int col=calculaColumna(arrel->tauler, ind_fill);
    
    printf("L'AI juga a la columna %i",col+1);
    // Torn normal:
    clean();
    aplicarJugada(jug,col,arrel->tauler);
    imprimirTauler(arrel->tauler);
    arrel->n_fills = arrel->fills[ind_fill]->n_fills;
    freeArbre(arrel, DIFF);
    return 0;
}

int checkWin(char tauler[BOARD_DIM][BOARD_DIM],int jug){
    // checkHoritzintal
    for (int j=0;j<BOARD_DIM-3;j++){
        for(int i=0;i<BOARD_DIM;i++){
            if(tauler[i][j]==jug && tauler[i][j+1]==jug && tauler[i][j+2]==jug && tauler[i][j+3]==jug){
                return 1;
            }
        }
    }
    
    // checkVertical
    for (int i = 0; i<BOARD_DIM-3 ; i++ ){
        for (int j = 0; j<BOARD_DIM; j++){
            if (tauler[i][j]==jug && tauler[i+1][j]==jug && tauler[i+2][j]==jug && tauler[i+3][j]==jug){
                return 1;
            }
        }
    }
    
    // checkDiagonal
    // ascendingDiagonalCheck
    for (int i=3; i<BOARD_DIM; i++){
        for (int j=0; j<BOARD_DIM-3; j++){
            if (tauler[i][j]==jug && tauler[i-1][j+1]==jug && tauler[i-2][j+2]==jug && tauler[i-3][j+3]==jug){
                return 1;
            }
        }
    }
    // descendingDiagonalCheck
    for (int i=3; i<BOARD_DIM; i++){
        for (int j=3; j<BOARD_DIM; j++){
            if (tauler[i][j]==jug && tauler[i-1][j-1]==jug && tauler[i-2][j-2]==jug && tauler[i-3][j-3]==jug){
                return 1;
            }
        }
    }
    return 0;
}

int taulerPle(int n_jugades){
    if(n_jugades==BOARD_DIM*BOARD_DIM)
        return 1;
    else
        return 0;
}

void connect_4(Node* arrel,char tauler[BOARD_DIM][BOARD_DIM]){
    int currentTorn=0;
    int currentPlayer;
    
    while(checkWin(tauler,1)==0 && checkWin(tauler,2)==0 && taulerPle(currentTorn)==0){
        currentTorn++;
        currentPlayer = currentTorn % 2;
        
        if(currentPlayer == 0){ //Torn de l'Ordinador
            int e =tornOrdinador(arrel);
            if(e==2){break;}
        }
        else{
            int e=tornJugador(tauler); //Torn del Jugador
            if(e==2){break;}
        }
    }
    
    // -------------------------- PRINTS ---------------------------------------
    
    if(checkWin(tauler,1)==1){
        printf("\n\nFelicitats, has guanyat!\n\n\n");
    }
    if(checkWin(tauler,2)==1){
        printf("\n\n Has perdut!\n\n\n");
    }
    else if(taulerPle(currentTorn)){
        printf("\n\nEl tauler esta ple!\n\n\n");
    }
    
}

// ------------------------------------- MAIN ------------------------------------------
int main(){
    clean();
    printf("\v\v\t\tConnect4 inicialitzat.\n\nEl Jugador 1 sera de color "); // centrar i posar mes enters
    blue();
    printf("blau");
    reset();
    printf(" i el Jugador 2 de color ");
    red();
    printf("vermell.");
    reset();
    printf("\nSi voleu sortir del joc en qualsevol moment, premeu 0 al vostre torn.\n\n");
    printf("\n\nPremeu enter per començar el joc. Bona sort!\n");
    getchar();
    clean();
    
    // Setting random seed:
    srand((unsigned int)time(NULL));
    
    Node* arrel=crearArrel();
    imprimirTauler(arrel->tauler);
    
    connect_4(arrel,arrel->tauler);
    
    free(arrel);
    free(arrel->fills);
    return 0;
}

