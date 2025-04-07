#include <stdio.h>
#include "headers/DynamicArray.h"
#include "headers/Leitura.h"
#include "headers/Busca.h"
#include <time.h>
#include <string.h>

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
        if (inicio != 0) printf("\nArquivo nao encontrado!\n");
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
                while(inicio == 1) {
                    printf("Digite o nome do arquivo desejado:\n");
                    fflush(stdin);
                    setbuf(stdin, NULL);
                    fgets(arq, 100, stdin);
                    arq[strlen(arq) - 1] = '\0';
                    inicio = LeArquivo(arq, &de, &arvNB, &arvAVL);
                    if (inicio != 0) printf("\nArquivo nao encontrado!\n");
                }
                continue;

            case 2:
                printf("\nDigite a palavra desejada:\n");
                fflush(stdin);
                setbuf(stdin, NULL);
                fgets(word, 100, stdin);
                word[strlen(word) - 1] = '\0';

                long double tempoABB = 0;
                long double tempoBIN = 0;
                entrada* aux1 = NULL;
                entrada* aux2 = NULL;

                start = clock();
                aux1 = BuscaABB(arvNB, word);
                end = clock();
                tempoABB = (double) (end - start)/CLOCKS_PER_SEC;

                start = clock();
                aux2 = BuscaBIN(&de, word, 0, (de.qtd)-1);
                end = clock();
                tempoBIN = (double) (end - start)/CLOCKS_PER_SEC;

                if(aux1 == NULL && aux2 == NULL) {
                    printf("palavra nao encontrada! voce digitou corretamente?");
                    continue;
                }

                ImprimeInfos(aux1, arq);
                ImprimeInfos(aux2, arq);
                printf("\nTempo de pesquisa de arvore nao balanceada: %.20Lf segs)\n", tempoABB);
                printf("\nTempo de pesquisa busca binaria: %.20Lf segs)\n", tempoBIN);
                continue;

            case 3:
                printf("Digite frequencia:\n");
                scanf("%d", &frq);
                long double tempoAVL = 0;
                start = clock();
                dinArrayEntrada *aux = BuscaAVL(arvAVL, frq);
                end = clock();
                if(aux == NULL) {
                    printf("Nao ha palavras com frequencia %d!\n", frq);
                    continue;
                }
                ImprimePalavras(aux);
                tempoAVL = (double) (end - start)/CLOCKS_PER_SEC;
                printf("Tempo de pesquisa por frequencia em AVL: %.20Lf segs\n", tempoAVL);
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
