//
//  minimax.h
//  principal
//
//  Created by Anna Danot Sanchez on 21/10/22.
//

#ifndef minimax_h
#define minimax_h

#define DIFF 5
#define BOARD_DIM 8

// Defines de les funcions maxim i minim entre dos valors.

#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))

typedef struct node{
    char tauler[BOARD_DIM][BOARD_DIM];
    int n_fills;
    struct node* *fills;
    double valor;
} Node;

int f_euristica(char tauler[BOARD_DIM][BOARD_DIM],int jug,int col);
int vectorScore(char v[4],int jug);
int pointScore(char tauler[BOARD_DIM][BOARD_DIM],int fila, int col,int jug);

void copiarTauler(char T1[BOARD_DIM][BOARD_DIM],char T2[BOARD_DIM][BOARD_DIM]);
void zerosTauler(char p[BOARD_DIM][BOARD_DIM]);

int calcularNumFills(char tauler[BOARD_DIM][BOARD_DIM]);
int calculaColumna(char tauler[BOARD_DIM][BOARD_DIM],int fill_index);

Node *crearNode(Node *pare,int fill_index,int nivell);
void crear1Nivell(Node *pare,int nivell);
void crearArbre(Node *arrel, int nivell);
void freeArbre(Node *arrel, int dim);
Node *crearArrel(void);

int returnMiniMax(Node* arrel, int valor);
int miniMax( Node* arrel, int nivell);





#endif /* minimax_h */

