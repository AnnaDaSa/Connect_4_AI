//
//  minimax.c
//  
//
//  Created by Anna Danot Sanchez on 21/10/22.
//
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


#include "main.h"

int f_euristica(char tauler[BOARD_F][BOARD_C],int jug,int col){ // Recordem que l'Ordinador és el jugador 2!
    // Funció heurística la qual valora un tauler amb una estratègia donada.
    int sum=0;
    
    for(int i=0;i<BOARD_F;i++){
        for(int j=0;j<BOARD_C;j++){
            sum+=pointScore(tauler,i,j,jug);
        }
    }
    
    return sum;
}

int pointScore(char tauler[BOARD_F][BOARD_C],int fila, int col,int jug){
    int sum=0;
    // Horitzontals:
    if(col+3<BOARD_C){ //[*, , , ]
        char h1[4];
        for(int j=0;j<4;j++){
            h1[j]=tauler[fila][col+j];
        }
        sum+=vectorScore(h1, jug);
    }
    
    // Verticals:
    if(fila+3<BOARD_F){ //[*, , , ]
        char v1[4];
        for(int i=0;i<4;i++){
            v1[i]=tauler[fila+i][col];
        }
        sum+=vectorScore(v1, jug);
    }
    
    // Descending diagonals:
    if(fila+3<BOARD_F && col+3<BOARD_C){ //[*, , , ]
        char dd1[4];
        for(int i=0;i<4;i++){
            dd1[i]=tauler[fila+i][col+i];
        }
        sum+=vectorScore(dd1, jug);
    }
    
    // Ascending diagonals:
    if(fila-3>=0 && col+3<BOARD_C){ //[*, , , ]
        char ad1[4];
        for(int i=0;i<4;i++){
            ad1[i]=tauler[fila-i][col+i];
        }
        sum+=vectorScore(ad1, jug);
    }
    
    return sum;
}
int vectorScore(char v[4],int jug){
    int jug_con;
    if(jug==1){jug_con=2;}
    else{jug_con=1;}
    
    int score=0;
    int G=0, B=0, E=0; // G as good, B as bad & E as empty.
    
    for(int k=0;k<4;k++){
        if(v[k]==jug){G++;}
        else if (v[k]==jug_con){B++;}
        else if (v[k]==0){E++;}
    }
    
    if(G==4){score+=50000001;}
    if(G==3 && E==1){score+=5000;}
    if(G==2 && E==2){score+=500;}
    if(B==2 && E==2){score-=501;}
    if(B==3 && E==1){score-=5001;}
    if(B==4){score-=50000000;}//si augmento aquest funciona
    
    return score;
}

void copiarTauler(char T1[BOARD_F][BOARD_C],char T2[BOARD_F][BOARD_C]){
    // Copia el tauler T2 dins T1.
    for(int i =0;i<BOARD_F;i++){
        for(int j=0;j<BOARD_C;j++){
            T1[i][j]=T2[i][j];
        }
    }
}

void zerosTauler(char p[BOARD_F][BOARD_C]){
    // Funció que omple de zeros un tauler donat.
    for (int i=0;i<BOARD_F;i++){
        for(int j=0;j<BOARD_C;j++){
            p[i][j]=0;
        }
    }
}

int calcularNumFills(char tauler[BOARD_F][BOARD_C]){
    // Ha de tenir tants fills com columnes hi hagui lliures per tirar.
    
    int columna_lliure=0;
    for(int j=0;j<BOARD_C;j++){
        if(tauler[0][j]==0){columna_lliure++;}
    }
    return columna_lliure;
}
int calculaColumna(char tauler[BOARD_F][BOARD_C],int fill_index){
    // Per cada possible tirada augmenta ind fins arribar a fill_index, aleshores
    // la columna ha de ser aquella per la que ind=fill_index.
    
    int col,ind;
    ind=-1;
    
    for (int j=0;j<BOARD_C;j++){
        if (tauler[0][j]==0){ind++;}
        if (ind==fill_index){
            col=j;
            return col;//vull que surti del for perque ja he trobat la columna
        }
    }
    return 0;
    
}

