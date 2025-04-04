#include "../headers/Arvores.h"
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
void RotacaoDireita(avl **pivo) {
    avl *temp;
    temp = (*pivo)->esq;
    (*pivo)->esq = temp->dir;
    temp->dir = *pivo;
    (*pivo) = temp;
}

int GetAltura(avl *raiz) {
    if(raiz == NULL) {
        return -1;
    }
    int d = GetAltura(raiz->dir);
    int e = GetAltura(raiz->esq);
    if(d >= e) return d + 1;
    return e + 1;
}



//Retirado do livro do André Backes "Algoritmos e Estruturas de Dados em Linguagem C"
void RotacaoEsquerda(avl **pivo) {
    avl *temp = (*pivo)->dir;
    (*pivo)->dir = temp->esq;
    temp->esq = *pivo;
    (*pivo) = temp;
}


//Insere um elemento na arvore AVL
int InsereAVL(avl **raiz, entrada *e) {
    if(raiz == NULL) return -2;

    if(*raiz == NULL) { //primeira inserção, coloca na raíz
        avl *new = malloc(sizeof(avl));
        if(new == NULL) return -1;
        new->dir = NULL;
        new->esq = NULL;
        InicializaDAEntrada(&new->entArr);
        InsereDAEntrada(e, &new->entArr);

        *raiz = new;
        return 0;
    }if(e->frequencia < (*raiz)->entArr.array[0].frequencia) {
        if((*raiz)->esq == NULL) {
            avl *new = malloc(sizeof(avl));
            if(new == NULL) return -1;
            new->dir = NULL;
            new->esq = NULL;
            InicializaDAEntrada(&new->entArr);
            InsereDAEntrada(e, &new->entArr);
            (*raiz)->esq = new;
            return 0;
        }
        InsereAVL(&(*raiz)->esq, e);
    }if(e->frequencia > (*raiz)->entArr.array[0].frequencia) {
        if((*raiz)->dir == NULL) {
            avl *new = malloc(sizeof(avl));
            new->dir = NULL;
            new->esq = NULL;
            InicializaDAEntrada(&new->entArr);
            InsereDAEntrada(e, &new->entArr);
            (*raiz)->dir = new;
            return 0;
        }
        InsereAVL(&(*raiz)->dir, e);
    } else {
        //se chegou aqui quer dizer que a entrada ja esta na arvore
        InsereDAEntrada(e, &(*raiz)->entArr);
        return 0;
    }


    int fb = GetAltura((*raiz)->esq) - (GetAltura((*raiz)->dir));
    if(fb == -2) { // Arvore maior esta na direita
        int fbDir = GetAltura((*raiz)->dir->esq) - GetAltura((*raiz)->dir->dir);
        if(fbDir < 0) { //Desbalanceamento direito-direito
            RotacaoEsquerda(raiz);
            return 0;
        }

        if(fbDir > 0) { //Desbalanceamento direito-esquerdo
            RotacaoDireita(&(*raiz)->dir);
            RotacaoEsquerda(raiz);
            return 0;
        }
    }

    if(fb == 2) { // Arvore maior na esquerda
        int fbEsq = GetAltura((*raiz)->esq->esq) - GetAltura((*raiz)->esq->dir);
        if(fbEsq > 0) { // Desbalanceamento esquerda-esquerda
            RotacaoDireita(raiz);
            return 0;
        }

        if(fbEsq < 0) { // Desbalanceamento esquerdo-direito
            RotacaoEsquerda(&(*raiz)->esq);
            RotacaoDireita(raiz);
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
void LiberaAVL(avl **raiz) {
    if(*raiz == NULL) return;
    LiberaAVL(&(*raiz)->esq);
    LiberaAVL(&(*raiz)->dir);
    LiberaDAInt(&(*raiz)->entArr.array[0].offsets);
    free(*raiz);
    *raiz = NULL;
}
