#include "../headers/Arvores.h"
#include "../headers/DynamicArray.h"
#include <stdlib.h>
#include <string.h>

//Inserção na ABB nao balanceada
//Retorno -1 caso falta de memória, -2 caso arvore nula
int InsereArvoreNB(arvore **raiz, entrada *e, int offs) {
    if(raiz == NULL) return -2;

    if(*raiz == NULL) { //primeira inserção, coloca na raíz
        arvore *new = malloc(sizeof(arvore));
        if(new == NULL) return -1;
        new->dir = NULL;
        new->esq = NULL;
        new->ent = *e;
        *raiz = new;
        return 0;
    }

    if(strcmp(e->palavra, (*raiz)->ent.palavra) < 0) {
        if((*raiz)->esq == NULL) {
            arvore *new = malloc(sizeof(arvore));
            if(new == NULL) return -1;
            new->dir = NULL;
            new->esq = NULL;
            new->ent = *e;
            (*raiz)->esq = new;
            return 0;
        }
        return InsereArvoreNB(&(*raiz)->esq, e, offs);
    }

    if(strcmp(e->palavra, (*raiz)->ent.palavra) > 0) {
        if((*raiz)->dir == NULL) {
            arvore *new = malloc(sizeof(arvore));
            new->dir = NULL;
            new->esq = NULL;
            new->ent = *e;
            (*raiz)->dir = new;
            return 0;
        }
        return InsereArvoreNB(&(*raiz)->dir, e, offs);
    }

    //se chegou aqui quer dizer que a entrada ja esta na arvore
    LiberaDAInt(&e->offsets);
    InsereDAInt(offs, &(*raiz)->ent.offsets);
    (*raiz)->ent.frequencia++;
    return 0;
}

//Libera todos os nós da arvore por meio de um percurso pós-fixado
void LiberaArvore(arvore **raiz) {
    if(*raiz == NULL) return;
    LiberaArvore(&(*raiz)->esq);
    LiberaArvore(&(*raiz)->dir);
    LiberaDAInt(&(*raiz)->ent.offsets);
    free(*raiz);
}
