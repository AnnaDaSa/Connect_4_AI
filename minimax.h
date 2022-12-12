//
//  minimax.h
//
//
//  Created by Anna Danot Sanchez on 21/10/22.
//

#ifndef minimax_h
#define minimax_h

#define BOARD_F 6 //Nombre de files del tauler
#define BOARD_C 7 //Nombre de columnes del tauler


int DIFF; //La dificultat del joc (s'escull a la main)

// Defines de les funcions maxim i minim entre dos valors.

#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))

typedef struct node{
    int cols;
    char tauler[BOARD_F][BOARD_C];
    int n_fills;
    struct node* *fills;
    double valor;
} Node;

int f_euristica(char tauler[BOARD_F][BOARD_C],int jug,int col);
int pointScore(char tauler[BOARD_F][BOARD_C],int fila, int col,int jug);
int vectorScore(char v[4],int jug);


void copiarTauler(char T1[BOARD_F][BOARD_C],char T2[BOARD_F][BOARD_C]);
void zerosTauler(char p[BOARD_F][BOARD_C]);

int calcularNumFills(char tauler[BOARD_F][BOARD_C]);
int calculaColumna(char tauler[BOARD_F][BOARD_C],int fill_index);

Node *crearNode(Node *pare,int fill_index,int nivell);
void crear1Nivell(Node *pare,int nivell);
void crearArbre(Node *arrel, int nivell);

void freeArbre(Node *arrel, int dim);

Node *crearArrel(void);

int returnMiniMax(Node* arrel, int valor);
int miniMax( Node* arrel, int nivell);





#endif /* minimax_h */

