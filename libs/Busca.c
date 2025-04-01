#include "../headers/Busca.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// Receve uma entrada (encontrada por meio de busca binaria ou alguma outra arvore de busca [AVL/Binária] + o nome do
// arquivo que se encontram as palavras
// Utiliza os offsets na struct para determinar as citações (busca todas as posições, lê a lista e imprime cada parte
// separadamente)
void ImprimeInfos(entrada *e, char *nomeArq) {
    FILE *arq = fopen(nomeArq, "rb"); /* abrindo em modo binário pra evitar problemas entre os separadores
    de linha de windows e UNIX (\CRLF vs \LF) */
    if(e == NULL) {
//        printf("Palavra nao encontrada, voce digitou corretamente?\n");
        return;
    }

    printf("Palavra encontrada: %s\n", e->palavra);
    printf("Frequencia: %d\n\n", e->frequencia);
    int ant = -1; //Não imprimir repetidos

    for(int i = 0; i < e->offsets.qtd; ++i) {
        fseek(arq, (long) e->offsets.array[i], 0);
        if(ant == e->offsets.array[i]) continue;
        char buff[500], *cit, *filme, *ano;
        fgets(buff, 500, arq);
        // Separação de cada parte da linha
        cit = strtok(buff, "\"");
        filme = strtok(NULL, "\",");
        ano = strtok(NULL, "\",");
        printf("Citacao: %s\n", cit);
        printf("Filme: %s\n", filme);
        printf("Ano: %s\n", ano);
        printf("\n");
        ant = (int) e->offsets.array[i];
    }
    fclose(arq);
}


//Busca a palavra passada e retorna uma refêrencia à sua entrada (assim passam-se todos os dados)
entrada* BuscaABB(arvore *raiz, char *palavra) {
    if(raiz == NULL) return NULL;
    if(strcmp(palavra, raiz->ent.palavra) == 0) return &raiz->ent;
    if(strcmp(palavra, raiz->ent.palavra) < 0) return BuscaABB(raiz->esq, palavra);
    if(strcmp(palavra, raiz->ent.palavra) > 0) return BuscaABB(raiz->dir, palavra);
}

void Infix(arvore *r, char *arq) {
    if(r == NULL) return;
    Infix(r->esq, arq);
    printf("Palavra: %s\n", r->ent.palavra);
    printf("Offsets: [");
    for(int j = 0; j < r->ent.offsets.qtd; ++j) {
        if(j != r->ent.offsets.qtd-1) printf("%03d, ", r->ent.offsets.array[j]);
        else printf("%03d]\n", r->ent.offsets.array[j]);
    }
    printf("Frequencia: %d\n\n", r->ent.frequencia);
    Infix(r->dir, arq);
}
