#include "../headers/Leitura.h"
#include "../headers/DinamycArray.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

int SeparaPalavras(char palavras[30][50], char *frase) {
    int i = 0;
    int j = 0;
    int qtdPalavras = 0;
    char acc[50];

    while(frase[i] != '\0'){
        if(frase[i] == ' ' || frase[i] == '.') {
            acc[j] = '\0';
            //printf("%s\n", acc);
            if(j >= 3) strcpy(palavras[qtdPalavras++], acc);
            j = 0;
            memset(acc, 0, 50);
            i++;
            continue;
        }

        if((frase[i] >= 65 && frase[i] <= 90) || (frase[i] >= 97 && frase[i] <= 122)) { //verifica se eh palavra
            //transforma em minusculo
            if(frase[i] >= 65 && frase[i] <= 90) acc[j] = (frase[i] + 32);
            else acc[j] = frase[i];
            j++;
        }
        i++;
    }
    return qtdPalavras;
}

int JaExiste(dinArrayEntrada *de, char *palavra) {
    for(int i = 0; i < de->qtd; ++i) {
        if(strcmp(palavra, de->array[i].palavra) == 0) return i;
    }
    return -1;
}


void InsereVetor(char palavra[30][50], dinArrayEntrada *de, int qtd, int offs) {
    for (int i = 0; i < qtd; ++i) {
        int existe = JaExiste(de, palavra[i]);
        if (existe >= 0) { //palavra existente, 'existe' indica seu indice
            de->array[existe].frequencia++;
            InsereDAInt(offs, &de->array[existe].offsets);
            continue;
        }
        entrada new;
        new.frequencia = 1;
        InicializaDAInt(&new.offsets);
        strcpy(new.palavra, palavra[i]);
        InsereDAEntrada(new, de);
        InsereDAInt(offs, &de->array[de->qtd - 1].offsets);
    }
}


int LeArquivo(char *nomeArq, dinArrayEntrada *de) {
    FILE* arq = fopen(nomeArq, "r");
    if(arq == NULL) {
        printf("Arquivo nao encontrado!\n");
        return 1;
    }
    char buff[500];

    double tempoVetor = 0;
    //TODO: Explicar

    long offs = ftell(arq); //o primeiro ftell tem que ser antes da primeira leitura
    while(fgets(buff, 500, arq)) {
        char *frase, palavra[30][50];
        frase = strtok(buff, "\"");
        int qtd = SeparaPalavras(palavra, frase);
        time_t start = clock();
        InsereVetor(palavra, de, qtd, offs);
        time_t end = clock();
        tempoVetor += ((double)(end - start)/CLOCKS_PER_SEC);

        //time_t
        //Insere Arvore
        //time_t

        //time_t
        //Insere arvore AVL
        //time_t
        offs = ftell(arq);
    }

//    time_t start = clock();
//    OrdenaVetor();
//    time_t end = clock();
//    tempoVetor += ((double)(end - start)/CLOCKS_PER_SEC);
    printf("Tempo para insercao e ordenacao no vetor: %lf segs\n", tempoVetor);
    fclose(arq);


    return 0;
}