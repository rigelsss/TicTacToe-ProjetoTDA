// FUNÇÕES DE ESCREVER, LER E FAZER ATUALIZAÇÃO DO ARQUIVO DE RANKING

#include <stdio.h>                    // Biblioteca de funções entrada e saída (printf, scanf, etc)
#include <locale.h>                   // Biblioteca para configuração de localidade e idioma
#include <string.h>                   // Biblioteca de funções para string
#include <ctype.h>                    // Biblioteca para manipulação de caracteres (toupper, isdigit, etc)
#include <stdlib.h>                   // Biblioteca de funções para manipulação de memória
#include <windows.h>                  // Biblioteca específica do Windows
#include <time.h>                     // Biblioteca de funções de tempo
#include "load-game.h"           // Arquivo declarando as funções de ranking


// FUNÇÃO DE CRIAÇÃO DO ARQUIVO DE RANKING
// Leitura e escrita do arquivo .txt
// Realiza a manipulação da memória para armazenar as informações de ranking
void escreveRanking()  { 
    // STRUCT DE JOGADOR NO RANKING
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

    FILE *fileRanking = fopen("./ranking.txt", "r+");

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
            printf("A seguinte linha não sera considerada para o ranking: %s\n\n", linha);
        }

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

    fileRanking = fopen("./ranking.txt", "w");

    if (fileRanking == NULL) {
        printf("Erro ao abrir o arquivo 'ranking.txt' no modo escrita.\n");
        free(ranking);
        return;
    }

    fprintf(fileRanking, "***TIC TAC TOE - Ranking:***\n\n");

    for (int i = 0; i < tamanhoRanking; i++) {
        fprintf(fileRanking, "%d. %s - %d pontos\n", ranking[i].rank, ranking[i].nome, ranking[i].pontos);
    }

    time_t horaAtual = time(NULL);
    struct tm *tempoLocal = localtime(&horaAtual);

    strftime(dataHora, sizeof(dataHora), "%d/%m/%Y %H:%M:%S", tempoLocal);

    fprintf(fileRanking, "\nUltima aualizacao em: %s UTC-3", dataHora);

    fclose(fileRanking);

    for (int i = 0; i < tamanhoRanking; i++) {
        printf("%d. %s - %d pontos\n", ranking[i].rank, ranking[i].nome, ranking[i].pontos);
    }

    printf("\n");
}


// FUNÇÃO PARA LEITURA DO RANKING:
// Lê e exibe o conteúdo do arquivo ranking.txt no console.
void lerRanking() {

    setlocale(0, "Portuguese");

    FILE *fileRanking = fopen("./ranking.txt", "r");
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

    printf("\n\nPressione 'Enter' para voltar ao Menu principal.");
    getchar();

    printf("\n");
}


// FUNÇÃO PARA ATUALIZAÇÃO DO RANKING:
// Adiciona ou atualiza as informações de um jogador específico no ranking.
// Caso o jogador já exista, seus pontos são incrementados.
// Se for um jogador novo, ele é adicionado ao ranking.
void atualizarRanking(char *nome, int pontos) {
    typedef struct {
        int rank;
        int pontos;
        char nome[50];
    } Jogador;

    Jogador *ranking = NULL;
    int capacidadeRanking = 15;
    int tamanhoRanking = 0;
    char linha[100];
    char dataHora[100];

    ranking = (Jogador *)malloc(capacidadeRanking * sizeof(Jogador));
    if (!ranking) {
        printf("Erro na alocação de memória.\n");
        return;
    }

    FILE *fileRanking = fopen("./ranking.txt", "r");
    if (fileRanking == NULL) {
        printf("Arquivo de ranking não encontrado. Criando novo ranking...\n");
        fileRanking = fopen("./ranking.txt", "w");
        if (fileRanking == NULL) {
            printf("Erro ao criar o arquivo 'ranking.txt'.\n");
            free(ranking);
            return;
        }
        fprintf(fileRanking, "***TIC TAC TOE - Ranking:***\n\n");
        fclose(fileRanking);
    } else {
        while (fgets(linha, sizeof(linha), fileRanking)) {
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
                ranking[tamanhoRanking++] = temp;
            }
        }
        fclose(fileRanking);
    }

    int jogadorEncontrado = 0;
    for (int i = 0; i < tamanhoRanking; i++) {
        if (strcmp(ranking[i].nome, nome) == 0) {
            ranking[i].pontos += pontos;
            jogadorEncontrado = 1;
            break;
        }
    }
    if (!jogadorEncontrado) {
        if (tamanhoRanking >= capacidadeRanking) {
            capacidadeRanking *= 2;
            ranking = (Jogador *)realloc(ranking, capacidadeRanking * sizeof(Jogador));
            if (!ranking) {
                printf("Erro ao redimensionar memória.\n");
                return;
            }
        }
        strncpy(ranking[tamanhoRanking].nome, nome, sizeof(ranking[tamanhoRanking].nome));
        ranking[tamanhoRanking].pontos = pontos;
        tamanhoRanking++;
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

    fileRanking = fopen("./ranking.txt", "w");
    if (fileRanking == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        free(ranking);
        return;
    }

    fprintf(fileRanking, "***TIC TAC TOE - Ranking:***\n\n");

    for (int i = 0; i < tamanhoRanking; i++) {
        fprintf(fileRanking, "%d. %s - %d pontos\n", i + 1, ranking[i].nome, ranking[i].pontos);
    }

    time_t horaAtual = time(NULL);
    struct tm *tempoLocal = localtime(&horaAtual);
    strftime(dataHora, sizeof(dataHora), "%d/%m/%Y %H:%M:%S", tempoLocal);
    fprintf(fileRanking, "\nUltima atualização em: %s UTC-3", dataHora);

    fclose(fileRanking);
    free(ranking);
}
