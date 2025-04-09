#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
#include "../headers/Arvores.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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
        InsereDAInt(offs, &new->ent.offsets);

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
//            InsereDAInt(offs, &new->ent.offsets);
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
//            InsereDAInt(offs, &new->ent.offsets);
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

//Retirado do livro do André Backes "Algoritmos e Estruturas de Dados em Linguagem C"
void RotacaoDireitaFrequencia(avlFrequencia **pivo) {
    avlFrequencia *temp;
    temp = (*pivo)->esq;
    (*pivo)->esq = temp->dir;
    temp->dir = *pivo;
    (*pivo) = temp;
}

//Rotaciona AVL de frequencias
int GetAlturaFrequencia(avlFrequencia *raiz) {
    if(raiz == NULL) {
        return -1;
    }
    int d = GetAlturaFrequencia(raiz->dir);
    int e = GetAlturaFrequencia(raiz->esq);
    if(d >= e) return d + 1;
    return e + 1;
}



//Retirado do livro do André Backes "Algoritmos e Estruturas de Dados em Linguagem C"
void RotacaoEsquerdaFrequencia(avlFrequencia **pivo) {
    avlFrequencia *temp = (*pivo)->dir;
    (*pivo)->dir = temp->esq;
    temp->esq = *pivo;
    (*pivo) = temp;
}

int GetAlturaAVL(arvore *raiz) {
    if(raiz == NULL) {
        return -1;
    }
    int d = GetAlturaAVL(raiz->dir);
    int e = GetAlturaAVL(raiz->esq);
    if(d >= e) return d + 1;
    return e + 1;
}



void RotacaoEsquerdaAVL(arvore **pivo) {
    arvore *temp = (*pivo)->dir;
    (*pivo)->dir = temp->esq;
    temp->esq = *pivo;
    (*pivo) = temp;
}

//Retirado do livro do André Backes "Algoritmos e Estruturas de Dados em Linguagem C"
void RotacaoDireitaAVL(arvore **pivo) {
    arvore *temp;
    temp = (*pivo)->esq;
    (*pivo)->esq = temp->dir;
    temp->dir = *pivo;
    (*pivo) = temp;
}





int InsereAVLPalavra(arvore **raiz, entrada *e, int offs) {
    if(raiz == NULL) return -2;

    if(*raiz == NULL) { //primeira inserção, coloca na raíz
        arvore *new = malloc(sizeof(arvore));
        if(new == NULL) return -1;
        new->dir = NULL;
        new->esq = NULL;
        new->ent = *e;
        InsereDAInt(offs, &new->ent.offsets);

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
//            InsereDAInt(offs, &new->ent.offsets);
            (*raiz)->esq = new;
            return 0;
        }
        return InsereAVLPalavra(&(*raiz)->esq, e, offs);
    }

    if(strcmp(e->palavra, (*raiz)->ent.palavra) > 0) {
        if((*raiz)->dir == NULL) {
            arvore *new = malloc(sizeof(arvore));
            new->dir = NULL;
            new->esq = NULL;
            new->ent = *e;
//            InsereDAInt(offs, &new->ent.offsets);
            (*raiz)->dir = new;
            return 0;
        }
        return InsereAVLPalavra(&(*raiz)->dir, e, offs);
    }

    //se chegou aqui quer dizer que a entrada ja esta na arvore
    LiberaDAInt(&e->offsets);
    InsereDAInt(offs, &(*raiz)->ent.offsets);
    (*raiz)->ent.frequencia++;

    //Checa balanceamento
    int fb = GetAlturaAVL((*raiz)->esq) - (GetAlturaAVL((*raiz)->dir));
    if(fb == -2) { // Arvore maior esta na direita
        int fbDir = GetAlturaAVL((*raiz)->dir->esq) - GetAlturaAVL((*raiz)->dir->dir);
        if(fbDir < 0) { //Desbalanceamento direito-direito
            RotacaoEsquerdaAVL(raiz);
            return 0;
        }

        if(fbDir > 0) { //Desbalanceamento direito-esquerdo
            RotacaoDireitaAVL(&(*raiz)->dir);
            RotacaoEsquerdaAVL(raiz);
            return 0;
        }
    }

    if(fb == 2) { // Arvore maior na esquerda
        int fbEsq = GetAlturaAVL((*raiz)->esq->esq) - GetAlturaAVL((*raiz)->esq->dir);
        if(fbEsq > 0) { // Desbalanceamento esquerda-esquerda
            RotacaoDireitaAVL(raiz);
            return 0;
        }

        if(fbEsq < 0) { // Desbalanceamento esquerdo-direito
            RotacaoEsquerdaAVL(&(*raiz)->esq);
            RotacaoDireitaAVL(raiz);
            return 0;
        }
    }
    return 0;
}


