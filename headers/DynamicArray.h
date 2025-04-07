#ifndef PROJETOFINALAED2_DYNAMICARRAY_H
#define PROJETOFINALAED2_DYNAMICARRAY_H

/* Como a gente nãos sabe a qitdade de offsets de primeira mao, achei que talvez seria interessante fazer um vetor
 * dinamico para armazenar a lista de offsets de cada entrada, assim não precisa ficar gastando memória desnecessária.
 */

typedef struct {
    unsigned int *array;
    int qtd;
    int capacidade;
} dinArrayInt; //vetor dinamico usado pros offsets


typedef struct {
    char palavra[30];
    dinArrayInt offsets;
    int frequencia;
} entrada;

typedef struct {
    entrada *array;
    int qtd;
    int capacidade;
} dinArrayEntrada; //vetor dinamico usado para entradas (palavra + frequencia + lista)


int InsereDAInt(int e, dinArrayInt *arr);
void InicializaDAInt(dinArrayInt *arr);
void LiberaDAInt(dinArrayInt *da);
int InsereDAEntrada(entrada *e, dinArrayEntrada *arr);
void InicializaDAEntrada(dinArrayEntrada *dae);
void LiberaDAEntrada(dinArrayEntrada *da);
void ImprimeEntradas(dinArrayEntrada *de);
void ShellSort(dinArrayEntrada* vet);



#endif