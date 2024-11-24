#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "game.h"

void logo_drawer()  {
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





void menuInicial() {
    int opcao = 0;
    char entrada[10];
    do {
        
        printf("Tic Tac Toe Game\n");

        printf("1. Jogar\n");
        printf("2. Ver Ranking\n");
        printf("3. Creditos\n");
        printf("4. Sair\n");
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
                break;
    
            case 2:
                printf("\nAcessando ranking...\n\n");
                break;
    
            case 3:
                printf("\nCréditos:.\n\n");
                break;
    
            case 4:
                printf("Saindo do jogo. Até logo! \n\n");
                break;

            default:
                printf("\nOpcao invalida, tente novamente.\n\n");
                break;
        }

    } while (opcao != 4);

    return;
}




