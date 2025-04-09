#include "../headers/DynamicArray.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//------------------------------------------ Funções de array dinânimicas ---------------------------------------------

//Array dinamica de inteiro usadas para offsets
void InicializaDAInt(dinArrayInt *arr){
    if(arr == NULL) {
        return;
    }

    arr->array = malloc(sizeof(int));
    arr->qtd = 0;
    arr->capacidade = 1;
}




// Insere no vector de inteiros, verifica se nao estourou a capacidade e coloca um novo
int InsereDAInt(int e, dinArrayInt *arr) {
    if(arr == NULL) {
        return -1;
    }

    if(arr->qtd+1 >= arr->capacidade) {
        arr->capacidade *= 2; /* por motivos de performance (nao ficar realocando memória toda hora) é melhor dobrar
        a qtidade de memoria reservada pro vetor */
        unsigned int *newPtr;
        newPtr = realloc(arr->array, arr->capacidade * sizeof(int));
        if(newPtr == NULL) {
            free(newPtr);
            return 1;
        }
        arr->array = newPtr;
    }

    arr->array[arr->qtd++] = e; //coloca o elemento no final do vetor
    return 0;
}

void LiberaDAInt(dinArrayInt *da) {
    free((da)->array);
    (da)->capacidade = 0;
    (da)->qtd = 0;
    //*da = NULL;
}



//Vetor dinamica de entradas
void InicializaDAEntrada(dinArrayEntrada *dae) {
    dae->qtd = 0;
    dae->capacidade = 1;
    dae->array = malloc(sizeof(entrada));
}


//Inserir nova entrada, verifica se nao estourou a capacidade e insere
//Função assume que ja inicializou o vetor dinamico de offsets
int InsereDAEntrada(entrada *e, dinArrayEntrada *arr) {
    if(arr == NULL) {
        return -1;
    }

    if(arr->qtd+1 >= arr->capacidade) {
        arr->capacidade *= 2;
        entrada *newPtr;
        newPtr = realloc(arr->array, arr->capacidade * sizeof(entrada));
        if(newPtr == NULL) {
            free(newPtr);
            return 1;
        }
        arr->array = newPtr;
    }


    arr->array[arr->qtd] = *e;
    arr->array[arr->qtd].offsets.array = malloc(e->offsets.capacidade * sizeof(unsigned int)); /* Aloca nova
    memória pra garantir que o array de offsets de 'e' e 'arr' apontem para espaços diferentes na memória, evitando
    conflitos */
    memcpy(arr->array[arr->qtd++].offsets.array, e->offsets.array,
           e->offsets.capacidade * sizeof(unsigned int)); /* copiar array pra
    pra garantir que ambas estejam separadas */
    return 0;
}


void LiberaDAEntrada(dinArrayEntrada *da) {
    for(int i = 0; i < da->qtd; ++i) {
        LiberaDAInt(&da->array[i].offsets);
    }
    free(da->array);
    da->array = NULL;
    da->capacidade = 0;
    da->qtd = 0;
}


void ImprimeEntradas(dinArrayEntrada *de) {
    for(int i = 0; i < de->qtd; ++i) {
        printf("Palavra: %s\n", de->array[i].palavra);
        printf("Offsets: [");
        for(int j = 0; j < de->array[i].offsets.qtd; ++j) {
            if(j != de->array[i].offsets.qtd-1) printf("%03d, ", de->array[i].offsets.array[j]);
            else printf("%03d]\n", de->array[i].offsets.array[j]);
        }
        printf("Frequencia: %d\n\n", de->array[i].frequencia);
    }
}

void ShellSort(dinArrayEntrada* vet) {
    int h = 1;
    int j;
    char key[30];
    entrada aux;
    do h = h * 3 + 1; while (h < vet->qtd);
    do {
        h = h/3;
        for (int i = h; i < vet->qtd;  i++) {
            strcpy(key, vet->array[i].palavra);
            aux = vet->array[i];
            j = i - h;
            while (j >= 0 && (strcmp(vet->array[j].palavra, aux.palavra) > 0)) {
                vet->array[j+h] = vet->array[j];
                j-=h;
            }
            vet->array[j+h] = aux;
        }
    }while (h > 1);
}



//---------------------------------------------------------------------------------------------------------------------

