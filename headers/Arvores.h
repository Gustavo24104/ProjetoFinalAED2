#ifndef PROJETOFINALAED2_ARVORES_H
#define PROJETOFINALAED2_ARVORES_H
#include "../headers/DynamicArray.h"

typedef struct arvore {
    entrada ent;
    struct arvore *dir, *esq;
} arvore;

typedef struct avl {
    dinArrayEntrada entArr;
    struct avl *dir, *esq;
} avlFrequencia;



int InsereArvoreNB(arvore **raiz, entrada *e, int offs);
void LiberaArvore(arvore **raiz);
int InsereAVLFrequencia(avlFrequencia **raiz, entrada *e);
int InsereAVLPalavra(arvore **raiz, entrada *e, int offs);
void LiberaAVL(avlFrequencia **raiz);




#endif
