# Tic Tac Toe – TDA

**Desenvolvido como o projeto final da disciplina Técnicas e Desenvolvimento de Algoritmos (docente: Prof. Wallace Bonfim), curso de Ciência da Computação, semestre 2024.2.**

**Descrição:** Este é um jogo simples de **Tic Tac Toe** (ou **Jogo da Velha**), onde dois jogadores competem para colocar seus símbolos (X ou O) em uma grade 3x3, tentando formar uma linha com três símbolos iguais. O jogo termina quando um jogador ganha ou quando o tabuleiro está completo sem vencedores (empate).

Relatórios, video-demonstração e capturas de tela do jogo em funcionamento estão disponíveis na pasta 'docs'.

---

## Funcionalidades

- Dois jogadores podem jogar alternadamente.
- O tabuleiro é uma matriz 3x3 representada no console.
- O jogo verifica automaticamente se um jogador venceu ou se houve empate.
- O jogador pode ver o estado do tabuleiro a cada jogada.
- O ranking é mostrado em um arquivo
  
---

## Como rodar

1. Clone o repositório:
   ```bash
   git clone https://github.com/rigelsss/TicTacToe-ProjetoTDA
    ```
    
2. Abra o terminal e compile o código-fonte:
   ```bash
   gcc src/main.c src/control-functions.c src/printing-functions.c src/ranking-functions.c -o src/main
    ```

3. Execute o programa:
    ```bash
   src/main.exe
    ```

---

## Autores
- Beatriz Almeida de Souza Silva
- Gabriel Bianchini Carvalho
- José Carlos de Oliveira Neto
- Rigel Silva de Souza Sales