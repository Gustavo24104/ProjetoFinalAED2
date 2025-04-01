#ifndef PROJETOFINALAED2_ARVORES_H
#define PROJETOFINALAED2_ARVORES_H
#include "../headers/DynamicArray.h"

typedef struct arv {
    entrada ent;
    struct arv *dir, *esq;
} arvore;

int InsereArvoreNB(arvore **raiz, entrada *e, int offs);
void LiberaArvore(arvore **raiz);




#endif
