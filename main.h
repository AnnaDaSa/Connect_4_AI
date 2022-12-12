//
//  main.h
//  
//
//  Created by Anna Danot Sanchez on 21/10/22.
//
#include "minimax.h"

#ifndef main_h
#define main_h


void red(void);
void blue(void);
void green(void);
void yellow(void);
void reset(void);
void clean(void);

void imprimirTauler(char p[BOARD_F][BOARD_C]);
void imprimirTauler_torn(char p[BOARD_F][BOARD_C],int col);
void imprimirTauler_win(char tauler[BOARD_F][BOARD_C], int jug);

void aplicarJugada(int jug, int col, char tauler[BOARD_F][BOARD_C]);
int tornJugador(char tauler[BOARD_F][BOARD_C]);
int tornOrdinador(Node* arrel);

int checkWin(char tauler[BOARD_F][BOARD_C],int jug);
int taulerPle(int n_jugades);
void connect_4(Node* arrel,char tauler[BOARD_F][BOARD_C],int begin);

int main(void);

#endif /* main_h */
