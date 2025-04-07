#ifndef PROJETOFINALAED2_BUSCA_H
#define PROJETOFINALAED2_BUSCA_H
#include "../headers/DynamicArray.h"
#include "../headers/Arvores.h"

void ImprimeInfos(entrada *e, char *nomeArq);
entrada* BuscaABB(arvore *raiz, char *palavra);
dinArrayEntrada* BuscaAVL(avl *raiz, unsigned int freq);
void ImprimePalavras(dinArrayEntrada *de);

#endif
