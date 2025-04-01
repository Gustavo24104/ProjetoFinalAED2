#ifndef PROJETOFINALAED2_BUSCA_H
#define PROJETOFINALAED2_BUSCA_H
#include "../headers/DynamicArray.h"
#include "../headers/Arvores.h"

void ImprimeInfos(entrada *e, char *nomeArq);
entrada* BuscaABB(arvore *raiz, char *palavra);
void Infix(arvore *r, char *arq);

#endif
