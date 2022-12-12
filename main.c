//
//  main.c
//  
//
//  Created by Anna Danot Sanchez on 21/10/22.
//

#include <stdio.h>
#include <stdlib.h>

#include "main.h"

// ------------------------------------ INTERFACE -----------------------------------------

void red(void){
    printf("\033[1;31m");
}

void blue(void){
    printf("\033[1;34m");
}

void green(void){
    printf("\033[0;32m");
}

void yellow(void){
    printf("\033[0;33m");
}

void reset(void){ //Esborra qualsevol color anterior
    printf("\033[0m");
}

void clean(void){ //Neteja la terminal
    printf("\e[1;1H\e[2J");
}

// ----------------------------------- FUNCIONS ----------------------------------------

void imprimirTauler(char p[BOARD_F][BOARD_C]){
    clean();
    printf("\t\t\t");
    for(int j=0;j<BOARD_C;j++){
        printf("%d \t",j+1);
    }
    printf("\n\n");
    for(int i=0; i<BOARD_F; i++){
        for(int k=0;k<2;k++){
            for(int j=0; j<BOARD_C; j++){
                if(j==0){printf("\t\t\t");}
                if(p[i][j]==0){printf("··\t");}
                else if(p[i][j]==1){blue();printf("██\t");reset();}
                else{red();printf("██\t");reset();}
            }
            printf("\n");
        }
        printf("\n");
    }
}

void imprimirTauler_torn(char p[BOARD_F][BOARD_C],int col){
    //Imprimeix el tauler a cada torn assenyalant l'ultima tirada
    
    //Trobo la fila on ha tirat:
    int fila=0;
    for(int i=BOARD_F-1;i>=0;i--){
        if(p[i][col]!=0){
            fila=i;
        }
    }
    
    clean();
    printf("\t\t\t");
    for(int j=0;j<BOARD_C;j++){
        printf("%d \t",j+1);
    }
    printf("\n\n");
    for(int i=0; i<BOARD_F; i++){
        for(int k=0;k<2;k++){
            for(int j=0; j<BOARD_C; j++){
                if(j==0){printf("\t\t\t");}
                if(i==fila && j==col && p[i][j]==1){yellow();printf("█");blue();printf("█\t");reset();}
                else if(i==fila && j==col && p[i][j]==2){yellow();printf("█");red();printf("█\t");reset();}
                else if(p[i][j]==0){printf("··\t");}
                else if(p[i][j]==1){blue();printf("██\t");reset();}
                else{red();printf("██\t");reset();}
            }
            printf("\n");
        }
        printf("\n");
    }
}

void imprimirTauler_win(char tauler[BOARD_F][BOARD_C], int jug){
    //Imprimeix el tauler quan ha guanyat algu i assenyala les 4 fitxes
    
    //Trobem els 4 en ratlla
    int files[4];
    int cols[4];
    // checkHoritzintal
    for (int j=0;j<BOARD_C-3;j++){
        for(int i=0;i<BOARD_F;i++){
            if(tauler[i][j]==jug && tauler[i][j+1]==jug && tauler[i][j+2]==jug && tauler[i][j+3]==jug){
                files[0]=i;files[1]=i;files[2]=i;files[3]=i;
                cols[0]=j;cols[1]=j+1;cols[2]=j+2;cols[3]=j+3;
            }
        }
    }
    
    // checkVertical
    for (int i = 0; i<BOARD_F-3 ; i++ ){
        for (int j = 0; j<BOARD_C; j++){
            if (tauler[i][j]==jug && tauler[i+1][j]==jug && tauler[i+2][j]==jug && tauler[i+3][j]==jug){
                files[0]=i;files[1]=i+1;files[2]=i+2;files[3]=i+3;
                cols[0]=j;cols[1]=j;cols[2]=j;cols[3]=j;
            }
        }
    }
    
    // checkDiagonal
    // ascendingDiagonalCheck
    for (int i=3; i<BOARD_F; i++){
        for (int j=0; j<BOARD_C-3; j++){
            if (tauler[i][j]==jug && tauler[i-1][j+1]==jug && tauler[i-2][j+2]==jug && tauler[i-3][j+3]==jug){
                files[0]=i;files[1]=i-1;files[2]=i-2;files[3]=i-3;
                cols[0]=j;cols[1]=j+1;cols[2]=j+2;cols[3]=j+3;
            }
        }
    }
    // descendingDiagonalCheck
    for (int i=3; i<BOARD_F; i++){
        for (int j=3; j<BOARD_C; j++){
            if (tauler[i][j]==jug && tauler[i-1][j-1]==jug && tauler[i-2][j-2]==jug && tauler[i-3][j-3]==jug){
                files[0]=i;files[1]=i-1;files[2]=i-2;files[3]=i-3;
                cols[0]=j;cols[1]=j-1;cols[2]=j-2;cols[3]=j-3;
            }
        }
    }
    int c=0;
    clean();
    printf("\t\t\t");
    for(int j=0;j<BOARD_C;j++){
        printf("%d \t",j+1);
    }
    printf("\n\n");
    for(int i=0; i<BOARD_F; i++){
        for(int k=0;k<2;k++){
            for(int j=0; j<BOARD_C; j++){
                if(j==0){printf("\t\t\t");}
                for(int k=0;k<4;k++){
                    if(files[k]==i && cols[k]==j){
                        if(jug==1){yellow();printf("█");blue();printf("█\t");reset();}
                        else{yellow();printf("█");red();printf("█\t");reset();}
                        c=1;
                    }
                }
                if(c!=1){
                    if(tauler[i][j]==0){printf("··\t");}
                    else if(tauler[i][j]==1){blue();printf("██\t");reset();}
                    else{red();printf("██\t");reset();}
                }
                c=0;
            }
            printf("\n");
        }
        printf("\n");
    }
}

