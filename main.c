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
    arvore *arvAVLPalavras = NULL;
    avlFrequencia *arvAVLFrequencia = NULL;
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
        inicio = LeArquivo(arq, &de, &arvNB, &arvAVLPalavras,&arvAVLFrequencia);
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
                LiberaArvore(&arvAVLPalavras);
                LiberaAVL(&arvAVLFrequencia);
                LiberaDAEntrada(&de);
                InicializaDAEntrada(&de);
                inicio = 1;
                while(inicio == 1) {
                    printf("Digite o nome do arquivo desejado:\n");
                    fflush(stdin);
                    setbuf(stdin, NULL);
                    fgets(arq, 100, stdin);
                    arq[strlen(arq) - 1] = '\0';
                    inicio = LeArquivo(arq, &de, &arvNB, &arvAVLPalavras, &arvAVLFrequencia);
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
                long double _tempoAVL = 0;
                long double tempoBIN = 0;
                struct timespec para, com;
                long double microABB = 0, microAVL = 0, microBIN = 0;
                entrada* aux1 = NULL;
                entrada* aux2 = NULL;
                entrada* aux3 = NULL;

                //Arvore binária
                start = clock();
                clock_gettime(CLOCK_MONOTONIC, &com);
                aux1 = BuscaABB(arvNB, word);
                clock_gettime(CLOCK_MONOTONIC, &para);
                end = clock();
                tempoABB = (double) ((double) (end - start)/CLOCKS_PER_SEC);
                microABB =  (para.tv_sec - com.tv_sec) * 1000000 + para.tv_nsec - com.tv_nsec;

                //Vetor com busca binaria
                start = clock();
                clock_gettime(CLOCK_MONOTONIC, &com);
                aux2 = BuscaBIN(&de, word, 0, (de.qtd)-1);
                clock_gettime(CLOCK_MONOTONIC, &para);
                end = clock();
                microBIN =  (para.tv_sec - com.tv_sec) * 1000000 + para.tv_nsec - com.tv_nsec;
                tempoBIN = (double) (end - start)/CLOCKS_PER_SEC;

                //Arvore AVL
                start = clock();
                clock_gettime(CLOCK_MONOTONIC, &com);
                aux3 = BuscaABB(arvAVLPalavras, word);
                clock_gettime(CLOCK_MONOTONIC, &para);
                end = clock();
                microAVL =  (para.tv_sec - com.tv_sec) * 1000000 + para.tv_nsec - com.tv_nsec;
                _tempoAVL = (double) (end - start)/CLOCKS_PER_SEC;


                if(aux1 == NULL && aux2 == NULL) {
                    printf("palavra nao encontrada! voce digitou corretamente?");
                    continue;
                }

                ImprimeInfos(aux1, arq);
                ImprimeInfos(aux2, arq);
                ImprimeInfos(aux3, arq);
                printf("\nTempo de pesquisa de arvore nao balanceada: %Lg segs\n", microABB);
                printf("\nTempo de pesquisa busca binaria: %Lg segs\n", microBIN);
                printf("\nTempo de pesquisa arvore AVL de palavras: %Lg segs\n", microAVL);
                continue;

            case 3:
                printf("Digite frequencia:\n");
                scanf("%d", &frq);
                long double tempoAVL = 0;
                start = clock();
                clock_gettime(CLOCK_MONOTONIC, &com);
                dinArrayEntrada *aux = BuscaAVL(arvAVLFrequencia, frq);
                end = clock();
                clock_gettime(CLOCK_MONOTONIC, &para);
                tempoAVL =  (para.tv_sec - com.tv_sec) * 1000000 + para.tv_nsec - com.tv_nsec;
                if(aux == NULL) {
                    printf("Nao ha palavras com frequencia %d!\n", frq);
                    continue;
                }
                ImprimePalavras(aux);
                tempoAVL = (double) (end - start)/CLOCKS_PER_SEC;
                printf("Tempo de pesquisa por frequencia em AVL: %Lg segs\n", tempoAVL);
                continue;

            case -1:
                LiberaArvore(&arvNB);
                LiberaAVL(&arvAVLFrequencia);
                LiberaDAEntrada(&de);
                printf("\nEncerrando...");
        }
    }
}

int main() {
   Menu();


    return 0;

}
