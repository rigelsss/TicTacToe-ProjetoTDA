// CARREGANDO AS FUNÇÕES

#ifndef LOAD_GAME_H
#define LOAD_GAME_H

// printing-functions.c:
void mostrarLogo();
void menuInicial();
void imprimeTabuleiro();
void mostrarCreditos();

// control-functions.c:
char iniciarJogo();
void realizarJogada(char tabuleiro[3][3], int linha, int coluna, char simbolo);
int validarEntrada();
int validarPosicao();
int validarJogada();
int verificarVencedor();

// ranking-functions.c:
void escreveRanking();
void lerRanking();
void atualizarRanking(char *nome, int pontos);

#endif