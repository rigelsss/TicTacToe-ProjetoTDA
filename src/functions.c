#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include<time.h>
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


void escreveRanking()  { 

    typedef struct  {
        int rank;
        int pontos;
        char nome[50];
    } Jogador;

    int rank, pontos;
    char nome[50];
    int linhaAtual = 0;
    char linha[50];
    int capacidadeRanking = 15;
    int tamanhoRanking = 0;
    char dataHora[100];
    

    Jogador *ranking = (Jogador *)malloc(capacidadeRanking * sizeof(Jogador));

    if(!ranking)    {
        printf("Erro na alocação de memória.\n\n");
        return;
    }


    FILE *fileRanking = fopen("../assets/ranking.txt", "r+");


    if(fileRanking == NULL)    {
        printf("Acesso ao arquivo ranking.txt não realizado.\n\n");
        free(ranking);
        return;    
    }

    printf("Acesso ao arquivo ranking.txt realizado com sucesso.\n\n");
    

    while(fgets(linha, sizeof(linha), fileRanking)) {
        if (linhaAtual < 2) {
            linhaAtual++;
            continue;
        }


        if (tamanhoRanking >= capacidadeRanking) {
            capacidadeRanking *= 2;
            ranking = (Jogador *)realloc(ranking, capacidadeRanking * sizeof(Jogador));
            if (!ranking) {
                printf("Erro ao redimensionar memória.\n");
                fclose(fileRanking);
                return;
            }
        }

        Jogador temp;

        if (sscanf(linha, "%d. %[^-] - %d pontos", &temp.rank, temp.nome, &temp.pontos) == 3) {
            ranking[tamanhoRanking] = temp;
            tamanhoRanking++;
        } else {
            printf("Encontrado formato de linha invalido.\n");
            printf("A seguinte linha nao sera considerada para o ranking: %s\n\n", linha);
        }

    }

    for(int i = 0; i < tamanhoRanking - 1; i++) {

    }


    for (int i = 0; i < tamanhoRanking - 1; i++) {
        for (int j = 0; j < tamanhoRanking - i - 1; j++) {
            if (ranking[j].pontos < ranking[j + 1].pontos) {
                Jogador temp = ranking[j];
                ranking[j] = ranking[j + 1];
                ranking[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < tamanhoRanking; i++) {
        ranking[i].rank = i + 1;
    }


    fileRanking = fopen("../assets/ranking.txt", "w");

    if (fileRanking == NULL) {
        printf("Erro ao abrir o arquivo 'ranking.txt' no modo escrita.\n");
        free(ranking);
        return;
    }

    fprintf(fileRanking, "Tic Tac Toe - Ranking\n\n");


    for (int i = 0; i < tamanhoRanking; i++) {
        fprintf(fileRanking, "%d. %s- %d pontos\n", ranking[i].rank, ranking[i].nome, ranking[i].pontos);
    }

    time_t horaAtual = time(NULL);
    struct tm *tempoLocal = localtime(&horaAtual);

    strftime(dataHora, sizeof(dataHora), "%d/%m/%Y %H:%M:%S", tempoLocal);

    fprintf(fileRanking, "\nUltima aualizacao em: %s", dataHora);

    fclose(fileRanking);


    for (int i = 0; i < tamanhoRanking; i++) {
        printf("%d. %s- %d pontos\n", ranking[i].rank, ranking[i].nome, ranking[i].pontos);
    }


    printf("\n");
}



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


void lerRanking() {

    setlocale(0, "Portuguese");

    FILE *fileRanking = fopen("../assets/ranking.txt", "r");
    char linha[50];
    char nome[50];
    int rank, pontos;
    int linhaAtual = 0;

    if (fileRanking == NULL) {
        printf("Erro ao abrir o arquivo.\n\n");
        return;
    } else {
        printf("Ranking lido com sucesso!\n\n");
    }

    while(fgets(linha, sizeof(linha), fileRanking)) {
        printf("%s", linha);
    }

    fclose(fileRanking); 

    printf("\n\nPressione 'Enter' para voltar ao Menu principal \n");
    getchar();

    printf("\n");
}



void menuInicial() {

    setlocale(LC_ALL, "pt_BR.UTF-8");
    
    int opcao = 0;
    char entrada[10];
    
    
    do {
        
        printf("Tic Tac Toe Game - Menu\n");

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
                escreveRanking();
                break;
    
            case 2:
                printf("\nAcessando ranking...\n\n");
                lerRanking();
                break;
    
            case 3:
                printf("\nCreditos: \n\n");
                break;
    
            case 4:
                printf("\nSaindo do jogo... Ate logo! \n\n");
                break;

            default:
                printf("\nOpcao invalida, tente novamente.\n\n");
                break;
        }

    } while (opcao != 4);

    return;
}





