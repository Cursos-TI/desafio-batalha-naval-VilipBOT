#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define TAMANHO_HABILIDADE 5 // Define o tamanho das matrizes de habilidade

// Funções do nível anterior
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

int posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linhaInicial, int colunaInicial, char orientacao) {
    if (linhaInicial < 0 || linhaInicial >= TAMANHO_TABULEIRO || colunaInicial < 0 || colunaInicial >= TAMANHO_TABULEIRO) {
        printf("Coordenadas de início inválidas.\n");
        return 0;
    }

    if (orientacao == 'h') {
        if (colunaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
            printf("Navio excede os limites do tabuleiro horizontalmente.\n");
            return 0;
        }
    } else if (orientacao == 'v') {
        if (linhaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
            printf("Navio excede os limites do tabuleiro verticalmente.\n");
            return 0;
        }
    } else if (orientacao == 'd') {
        if (linhaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO || colunaInicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
            printf("Navio excede os limites do tabuleiro na diagonal.\n");
            return 0;
        }
    } else {
        printf("Orientação inválida. Use 'h' (horizontal), 'v' (vertical) ou 'd' (diagonal).\n");
        return 0;
    }

    if (orientacao == 'h') {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linhaInicial][colunaInicial + i] != 0) {
                printf("Sobreposição de navios detectada.\n");
                return 0;
            }
        }
    } else if (orientacao == 'v') {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linhaInicial + i][colunaInicial] != 0) {
                printf("Sobreposição de navios detectada.\n");
                return 0;
            }
        }
    } else if (orientacao == 'd') {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linhaInicial + i][colunaInicial + i] != 0) {
                printf("Sobreposição de navios detectada.\n");
                return 0;
            }
        }
    }

    if (orientacao == 'h') {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linhaInicial][colunaInicial + i] = 3;
        }
    } else if (orientacao == 'v') {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linhaInicial + i][colunaInicial] = 3;
        }
    } else if (orientacao == 'd') {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linhaInicial + i][colunaInicial + i] = 3;
        }
    }

    return 1;
}

// Funções para as novas habilidades
void criarCone(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (j >= centro - i && j <= centro + i) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

void criarCruz(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (i == centro || j == centro) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

void criarOctaedro(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int distanciaLinha = (i > centro) ? i - centro : centro - i;
            int distanciaColuna = (j > centro) ? j - centro : centro - j;
            if (distanciaLinha + distanciaColuna <= centro) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

void sobreporHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], int linhaOrigem, int colunaOrigem) {
    int inicioLinha = linhaOrigem - TAMANHO_HABILIDADE / 2;
    int inicioColuna = colunaOrigem - TAMANHO_HABILIDADE / 2;

    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (habilidade[i][j] == 1) {
                int linhaAtual = inicioLinha + i;
                int colunaAtual = inicioColuna + j;
                if (linhaAtual >= 0 && linhaAtual < TAMANHO_TABULEIRO && colunaAtual >= 0 && colunaAtual < TAMANHO_TABULEIRO) {
                    if (tabuleiro[linhaAtual][colunaAtual] != 3) {
                        tabuleiro[linhaAtual][colunaAtual] = 5; // Marca a área afetada
                    }
                }
            }
        }
    }
}

// Exibe o tabuleiro com os novos caracteres
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("   ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%d ", j);
    }
    printf("\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d  ", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == 0) {
                printf("~ ");
            } else if (tabuleiro[i][j] == 3) {
                printf("3 ");
            } else if (tabuleiro[i][j] == 5) {
                printf("* ");
            }
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int habilidadeCone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidadeCruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidadeOctaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    inicializarTabuleiro(tabuleiro);

    // Posiciona os navios
    posicionarNavio(tabuleiro, 2, 3, 'h');
    posicionarNavio(tabuleiro, 5, 1, 'v');
    posicionarNavio(tabuleiro, 0, 6, 'd');
    posicionarNavio(tabuleiro, 7, 5, 'd');
    
    // Cria as matrizes de habilidade
    criarCone(habilidadeCone);
    criarCruz(habilidadeCruz);
    criarOctaedro(habilidadeOctaedro);

    // Exibe o tabuleiro com a habilidade Cone
    printf("Tabuleiro com Habilidade Cone (origem em 2, 2):\n");
    sobreporHabilidade(tabuleiro, habilidadeCone, 2, 2);
    exibirTabuleiro(tabuleiro);
    inicializarTabuleiro(tabuleiro); // Limpa o tabuleiro para a próxima demonstração

    // Posiciona os navios novamente
    posicionarNavio(tabuleiro, 2, 3, 'h');
    posicionarNavio(tabuleiro, 5, 1, 'v');
    posicionarNavio(tabuleiro, 0, 6, 'd');
    posicionarNavio(tabuleiro, 7, 5, 'd');

    // Exibe o tabuleiro com a habilidade Cruz
    printf("\nTabuleiro com Habilidade Cruz (origem em 5, 5):\n");
    sobreporHabilidade(tabuleiro, habilidadeCruz, 5, 5);
    exibirTabuleiro(tabuleiro);
    inicializarTabuleiro(tabuleiro); // Limpa o tabuleiro para a próxima demonstração

    // Posiciona os navios novamente
    posicionarNavio(tabuleiro, 2, 3, 'h');
    posicionarNavio(tabuleiro, 5, 1, 'v');
    posicionarNavio(tabuleiro, 0, 6, 'd');
    posicionarNavio(tabuleiro, 7, 5, 'd');

    // Exibe o tabuleiro com a habilidade Octaedro
    printf("\nTabuleiro com Habilidade Octaedro (origem em 8, 8):\n");
    sobreporHabilidade(tabuleiro, habilidadeOctaedro, 8, 8);
    exibirTabuleiro(tabuleiro);

    return 0;
}