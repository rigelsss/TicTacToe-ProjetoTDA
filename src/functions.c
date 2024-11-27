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

int validarJogada(char tabuleiro[3][3], int linha, int coluna)  {
    if(linha >= 0 && linha < 3 && coluna >= 0 && coluna <3) {
        if(tabuleiro[linha][coluna] == ' ') {
                 return 1;

            }     
    }
    return 0;

}

void realizarJogada(char tabuleiro[3][3], int linha, int coluna, char simbolo)    {
    tabuleiro[linha][coluna] = simbolo;
}


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


    printf("Digite o nome do Jogador 'O': ");
    fgets(jogador[1].nome, sizeof(jogador[turno].nome), stdin);
    jogador[1].simbolo = 'O';
    jogador[1].nome[strcspn(jogador[1].nome, "\n")] = '\0';


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

    FILE *fileRanking = fopen("../assets/ranking.txt", "r");
    if (fileRanking == NULL) {
        printf("Arquivo de ranking não encontrado. Criando novo ranking...\n");
    } else {
        // Ler o ranking existente
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

    // Atualizar ou adicionar o jogador
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

    // Ordenar o ranking
    for (int i = 0; i < tamanhoRanking - 1; i++) {
        for (int j = 0; j < tamanhoRanking - i - 1; j++) {
            if (ranking[j].pontos < ranking[j + 1].pontos) {
                Jogador temp = ranking[j];
                ranking[j] = ranking[j + 1];
                ranking[j + 1] = temp;
            }
        }
    }

    // Reescrever o ranking no arquivo
    fileRanking = fopen("../assets/ranking.txt", "w");
    if (fileRanking == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        free(ranking);
        return;
    }

    fprintf(fileRanking, "Tic Tac Toe - Ranking\n\n");

    for (int i = 0; i < tamanhoRanking; i++) {
        fprintf(fileRanking, "%d. %s - %d pontos\n", i + 1, ranking[i].nome, ranking[i].pontos);
    }


    time_t horaAtual = time(NULL);
    struct tm *tempoLocal = localtime(&horaAtual);

    strftime(dataHora, sizeof(dataHora), "%d/%m/%Y %H:%M:%S", tempoLocal);

    fprintf(fileRanking, "\nUltima aualizacao em: %s UTC-3", dataHora);

    fclose(fileRanking);

    fclose(fileRanking);
    free(ranking);
}





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

    printf("\n\nPressione 'Enter' para voltar ao Menu principal.");
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
                iniciarJogo();
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
                printf("\nOpcao invalida, tente novamente.\n");
                break;
        }

    } while (opcao != 4);

    return;
}





