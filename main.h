//
//  main.h
//  principal
//
//  Created by Anna Danot Sanchez on 21/10/22.
//
#include<time.h>

#ifndef main_h
#define main_h

void red(void);
void blue(void);
void reset(void);
void clean(void);

void imprimirTauler(char p[BOARD_DIM][BOARD_DIM]);
void aplicarJugada(int jug, int col, char tauler[BOARD_DIM][BOARD_DIM]);
int tornJugador(char tauler[BOARD_DIM][BOARD_DIM]);
int tornOrdinador(Node* arrel);
int checkWin(char tauler[BOARD_DIM][BOARD_DIM],int jug);
int taulerPle(int n_jugades);
void connect_4(Node* arrel,char tauler[BOARD_DIM][BOARD_DIM]);

int main();

#endif /* main_h */
