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
}avl ;



int InsereArvoreNB(arvore **raiz, entrada *e, int offs);
void LiberaArvore(arvore **raiz);
int InsereAVL(avl **raiz, entrada *e);
void LiberaAVL(avl **raiz);




#endif
