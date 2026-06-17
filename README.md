# 🎲 Caminho do Conhecimento: O Jogo de AED

O **Caminho do Conhecimento** é um jogo de tabuleiro educacional desenvolvido em linguagem C. O projeto foi idealizado pelo Clube de Programação da Universidade Senai Cimatec como uma forma lúdica e prática de aplicar os conceitos fundamentais da disciplina de **Algoritmos e Estruturas de Dados (AED)**.

No jogo, de 2 a 4 jogadores disputam um percurso de no mínimo 30 casas, divididas em 3 unidades temáticas da disciplina. O avanço depende tanto da sorte (dado virtual) quanto do conhecimento (perguntas sobre a matéria).

---

## 🛠️ Arquitetura de Estruturas de Dados

Cada funcionalidade do jogo foi projetada utilizando uma estrutura de dados específica para garantir a eficiência exigida pelo projeto:

| Funcionalidade / Requisito | Estrutura de Dados Aplicada | Justificativa Técnica |
| :--- | :--- | :--- |
| **Ordem das Rodadas** | Fila Dinâmica (`Queue`) | Garante rigorosamente a ordem de entrada dos jogadores (FIFO). O jogador da vez joga e é reposicionado ao final da fila. |
| **O Tabuleiro** | Lista Duplamente Encadeada | Permite a alocação dinâmica das casas e a navegação linear bidirecional (para frente e para trás), necessária para efeitos de avanço e retorno. |
| **Banco de Perguntas** | Pilha Dinâmica (`Stack`) | As perguntas de cada unidade funcionam de modo que a última inserida (ou reembaralhada) seja a primeira utilizada (LIFO), retirando-se do topo até esgotar. |
| **Estatísticas das Casas** | Árvore Binária de Busca (BST) ou AVL | Utiliza o número da casa como chave para garantir buscas e atualizações rápidas com complexidade de tempo logarítmica $O(\log n)$ no caso médio. |

---

## 🎮 Funcionamento do Jogo

### 1. Dinâmica da Rodada
* Entre **2 e 4 jogadores** são cadastrados e iniciam na casa 0 (Início).
* A cada turno, o jogador lança um dado virtual ($1$ a $6$) e avança pelo tabuleiro.
* O jogo termina assim que o primeiro jogador alcança ou ultrapassa a última casa (Aprovação).

### 2. Casas Especiais e Perguntas
Ao longo do tabuleiro existem casas normais e casas com efeitos especiais:
* **Casas de Avanço/Retorno:** Movem o jogador diretamente para frente ou para trás.
* **Casas de Pergunta:** Sorteiam um nível de dificuldade (Fácil, Médio ou Difícil) para uma questão baseada na unidade atual do jogador.
  * **Acerto:** Concede avanço extra ($+1$ para Fácil, $+2$ para Médio, $+3$ para Difícil).
  * **Erro:** Aplica penalidades (como perda de turno ou retorno de casas).

### 3. Registro de Dados e Persistência
Ao cair em qualquer casa, o sistema contabiliza o evento na árvore de estatísticas. Ao encerrar o jogo, a estrutura grava um relatório em disco contendo:
* Quantidade de vezes que cada casa foi visitada.
* Total de acertos e erros por posição.

---

## 📋 Requisitos do Sistema (Mínimos)

* **Tabuleiro:** Mínimo de 30 casas (10 por unidade da disciplina).
* **Perguntas:** Banco de dados com no mínimo 18 perguntas (6 por unidade, distribuídas igualmente entre as dificuldades).
* **Interface:** CLI (Interface de Linha de Comando) limpa, organizada e intuitiva.

---

## 🚀 Como Executar o Projeto

### Pré-requisitos
Você precisará de um compilador C (como o `gcc`) instalado em sua máquina.

### Passo a Passo

1. Clone o repositório:
   ```bash
   git clone [https://github.com/seu-usuario/caminho-do-conhecimento.git](https://github.com/seu-usuario/caminho-do-conhecimento.git)
