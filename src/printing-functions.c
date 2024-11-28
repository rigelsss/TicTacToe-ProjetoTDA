// FUNÇÕES PARA PRINTAR INTERFACE E OUTROS ELEMENTOS DO JOGO

#include <stdio.h>                    // Biblioteca de funções entrada e saída (printf, scanf, etc)
#include <locale.h>                   // Biblioteca para configuração de localidade e idioma
#include <string.h>                   // Biblioteca de funções para string
#include <ctype.h>                    // Biblioteca para manipulação de caracteres (toupper, isdigit, etc)
#include <stdlib.h>                   // Biblioteca de funções para manipulação de memória
#include <windows.h>                  // Biblioteca específica do Windows
#include <time.h>                     // Biblioteca de funções de tempo
#include "load-game.h"                // Arquivo declarando as funções de ranking


// FUNÇÃO PARA PRINTAR A LOGO 
void mostrarLogo()  {
    printf("===========================================================\n");
    printf("  _____  _         _____              _____             \n");
    printf(" |_   _|(_)  ___  |_   _|__ _   ___  |_   _|___    ___  \n");
    printf("   | |  | | / __|   | | / _  | / __|   | | / _ \\  / _ \\ \n");
    printf("   | |  | || (__    | || (_| || (__    | | |(_)| |  __/ \n");
    printf("   |_|  |_| \\___|   |_| \\____| \\___|   |_| \\___/  \\___| \n");
    printf("                                                        \n");
    printf("===========================================================\n");
    printf("\n");

    return;
};


// FUNÇÃO PARA MOSTRAR O MENU DE OPÇÕES DO JOGO
void menuInicial() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    
    int opcao = 0;
    char entrada[10];
        
    do {
        printf("*** TIC TAC TOE ***\n");

        printf("1. Jogar\n");
        printf("2. Ver Ranking\n");
        printf("3. Creditos\n");
        printf("4. Sair\n\n");
        printf("Escolha uma opcao: ");
        
        fgets(entrada, sizeof(entrada), stdin);

        entrada[strcspn(entrada, "\n")] = '\0';

        if (!validarEntrada(entrada)) {
            printf("\nOpcao invalida, tente novamente.\n");
            continue;
        }
        
        opcao = atoi(entrada);
        
        switch (opcao)
        {
            case 1:
                printf("\nIniciando jogo...\n\n");
                iniciarJogo();
                break;
    
            case 2:
                printf("\nAcessando ranking...\n\n");
                lerRanking();
                break;
    
            case 3:
                mostrarCreditos();
                break;
    
            case 4:
                printf("\nSaindo do jogo... Ate logo! \n\n");
                break;

            default:
                printf("\nOpcao invalida, tente novamente.\n");
                break;
        }
    } while (opcao != 4);

    return;
}


// FUNÇÃO PARA PRINTAR O TABULEIRO DO JOGO
void imprimeTabuleiro(char tabuleiro[3][3]) {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", tabuleiro[i][j]); 
            if (j < 2) {
                printf("|"); 
            }
        }
        printf("\n"); 
        if (i < 2) {
            printf("---|---|---\n"); 
        }
    }
    printf("\n");
}


void mostrarCreditos() {
    // ARRAY DE STRINGS LITERAIS
    const char *autores[] = {
        "Beatriz Almeida de Souza Silva",
        "Gabriel Bianchini Carvalho",
        "Jose Carlos de Oliveira Neto",
        "Rigel Silva de Souza Sales"
    };
    int numAutores = sizeof(autores) / sizeof(autores[0]);

    int comprimentoMax = 0;
    for (int i = 0; i < numAutores; i++) {
        int comprimento = strlen(autores[i]);
        if (comprimento > comprimentoMax) {
            comprimentoMax = comprimento;
        }
    }

    comprimentoMax += 6;

    // PRINTANDO FORMATO DA CAIXA E TÍTULO
    printf("\n+");
    for (int i = 0; i < comprimentoMax; i++) {
        printf("-");
    }
    printf("+\n");

    const char *titulo = "CREDITOS";
    int espacosTitulo = (comprimentoMax - strlen(titulo)) / 2;
    printf("|");
    for (int i = 0; i < espacosTitulo; i++) {
        printf(" ");
    }
    printf("%s", titulo);
    for (int i = 0; i < comprimentoMax - strlen(titulo) - espacosTitulo; i++) {
        printf(" ");
    }
    printf("|\n");

    printf("|");
    for (int i = 0; i < comprimentoMax; i++) {
        printf("-");
    }
    printf("|\n");

    for (int i = 0; i < numAutores; i++) {
        int espacos = comprimentoMax - strlen(autores[i]) - 2;
        printf("| %s", autores[i]);
        for (int j = 0; j < espacos; j++) {
            printf(" ");
        }
        printf("|\n");
    }

    printf("+");
    for (int i = 0; i < comprimentoMax; i++) {
        printf("-");
    }
    printf("+\n");
    
    printf("\n");
}