#ifndef PROJETOFINALAED2_DYNAMICARRAY_H
#define PROJETOFINALAED2_DYNAMICARRAY_H

/* Como a gente nãos sabe a qitdade de offsets de primeira mao, achei que talvez seria interessante fazer um vetor
 * dinamico para armazenar a lista de offsets de cada entrada, assim não precisa ficar gastando memória desnecessária.
 * Outra ideia seria percorrer o arquivo duas vezes: Uma inserindo tudo normal e contando a qtidade de palavras, e outra
 * colocando os offsets (agr que a qtidade eh conhcecida), mas acho bem melhor usar um vetor dinamico logo de cara
 */

typedef struct {
    int *array;
    int qtd;
    int capacidade;
} dinArrayInt;


typedef struct {
    char palavra[30];
    dinArrayInt offsets;
    int frequencia;
} entrada;

typedef struct {
    entrada *array;
    int qtd;
    int capacidade;
} dinArrayEntrada;


int InsereDAInt(int e, dinArrayInt *arr);
void InicializaDAInt(dinArrayInt *arr);
void LiberaDAInt(dinArrayInt *da);
int InsereDAEntrada(entrada e, dinArrayEntrada *arr);
void InicializaDAEntrada(dinArrayEntrada *dae);
void LiberaDAEntrada(dinArrayEntrada *da);
void ImprimeEntradas(dinArrayEntrada *de);



#endif