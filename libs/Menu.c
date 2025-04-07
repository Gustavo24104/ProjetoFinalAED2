#include "../headers/Menu.h"
#include "../headers/DynamicArray.h"
#include "../headers/Leitura.h"
#include "../headers/Busca.h"
#include "../headers/Arvores.h"
#include <stdio.h>


//se precisar adicionar mais coisas, avisa
void Menu(){
    int escolha = 0;
    dinArrayEntrada de;
    arvore *arvNB = NULL;
    avl *arvAVL = NULL;
    InicializaDAEntrada(&de);
    char arq[100];
    char word[100];
    int inicio = 1;
    int frq = 0;

    while(inicio == 1){
        printf("Digite o nome de um arquivo para comecar:\n");
        fflush(stdin);
        fgets(arq, 100, stdin);
        arq[strlen(arq) - 1] = '\0';
        inicio = LeArquivo(arq, &de, &arvNB, &arvAVL);
        if (inicio == 1) printf("\nTente Novamente!\n");
    }

    while (escolha != -1){
        printf("\n(1)Trocar arquivo.\n(2)Busca por palavra.\n(3)Busca por frequencia.\n(-1)Encerrar.\n");
        scanf("%d", &escolha);
        switch (escolha){
            default:
                printf("\nOpcao invalida!\n");
                continue;

        case 1:
            LiberaArvore(&arvNB);
            LiberaAVL(&arvAVL);
            LiberaDAEntrada(&de);
            InicializaDAEntrada(&de);
            printf("\nDigite o nome do arquivo desejado:\n");
            fflush(stdin);
            fgets(arq, 100, stdin);
            arq[strlen(arq) - 1] = '\0';
            LeArquivo(arq, &de, &arvNB, &arvAVL);
            continue;

        case 2:
            printf("\nDigite a palavra desejada:\n");
            fflush(stdin);
            fgets(word, 100, stdin);
            word[strlen(word) - 1] = '\0';
            entrada* aux = NULL;
            aux = BuscaABB(arvNB, word);
            aux = BuscaBIN(&de, word, 0, (de.qtd)-1);
            if(aux == NULL) {
                    printf("palavra nao encontrada! voce digitou corretamente?");
                    continue;
            }
            ImprimeInfos(aux, arq);
            continue;

        case 3:
            printf("\nPalavras com frequencia x:\n");
            scanf("%d", &frq);
            ImprimePalavras(BuscaAVL(arvAVL, frq));
            continue;

        case -1:
            LiberaArvore(&arvNB);
            LiberaAVL(&arvAVL);
            LiberaDAEntrada(&de);
            printf("\nEncerrando...");
        }
    }
}