//Insere um elemento na arvore AVL
int InsereAVLFrequencia(avlFrequencia **raiz, entrada *e) {
    if(raiz == NULL) return -2;
    if(*raiz == NULL) { //primeira inserção, coloca na raíz
        avlFrequencia *new = malloc(sizeof(avlFrequencia));
        if(new == NULL) return -1;
        new->dir = NULL;
        new->esq = NULL;
        InicializaDAEntrada(&new->entArr);
        InsereDAEntrada(e, &new->entArr);

        *raiz = new;
        return 0;
    }if(e->frequencia < (*raiz)->entArr.array[0].frequencia) {
        if((*raiz)->esq == NULL) {
            avlFrequencia *new = malloc(sizeof(avlFrequencia));
            if(new == NULL) return -1;
            new->dir = NULL;
            new->esq = NULL;
            InicializaDAEntrada(&new->entArr);
            InsereDAEntrada(e, &new->entArr);
            (*raiz)->esq = new;
            return 0;
        }
        InsereAVLFrequencia(&(*raiz)->esq, e);
    }if(e->frequencia > (*raiz)->entArr.array[0].frequencia) {
        if((*raiz)->dir == NULL) {
            avlFrequencia *new = malloc(sizeof(avlFrequencia));
            new->dir = NULL;
            new->esq = NULL;
            InicializaDAEntrada(&new->entArr);
            InsereDAEntrada(e, &new->entArr);
            (*raiz)->dir = new;
            return 0;
        }
        InsereAVLFrequencia(&(*raiz)->dir, e);
    } else {
        //se chegou aqui quer dizer que a entrada ja esta na arvore
        InsereDAEntrada(e, &(*raiz)->entArr);
        return 0;
    }

    int fb = GetAlturaFrequencia((*raiz)->esq) - (GetAlturaFrequencia((*raiz)->dir));
    if(fb == -2) { // Arvore maior esta na direita
        printf("rt\n");
        int fbDir = GetAlturaFrequencia((*raiz)->dir->esq) - GetAlturaFrequencia((*raiz)->dir->dir);
        if(fbDir < 0) { //Desbalanceamento direito-direito
            RotacaoEsquerdaFrequencia(raiz);
            return 0;
        }

        if(fbDir > 0) { //Desbalanceamento direito-esquerdo
            RotacaoDireitaFrequencia(&(*raiz)->dir);
            RotacaoEsquerdaFrequencia(raiz);
            return 0;
        }
    }

    if(fb == 2) { // Arvore maior na esquerda
        printf("rt\n");
        int fbEsq = GetAlturaFrequencia((*raiz)->esq->esq) - GetAlturaFrequencia((*raiz)->esq->dir);
        if(fbEsq > 0) { // Desbalanceamento esquerda-esquerda
            RotacaoDireitaFrequencia(raiz);
            return 0;
        }

        if(fbEsq < 0) { // Desbalanceamento esquerdo-direito
            RotacaoEsquerdaFrequencia(&(*raiz)->esq);
            RotacaoDireitaFrequencia(raiz);
            return 0;
        }
    }
    return 0;
}



//Libera todos os nós da arvore por meio de um percurso pós-fixado
void LiberaArvore(arvore **raiz) {
    if(*raiz == NULL) return;
    LiberaArvore(&(*raiz)->esq);
    LiberaArvore(&(*raiz)->dir);
    LiberaDAInt(&(*raiz)->ent.offsets);
    free(*raiz);
    *raiz = NULL;
}

//Idem acima para arvore AVL
void LiberaAVL(avlFrequencia **raiz) {
    if(*raiz == NULL) return;
    LiberaAVL(&(*raiz)->esq);
    LiberaAVL(&(*raiz)->dir);
    LiberaDAInt(&(*raiz)->entArr.array[0].offsets);
    free(*raiz);
    *raiz = NULL;
}

#pragma clang diagnostic pop