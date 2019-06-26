# Trabalho prático 2 de Pesquisa Operacional
## Gabriela Peres Neme - 2018054745

O objetivo do presente programa é retornar o corte mínimo em um grafo dirigido conexo ponderado.

### Dados de entrada
Descrição do grafo, feita pela entrada padrão (standard input).
A primeira linha da entrada contém dois inteiros separados por espaços, n e m, o número de vértices do grafo e o número de arestas entre eles, respectivamente. Seguem m linhas, cada uma com três inteiros, u , v e w , indicando
que existe uma aresta de peso w entre os vértices u e v. Não devem existir arestas paralelas nem laços no grafo em questão.

### Dados de saída
Descrição do corte mínimo obtido no grafo, feita pela saída padrão (standard output).
A primeira linha da saı́da contém a quantidade de vértices do conjunto S que define o corte mínimo no grafo. A segunda linha da saı́da contém o ı́ndice dos vértices de S, separados por espaços. A última linha contém o valor do corte mínimo.

### Como compilar
Usar o comando:
```
./compilar.sh
```
ou
```
make
```

### Como rodar
Para uma definição do grafo no arquivo "entrada.in", e para que o resultado do corte mínimo seja escrito em "saida.out", o programa deve ser rodado como:
```
./executar.sh entrada.in saida.out
```
ou
```
./bin/tp2 < entrada.in > saida.out
```