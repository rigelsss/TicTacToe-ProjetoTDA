// FUNÇÕES QUE RODAM O JOGO E REALIZAM O TRATAMENTO DE ERROS

#include <stdio.h>                    // Biblioteca de funções entrada e saída (printf, scanf, etc)
#include <locale.h>                   // Biblioteca para configuração de localidade e idioma
#include <string.h>                   // Biblioteca de funções para string
#include <ctype.h>                    // Biblioteca para manipulação de caracteres (toupper, isdigit, etc)
#include <stdlib.h>                   // Biblioteca de funções para manipulação de memória
#include <windows.h>                  // Biblioteca específica do Windows
#include <time.h>                     // Biblioteca de funções de tempo
#include "load-game.h"                // Arquivo declarando as funções de ranking

// FUNÇÃO PARA INICIAR A PARTIDA
char iniciarJogo()   {
    char entrada[5];
    int linha;
    int coluna;
    int resultado = 0;
    int turno = 0;

    typedef struct  {
        char nome[50];
        char simbolo;
        int pontuacao;
    } Player;

    char tabuleiro[3][3] = {

        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}

    };

    Player jogador[2];

    printf("Digite o nome do Jogador 'X': ");
    fgets(jogador[0].nome, sizeof(jogador[0].nome), stdin);
    jogador[0].simbolo = 'X';
    jogador[0].nome[strcspn(jogador[0].nome, "\n")] = '\0';
    jogador[0].pontuacao = 0;

    printf("Digite o nome do Jogador 'O': ");
    fgets(jogador[1].nome, sizeof(jogador[turno].nome), stdin);
    jogador[1].simbolo = 'O';
    jogador[1].nome[strcspn(jogador[1].nome, "\n")] = '\0';
    jogador[1].pontuacao = 0;

    while(resultado == 0)   {
        imprimeTabuleiro(tabuleiro);
        
        printf("%s (%c), escolha em qual linha jogar (1-3): ", jogador[turno].nome, jogador[turno].simbolo);
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strcspn(entrada, "\n")] = '\0';

        if (!validarEntrada(entrada)) {
            printf("\nEntrada invalida %s, digite um valor entre 1 e 3.\n", jogador[turno].nome);
            continue;
        }

        linha = atoi(entrada);

        printf("%s (%c), escolha em qual coluna jogar (1-3): ", jogador[turno].nome, jogador[turno].simbolo);  
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strcspn(entrada, "\n")] = '\0';

        if (!validarEntrada(entrada)) {
            printf("\nEntrada invalida %s, digite um valor entre 1 e 3.\n", jogador[turno].nome);
            continue;
        }

        coluna = atoi(entrada);

        if(validarJogada(tabuleiro, linha - 1, coluna -1))  {
            realizarJogada(tabuleiro, linha -1, coluna - 1, jogador[turno].simbolo);
            resultado = verificarVencedor(tabuleiro);

            if(resultado == 1)  {
                imprimeTabuleiro(tabuleiro);
                printf("Parabens %s, voce foi o vencedor!\n", jogador[turno].nome);

                jogador[turno].pontuacao += 10;
                atualizarRanking(jogador[turno].nome, jogador[turno].pontuacao);

                printf("\n\nPressione 'Enter' para voltar ao Menu principal.");
                getchar();
                break;
            }

            else if(resultado == -1)    {
                imprimeTabuleiro(tabuleiro);
                printf("O jogo terminou empatado.\n");
                printf("\n\nPressione 'Enter' para voltar ao Menu principal.");
                getchar();
                break;
            }

        turno = 1 - turno;       
    }    

        else    {
            printf("\nJogada invalida %s, tente novamente.\n", jogador[turno].nome);
        }
    }
    return 0;
}


// FUNÇÃO PARA ATUALIZAR O TABULEIRO COM OS SÍMBOLOS DOS JOGADORES NAS POSIÇÕES ESPECIFICADAS
void realizarJogada(char tabuleiro[3][3], int linha, int coluna, char simbolo)    {
    tabuleiro[linha][coluna] = simbolo;
}


// FUNÇOES PARA VERIFICAR SE A ENTRADA DO JOGADOR É COMPOSTA POR APENAS DÍGITOS E NÃO ESTÁ VAZIA
int validarEntrada(char *entrada) {
    int i = 0;

    if (entrada[0] == '\0') {
        return 0;
    }

    while (entrada[i] != '\0') {
        if (!isdigit(entrada[i])) {
            return 0; 
        }
        i++;
    }
    return 1; 
}

int validarPosicao(int *entrada) {
    int i = 0;

    if (entrada[0] == '\0') {
        return 0;
    }

    while (entrada[i] != '\0') {
        if (!isdigit(entrada[i])) {
            return 0; 
        }
        i++;
    }
    return 1; 
}


// FUNÇÃO PARA VERIFICAR SE A JOGADA ESTÁ NOS LIMITES DO TABULEIRO E O ESPAÇO ESTÁ VAZIO
int validarJogada(char tabuleiro[3][3], int linha, int coluna)  {
    if(linha >= 0 && linha < 3 && coluna >= 0 && coluna <3) {
        if(tabuleiro[linha][coluna] == ' ') {
                 return 1;

            }     
    }
    
    return 0;
}


// FUNÇÃO PARA CHECAR SE HOUVE VENCEDOR, EMPATE OU O JOGO CONTINUA
int verificarVencedor(char tabuleiro[3][3]) {
    for(int i = 0; i < 3; i++)  {
        if (tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2] && tabuleiro[i][0] != ' ')
            return 1;
    
        if (tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[1][i] == tabuleiro[2][i] && tabuleiro[0][i] != ' ')
            return 1;

    }

    if (tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2] && tabuleiro[0][0] != ' ')
        return 1;
    if (tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0] && tabuleiro[0][2] != ' ')
        return 1;


    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tabuleiro[i][j] == ' ')
                return 0; 
        }
    }

    return -1;
}