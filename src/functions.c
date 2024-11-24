#include <stdio.h>
#include "game.h"
#include <wchar.h>


void logo_drawer()  {

    printf("  _____  _         _____              _____             \n");
    printf(" |_   _|(_)  ___  |_   _|__ _   ___  |_   _|___    ___  \n");
    printf("   | |  | | / __|   | | / _  | / __|   | | / _ \\  / _ \\ \n");
    printf("   | |  | || (__    | || (_| || (__    | | |(_)| |  __/ \n");
    printf("   |_|  |_| \\___|   |_| \\____| \\___|   |_| \\___/  \\___| \n");
    printf("                                                        \n");
    return;
};




void menuInicial() {
    int opcao;

    do {
        printf("=====================================================\n");
        printf("Tic Tac Toe Game\n");

        printf("1. Jogar\n");
        printf("2. Ver Ranking\n");
        printf("3. Creditos\n");
        printf("4. Sair\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
            case 1:
                break;
    
            case 2:
                break;
    
            case 3:
                break;
    
            case 4:
                printf("Saindo do jogo. Até logo! \n");
                break;

            default:
                printf("Opcao invalida, tente novamente.\n");
                break;
        }

    } while (opcao != 4);
}

void readRanking()  {
    
    FILE *ranking;
      
}