void aplicarJugada(int jug, int col, char tauler[BOARD_F][BOARD_C]){
    for (int i=BOARD_F-1;i>=0;i--){
        if(tauler[i][col]==0){
            tauler[i][col] = (char)jug;
            return;
        }
    }
}

int tornJugador(char tauler[BOARD_F][BOARD_C]){
    int jug=1;
    printf("Quin es el moviment del Jugador %i? ",jug);
    int col;
    printf("> ");
    scanf("%i",&col);
    
    // Error tipus 2: ESC return 2;
       if (col==0){
           clean();
           printf("\nSortint del joc...\n");
           return 2;
       }
    // Error tipus 3: Out of range
        while(col>BOARD_C){
            printf("Ha d'escollir una columna dins el tauler! Torna a itentar-ho:\n");
            printf("Quin es el moviment del Jugador %i? ",jug);
            printf("> ");
            scanf("%i",&col);
        }
        while(col<0){
            printf("Ha d'escollir una columna dins el tauler! Torna a itentar-ho:\n");
            printf("Quin es el moviment del Jugador %i? ",jug);
            printf("> ");
            scanf("%i",&col);
        }
    // Error tipus 1: llocOcupat return 1;
        while(tauler[0][col-1]!=0){
            printf("La columna esta plena! Torna a internar-ho:\n");
            printf("Quin es el moviment del Jugador %i? ",jug);
            printf("> ");
            scanf("%i",&col);
        }

    col=col-1; // -1 perque la columna 0(logica) es la 1 pel jugador
    
    // Torn normal:
    clean();
    aplicarJugada(jug,col,tauler);
    imprimirTauler_torn(tauler,col);
    return 0;
}

int tornOrdinador(Node* arrel){
    int jug=2;
    crearArbre(arrel, 0);
    int ind_fill=returnMiniMax(arrel,miniMax(arrel,0));
    int col=calculaColumna(arrel->tauler, ind_fill);
    
    // Torn normal:
    clean();
    aplicarJugada(jug,col,arrel->tauler);
    imprimirTauler_torn(arrel->tauler,col);
    arrel->n_fills = arrel->fills[ind_fill]->n_fills;
    freeArbre(arrel, DIFF);
    return 0;
}

