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

//Busca a palavra em frequência na arvore AVL, e retorna um ponteiro para o vetor de palavras que tem aquela frequência
dinArrayEntrada* BuscaAVL(avl *raiz, unsigned int freq) {
    if(raiz == NULL) return NULL;
    if(freq == raiz->entArr.array[0].frequencia) return &raiz->entArr;
    if(freq > raiz->entArr.array[0].frequencia) return BuscaAVL(raiz->dir, freq);
    if(freq < raiz->entArr.array[0].frequencia) return BuscaAVL(raiz->esq, freq);
}

//Imprime as palavras no vetor de entradas, usamos essa função junto com a buscaAVL para mostrar todas as palavras com
// uma frequência x
void ImprimePalavras(dinArrayEntrada *de) {
    for(int i = 0; i < de->qtd; ++i) {
        printf("Palavra: %s\n", de->array[i].palavra);
    }
}


entrada* BuscaBIN(dinArrayEntrada *vetor ,char *palavra, int esq, int dir){ //coloca que a direita é a qtd - 1
    if (vetor == NULL) return NULL;
    else{
        if (dir >= esq){
            int meio = (esq + dir)/2;

            if(strcmp(palavra, vetor->array[meio].palavra) == 0) return vetor->array;

            if(strcmp(palavra, vetor->array[meio].palavra) < 0){
                return BuscaBIN(vetor, palavra, esq, (meio-1));
            }

            if(strcmp(palavra, vetor->array[meio].palavra) > 0){
                return BuscaBIN(vetor, palavra, (meio+1), dir);
            }
        }
        else return NULL;
    }
}
