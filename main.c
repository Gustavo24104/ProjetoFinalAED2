#include <stdio.h>
#include "headers/DinamycArray.h"
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
 * memória do programa, e, usando sua lista de offsets conseguimos imprimir o que é pedido corretamente
 *
 * O problema 'C' ainda não sabemos resolver
 *
 */

int main() {

    dinArrayEntrada de;
    InicializaDAEntrada(&de);
    LeArquivo("subset.csv", &de);
    //TODO: Função de ordenação
    ImprimeEntradas(&de);
    ImprimeInfos(&de.array[0], "subset.csv");
    return 0;
}
