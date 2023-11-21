#include <stdio.h>
#include <stdlib.h>

#define MAX_L 100
#define MAX_C 100

int tabuleiro[MAX_L][MAX_C];

// Função para verificar se uma posição é válida para colocar uma peça branca
int isValid(int L, int C, int i, int j) {
    // Verifica se a posição está dentro dos limites do tabuleiro
    if (i >= 0 && i < L && j >= 0 && j < C) {
        // Verifica se não há peça branca nas posições vizinhas
        if ((i > 0 && tabuleiro[i - 1][j] == 2) ||
            (j > 0 && tabuleiro[i][j - 1] == 2) ||
            (i < L - 1 && tabuleiro[i + 1][j] == 2) ||
            (j < C - 1 && tabuleiro[i][j + 1] == 2)) {
            return 0; // Não é válido
        }
        return 1; // É válido
    }
    return 0; // Não é válido (fora dos limites)
}

// Função recursiva para encontrar o máximo de peças brancas
int placeWhite(int L, int C, int i, int j) {
    // Verifica se a posição está dentro dos limites do tabuleiro
    if (i >= 0 && i < L && j >= 0 && j < C) {
        // Verifica se a posição está vazia e é válida para colocar uma peça branca
        if (tabuleiro[i][j] == 0 && isValid(L, C, i, j)) {
            // Coloca uma peça branca na posição
            tabuleiro[i][j] = 2;

            // Tenta colocar peças brancas nas posições vizinhas
            int total = 1 +
                        placeWhite(L, C, i - 1, j) +
                        placeWhite(L, C, i + 1, j) +
                        placeWhite(L, C, i, j - 1) +
                        placeWhite(L, C, i, j + 1);

            // Remove a peça branca se a tentativa não for bem-sucedida
            if (total == 1) {
                tabuleiro[i][j] = 0;
            }

            return total;
        }
    }
    return 0; // Posição inválida
}

int main() {
    int L, C, P, Xi, Yi;

    // Leitura da entrada
    scanf("%d %d", &L, &C);
    scanf("%d", &P);

    // Inicializa o tabuleiro com zeros
    for (int i = 0; i < L; ++i) {
        for (int j = 0; j < C; ++j) {
            tabuleiro[i][j] = 0;
        }
    }

    // Marcação das peças pretas no tabuleiro
    for (int i = 0; i < P; ++i) {
        scanf("%d %d", &Xi, &Yi);
        tabuleiro[Xi - 1][Yi - 1] = 1; // Marca a posição da peça preta no tabuleiro
    }

    // Tenta colocar peças brancas em todas as posições
    int maxWhites = 0;
    for (int i = 0; i < L; ++i) {
        for (int j = 0; j < C; ++j) {
            if (tabuleiro[i][j] == 0) {
                int whites = placeWhite(L, C, i, j);
                if (whites > maxWhites) {
                    maxWhites = whites;
                }
            }
        }
    }

    // Exibe o resultado
    printf("%d\n", maxWhites);

    return 0;
}
