#ifndef PROJETOFINALAED2_ENTRADA_H
#define PROJETOFINALAED2_ENTRADA_H

/* Como a gente nãos sabe a qitdade de offsets de primeira mao, achei que talvez seria interessante fazer um vetor
 * dinamico para armazenar a lista de offsets de cada entrada, assim não precisa ficar gastando memória desnecessária.
 * Outra ideia seria percorrer o arquivo duas vezes: Uma inserindo tudo normal e contando a qtidade de palavras, e outra
 * colocando os offsets (agr que a qtidade eh conhcecida), mas acho bem melhor usar um vetor dinamico logo de cara
 */

typedef struct {
    int *array;
    int qtd;
    int capacidade;
} dinArray;


typedef struct {
    char palavra[100];
    dinArray *offsets;
    int frequencia;
} entrada;


int InsereArray(int e, dinArray *arr);


#endif