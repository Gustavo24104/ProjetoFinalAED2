#include "../headers/Entrada.h"
#include <stdlib.h>

int InsereArray(int e, dinArray *arr) {
    if(arr == NULL) {
        return -1;
    }


    if(arr->capacidade == 0) {
        arr->capacidade = 5;
    }

    if(arr->array == NULL) {
        arr->array = malloc(sizeof(int));
    }

    if(arr->capacidade == arr->qtd) {
        arr->capacidade *= 2;
        int *newPtr = realloc(arr->array, arr->capacidade);
        if(newPtr == NULL) {
            free(arr->array);
            return 1;
        }
    }

    arr->array[arr->qtd++] = e;
    return 0;
}



int LiberaArray() {

}
