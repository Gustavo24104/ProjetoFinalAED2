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

    for(int i = 0; i < e->offsets.qtd; ++i) {
        fseek(arq, (long) e->offsets.array[i], 0);
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
    }

    fclose(arq);
}