int checkWin(char tauler[BOARD_F][BOARD_C],int jug){
    // checkHoritzintal
    for (int j=0;j<BOARD_C-3;j++){
        for(int i=0;i<BOARD_F;i++){
            if(tauler[i][j]==jug && tauler[i][j+1]==jug && tauler[i][j+2]==jug && tauler[i][j+3]==jug){
                return 1;
            }
        }
    }
    
    // checkVertical
    for (int i = 0; i<BOARD_F-3 ; i++ ){
        for (int j = 0; j<BOARD_C; j++){
            if (tauler[i][j]==jug && tauler[i+1][j]==jug && tauler[i+2][j]==jug && tauler[i+3][j]==jug){
                return 1;
            }
        }
    }
    
    // checkDiagonal
    // ascendingDiagonalCheck
    for (int i=3; i<BOARD_F; i++){
        for (int j=0; j<BOARD_C-3; j++){
            if (tauler[i][j]==jug && tauler[i-1][j+1]==jug && tauler[i-2][j+2]==jug && tauler[i-3][j+3]==jug){
                return 1;
            }
        }
    }
    // descendingDiagonalCheck
    for (int i=3; i<BOARD_F; i++){
        for (int j=3; j<BOARD_C; j++){
            if (tauler[i][j]==jug && tauler[i-1][j-1]==jug && tauler[i-2][j-2]==jug && tauler[i-3][j-3]==jug){
                return 1;
            }
        }
    }
    return 0;
}

int taulerPle(int n_jugades){
    if(n_jugades==BOARD_F*BOARD_C)
        return 1;
    else
        return 0;
}

void connect_4(Node* arrel,char tauler[BOARD_F][BOARD_C],int begin){
    int currentTorn=0;
    int currentPlayer;
    
    while(checkWin(tauler,1)==0 && checkWin(tauler,2)==0 && taulerPle(currentTorn)==0){
        currentTorn++;
        if(begin==1){currentPlayer = currentTorn % 2;}
        else{currentPlayer = currentTorn % 2-1;}
        
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
        imprimirTauler_win(tauler,1);
        printf("\n\nFelicitats, has guanyat!\n\n\n");
    }
    if(checkWin(tauler,2)==1){
        imprimirTauler_win(tauler,2);
        printf("\n\nHas perdut... Torna-ho a intentar!\n\n\n");
    }
    else if(taulerPle(currentTorn)){
        printf("\n\nEmpat!\n\n\n");
    }

}

// ------------------------------------- MAIN ------------------------------------------
int main(void){
    int again=1;
    while(again==1){
        clean();
        printf("\v\v\t\tConnect4 inicialitzat.\n\nEl Jugador 1 sera de color ");blue();printf("blau");reset();
        printf(" i el Jugador 2 de color ");red();printf("vermell.");reset();
        printf("\nSi voleu sortir del joc en qualsevol moment, premeu 0 al vostre torn.\n\n");
        /*
        printf("Escollim primer el tamany del tauler:\n");
        green();printf("Nombre de files:\t");reset();
        int files=0;
        while(files<=0){scanf("%d" ,&files);}
        BOARD_F=files;
        printf("\n");
        green();printf("Nombre de columnes:\t");reset();
        int cols=0;
        while(cols<=0){scanf("%d" ,&cols);}
        BOARD_C=cols;
        */
        DIFF=0;
        printf("Quina dificultat vols que tingui el joc?\n");
        green();printf("1)\t");reset();
        printf("BAIXA");
        printf("  ...  ");
        green();printf("5)\t");reset();
        printf("ALTA\n");
        while(DIFF<1 || DIFF>5){printf("> ");scanf("%i",&DIFF);}
        
        int begin=0;
        printf("Vols començar tu o la maquina?\n");
        green();printf("1)\t");reset();
        printf("JO\n");
        green();printf("2)\t");reset();
        printf("LA MAQUINA\n");
        while(begin!=1 && begin!=2){printf("> ");scanf("%i",&begin);}
        
        printf("\n\nPremeu enter per començar el joc. Bona sort!\n");
        getchar();
        clean();
        
        Node* arrel=crearArrel();
        imprimirTauler(arrel->tauler);
        
        connect_4(arrel,arrel->tauler,begin);
        
        free(arrel);
        free(arrel->fills);
        printf("Voleu tornar a jugar?\n");
        green();printf("1)\t");reset();
        printf("SI\n");
        green();printf("2)\t");reset();
        printf("NO\n");
        again=0;
        while(again!=1 && again!=2){printf("> ");scanf("%i",&again);}
    }
    return 0;
}