// Les tres funcions de a continuació creen un arbre a partir d'un Node i valoren els nodes fulla
// segons la funció heurística anterior.

// -------------------------------------- CREAR ARBRE ----------------------------------------------

Node *crearNode(Node *pare,int fill_index,int nivell){
    Node *p=malloc(sizeof(Node));
    
    copiarTauler(p->tauler,pare->tauler);
    
    int jug;
    if (nivell % 2 ==0){jug=1;}
    else{jug=2;}
    
    int col = calculaColumna(p->tauler,fill_index);
    aplicarJugada(jug,col,p->tauler);
    
    if (nivell<DIFF) {
    p->n_fills=calcularNumFills(p->tauler);
    p->fills=malloc(p->n_fills * sizeof(Node *));
    }
    
    else {  //Node fulla
    
    p->n_fills=0;
    p->fills=NULL;
    p->valor = f_euristica(p->tauler,jug,col);
    /*
    imprimirTauler(p->tauler);
    printf("\nJug %d col %d score %f",jug,col+1,p->valor);
    */
    }
    return p;
}

void crear1Nivell(Node *pare,int nivell) {
    //printf("Creo un nivell més: %d\n",nivell);
    for(int i=0;i<pare->n_fills;i++) {
    pare->fills[i]=crearNode(pare,i,nivell);
    }
}

void crearArbre(Node *arrel, int nivell) {
    if(nivell<DIFF){
        nivell++;
        crear1Nivell(arrel,nivell);
        for(int i=0;i<arrel->n_fills;i++) {
            crearArbre(arrel->fills[i],nivell);
        }
    }
}

// --------------------------------------------------------------------------------------------------

void freeArbre(Node *arrel, int dim){
    // Aquesta funció esborra tot l'arbre creat a partir d'una arrel pero, no esborra aquesta!
    
    if(arrel->n_fills!=0){
        for (int i=0;i<arrel->n_fills;i++){
            freeArbre(arrel->fills[i],dim-1);
        }
        if(dim!=DIFF){
            free(arrel->fills);
        }
    }
    if(dim!=DIFF){
        free(arrel);
    }
}

Node *crearArrel(void){
    // Aquesta funció nomes la crido una vegada, per crear la primera arrel, ja que a partir d'alla no li faig
    // free mai i simplement la vaig modificant.
    
    Node *arrel=malloc(sizeof(Node));
    arrel->n_fills=BOARD_C;
    arrel->fills=malloc(arrel->n_fills * sizeof(Node *));
    zerosTauler(arrel->tauler);
    return arrel;
}

int returnMiniMax(Node* arrel, int valor){ // on valor=miniMax(arrel,0)
    
    // La funció minimax retorna el valor del fill que l'Ordinador ha de jugar,
    // aquesta funció diu quin fill és el que té aquest valor.
    
    for( int i=0 ; i<arrel->n_fills ; i++ ){
        if( arrel->fills[i]->valor == valor ){return i;}
    }
    return 0;
}

int miniMax( Node* arrel,int nivell){
    // Algoritme MiniMax, la funció retorna el valor del fill que guanya segons l'algoritme.
    
    if(arrel->n_fills==0){
        return arrel->valor;
    }//node fulla

    int valor;

    if (nivell%2 ==0){
        valor = INT_MIN;
        for(int i=0;i<arrel->n_fills;i++){
            valor= max(valor,miniMax(arrel->fills[i],nivell+1));
            arrel->valor=valor;
        }
        return valor;
    }//jugada a maximitzar

    else{
        valor = INT_MAX;
        for(int i=0;i<arrel->n_fills;i++){
            valor= min(valor,miniMax(arrel->fills[i],nivell+1));
            arrel->valor=valor;
        }
        return valor;
    }//jugada a minimitzar
 }


