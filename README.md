# Projeto de Estruturas de Dados III

Este documento apresenta, de forma formal, a descrição e os requisitos do projeto desenvolvido para a disciplina de Estrutura de Dados III, englobando três trabalhos práticos inter-relacionados que abordam a manipulação de arquivos binários, a construção e análise de grafos, bem como a implementação de um índice árvore-B.

---

### Integrantes:
|                          Nome | Nº USP   |
|------------------------------:|----------|
|    Gabriela Passos de Andrade | 12625142 |
|     Rafael Cunha Bejes Learth | 13676367 |

---

## 1. Trabalho Introdutório

O trabalho introdutório tem por objetivo a leitura de dados a partir de um arquivo CSV e a geração de um arquivo binário que os armazene segundo especificações rigorosas. Os principais aspectos incluem:

- **Registro de Cabeçalho:**  
  Contém informações como status do arquivo, próximo RRN, número de tecnologias e número de pares de tecnologias.

- **Registros de Dados:**  
  Os registros possuem campos de tamanho fixo e variável, com tratamento específico para valores nulos e preenchimento de lixo, de forma a garantir que cada byte seja ocupado conforme as especificações.

- **Objetivo:**  
  Assegurar a integridade dos dados e preparar o ambiente para as operações subsequentes, utilizando exclusivamente operações de entrada/saída no modo binário.

---

## 2. Trabalho Prático – Grafos

Este trabalho tem o foco na construção e análise de grafos direcionados ponderados, que representam as relações entre diferentes tecnologias. As funcionalidades implementadas incluem:

- **Construção do Grafo Original:**  
  A partir dos dados contidos no arquivo binário, é gerado um grafo em que cada vértice representa uma tecnologia, contendo informações sobre grupo, grau de entrada, grau de saída e grau total. Cada aresta, associada a um peso, representa a frequência com que os cliques ocorrem entre tecnologias.

- **Grafo Transposto:**  
  É gerada uma versão transposta do grafo original, invertendo as direções das arestas. A representação permanece na forma de listas de adjacências, com a ordenação adequada dos vértices e das arestas.

- **Busca de Origem:**  
  Dado o nome de uma tecnologia destino, o programa lista todas as tecnologias que originaram cliques para a mesma.

- **Análise de Conectividade:**  
  Determina se o grafo é fortemente conexo e calcula o número de componentes fortemente conexos presentes.

- **Caminho Mais Curto:**  
  Para um par de tecnologias (origem e destino), o sistema calcula o caminho de menor custo (em termos de peso) ou informa a inexistência de caminho entre elas.

---

## 3. Trabalho Prático – Índice Árvore-B

Este módulo do projeto aborda a implementação de um índice árvore-B para melhorar a eficiência das operações de busca e inserção em arquivos de dados. Os principais pontos são:

- **Estrutura do Índice:**  
  Cada página (ou nó) da árvore-B possui um tamanho fixo e armazena um número determinado de chaves, ponteiros e campos auxiliares, como o número de chaves, a altura do nó e o RRN do nó. A chave de busca é definida pela concatenação dos nomes das tecnologias de origem e destino, garantindo unicidade.

- **Algoritmo de Inserção:**  
  A inserção de novas chaves é realizada individualmente, aplicando-se a operação de split para manter a uniformidade da distribuição das chaves entre os nós.

- **Integração com Operações de Busca:**  
  A utilização do índice árvore-B permite a execução de buscas de forma eficiente, especialmente quando o critério de pesquisa envolve a chave de busca composta.

- **Requisitos Adicionais:**  
  O desenvolvimento deve seguir as especificações rigorosas quanto à manipulação de arquivos binários, uso exclusivo das funções da biblioteca `<stdio.h>` e cumprimento dos requisitos de documentação e modularização do código-fonte.

---

## 4. Requisitos Técnicos e Entrega

- **Linguagem de Programação:**  
  O projeto deve ser implementado utilizando a linguagem C (e, quando aplicável, C++), utilizando as funções de entrada e saída da biblioteca `<stdio.h>`.

- **Compilação e Execução:**  
  Um Makefile deve ser provido, contendo as diretivas necessárias para compilação (target `all`) e execução (target `run`).

- **Formato dos Arquivos:**  
  Os dados devem ser manipulados exclusivamente no modo binário, e todos os registros devem obedecer às especificações de tamanho e ordenação definidas.

- **Documentação:**  
  Todo o código-fonte deve ser devidamente comentado, incluindo identificação dos alunos responsáveis pelo desenvolvimento.

- **Material para Entrega:**  
  O produto final deve ser submetido em um arquivo compactado `.zip` contendo:  
  - Código-fonte documentado  
  - Makefile  
  - Vídeo explicativo (máximo de 5 minutos) em que todos os integrantes do grupo apresentam as funcionalidades implementadas

---

## Considerações Finais

O projeto integra conceitos fundamentais de manipulação de arquivos, estruturas de dados e algoritmos, demonstrando a aplicação prática dos conhecimentos adquiridos em sala de aula. A correta implementação dos trabalhos – desde a criação dos arquivos binários até a construção dos grafos e o uso do índice árvore-B – é essencial para a integridade e eficiência do sistema, atendendo aos rigorosos requisitos estabelecidos pela disciplina.

Este documento, portanto, sintetiza os objetivos, as especificações e os requisitos técnicos do projeto, servindo como referência para o desenvolvimento e a avaliação das funcionalidades implementadas.
