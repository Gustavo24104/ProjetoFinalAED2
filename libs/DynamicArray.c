#include "../headers/DynamicArray.h"
#include <stdlib.h>
#include <stdio.h>


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




// Função de inserção na array dinaminca de offsets
int InsereDAInt(int e, dinArrayInt *arr) {
    if(arr == NULL) {
        return -1;
    }

    if(arr->qtd+1 >= arr->capacidade) {
        arr->capacidade *= 2; /* por motivos de performance (nao ficar realocando memória toda hora) é melhor dobrar
        a qtidade de memoria reservada pro vetor */
        int *newPtr;
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
    free(da->array);
    da->capacidade = 0;
    da->qtd = 0;
}



//Vetor dinamica de entradas
void InicializaDAEntrada(dinArrayEntrada *dae) {
    dae->qtd = 0;
    dae->capacidade = 1;
    dae->array = malloc(sizeof(entrada));
}

int InsereDAEntrada(entrada e, dinArrayEntrada *arr) {
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

    InicializaDAInt(&arr->array[arr->qtd].offsets); /* Como cada entrada tem um vetor dinamica de offsets, é preciso
    inicializar ele com cada novo elemento */
    arr->array[arr->qtd++] = e;
    return 0;
}


void LiberaDAEntrada(dinArrayEntrada *da) {
    for(int i = 0; i < da->qtd; ++i) {
        LiberaDAInt(&da->array[i].offsets);
    }
    free(da->array);
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

//---------------------------------------------------------------------------------------------------------------------

