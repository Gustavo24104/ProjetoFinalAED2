#include <stdio.h>
#include "headers/DynamicArray.h"
#include "headers/Leitura.h"
#include "headers/Busca.h"
#include "headers/Menu.h"
#include <time.h>

/*
 * Ideia geral: cada entrada eh representado por uma struct, após a leitura do arquivo (feita por uma função) um vetor
 * armazena todas as entradas (pra busca binária), veja o aruquivo Entrada.h para mais comentário sobre a organização
 * da struct
 *
 * A principal duvida: é melhor ja tentar inserir todas essas citações ordenadas ou ordenar dps de inserir tudo (eu acho
 * que eh a segunda opção, mas nn tenho ctz)
 *
 * O problema 'A' eh bem simples, basta ler todo o arquivo, separando tudo pela virgula e limpando os pontos finais,
 * virgulas, etc
 *
 * O problema 'B' também não é complicado: O usuário digita a palavra de busca, essa palavra eh encontrada dentro da
 * memória do programa (por meio de busca binária no vetor e a arvore de busca nao balanceada),
 * e, usando sua lista de offsets conseguimos imprimir o que é pedido corretamente
 *
 * O problema 'C' basta inserir os elementos na arvore AVL (fazer isso depois da leitura do arquivo pois é necessário
 * saber a frequência anteriormente) e fazer a busca binária de modo normal. O mais chato dessa questão será o balancea-
 * mento da árvore
 *
 *
 * Outro detalhe é que durante a execução do programa o usuário pode mudar o arquivo escolhido, para isso temos que
 * liberar as estruturas e recarregá-las
 */
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
    time_t start = 0, end = 0;

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
                inicio = 1;
                while(inicio == 1){
        printf("Digite o nome do arquivo desejado:\n");
        fflush(stdin);
        fgets(arq, 100, stdin);
        arq[strlen(arq) - 1] = '\0';
        inicio = LeArquivo(arq, &de, &arvNB, &arvAVL);
        if (inicio == 1) printf("\nTente Novamente!\n");
    }
                continue;

            case 2:
                printf("\nDigite a palavra desejada:\n");
                fflush(stdin);
                fgets(word, 100, stdin);
                word[strlen(word) - 1] = '\0';

                double tempoABB = 0;
                double tempoBIN = 0;
                entrada* aux1 = NULL;
                entrada* aux2 = NULL;

                start = clock();
                aux1 = BuscaABB(arvNB, word);
                end = clock();
                tempoABB = (end - start)/CLOCKS_PER_SEC;

                start = clock();
                aux2 = BuscaBIN(&de, word, 0, (de.qtd)-1);
                end = clock();
                tempoBIN = (end - start)/CLOCKS_PER_SEC;

                if(aux1 == NULL && aux2 == NULL) {
                    printf("palavra nao encontrada! voce digitou corretamente?");
                    continue;
                }

                printf("\nPor busca de arvore nao balanceada (tempo: %.4lf segs):\n", tempoABB);
                ImprimeInfos(aux1, arq);
                printf("\nPor busca binaria (tempo: %.4lf segs):\n", tempoBIN);
                ImprimeInfos(aux2, arq);
                continue;

            case 3:
                printf("\nPalavras com frequencia x:\n");
                scanf("%d", &frq);
                double tempoAVL = 0;
                start = clock();
                ImprimePalavras(BuscaAVL(arvAVL, frq));
                end = clock();
                tempoAVL = (end - start)/CLOCKS_PER_SEC;
                printf("Custo da busca por frequencia em AVL: %.4lf segs\n", tempoAVL);
                continue;

            case -1:
                LiberaArvore(&arvNB);
                LiberaAVL(&arvAVL);
                LiberaDAEntrada(&de);
                printf("\nEncerrando...");
        }
    }
}

int main() {
    Menu();
    return 0;
}
