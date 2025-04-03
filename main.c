#include <stdio.h>
#include "headers/DynamicArray.h"
#include "headers/Leitura.h"
#include "headers/Busca.h"

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

//int ContaNos(arvore *a, int count) {
//    if(a == NULL) return count;
//    ContaNos(a->dir, ++count);
//    ContaNos(a->esq, ++count);
//}


int main() {
    dinArrayEntrada de;
    arvore *arvNB = NULL;
    arvore *arvAVL = NULL;
    InicializaDAEntrada(&de);
    LeArquivo("small.csv", &de, &arvNB);
    //TODO: Função de ordenação
//    ImprimeEntradas(&de);


    //ImprimeInfos(BuscaABB(arvNB, "dog"), "subset.csv");


    LiberaDAEntrada(&de);
    return 0;
}
