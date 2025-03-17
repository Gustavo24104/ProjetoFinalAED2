#include "../headers/DinamycArray.h"
#include <stdlib.h>
#include <stdio.h>


//------------------------------------------ Funções de array dinânimicas ---------------------------------------------
void InicializaDAInt(dinArrayInt *arr){
    if(arr == NULL) {
        printf("UE\n");
        return;
    }
    arr->array = malloc(sizeof(int));
    arr->qtd = 0;
    arr->capacidade = 1;
}

int InsereDAInt(int e, dinArrayInt *arr) {
    if(arr == NULL) {
        return -1;
    }

    if(arr->qtd+1 >= arr->capacidade) {
        arr->capacidade *= 2;
        int *newPtr;
        newPtr = realloc(arr->array, arr->capacidade * sizeof(int));
        if(newPtr == NULL) {
            free(newPtr);
            return 1;
        }
        arr->array = newPtr;
    }


    arr->array[arr->qtd++] = e;
    return 0;
}

void LiberaDAInt(dinArrayInt *da) {
    free(da->array);
    da->capacidade = 0;
    da->qtd = 0;
}



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

    InicializaDAInt(&arr->array[arr->qtd].offsets); //test
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

