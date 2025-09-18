#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_VERTICES 150
#define NOME_ARQUIVO "IrisDataset.csv"

// Estrutura para armazenar os dados de uma observação de flor
typedef struct {
    double comprimento_sepala;
    double largura_sepala;
    double comprimento_petala;
    double largura_petala;
} DadosIris;

// Protótipos das funções
void carregar_dados(DadosIris *dados, const char *nome_arquivo);
double calcular_distancia_euclidiana(DadosIris v1, DadosIris v2);
void calcular_todas_distancias_euclidianas(DadosIris *dados, double matriz_de[NUM_VERTICES][NUM_VERTICES]);
void normalizar_distancias(double matriz_de[NUM_VERTICES][NUM_VERTICES], double matriz_den[NUM_VERTICES][NUM_VERTICES]);
void construir_grafo(double matriz_den[NUM_VERTICES][NUM_VERTICES], int matriz_adj[NUM_VERTICES][NUM_VERTICES]);
void imprimir_matriz_adjacencias(int matriz_adj[NUM_VERTICES][NUM_VERTICES]);

int main() {
    DadosIris dados_iris[NUM_VERTICES];
    double matriz_de[NUM_VERTICES][NUM_VERTICES];
    double matriz_den[NUM_VERTICES][NUM_VERTICES];
    int matriz_adjacencias[NUM_VERTICES][NUM_VERTICES];

    // Passo 1: Carregar os dados do CSV
    carregar_dados(dados_iris, NOME_ARQUIVO);

    // Passo 2: Calcular todas as distâncias euclidianas
    calcular_todas_distancias_euclidianas(dados_iris, matriz_de);

    // Passo 3: Normalizar as distâncias
    normalizar_distancias(matriz_de, matriz_den);

    // Passo 4: Construir a matriz de adjacências com o limiar de 0.3
    construir_grafo(matriz_den, matriz_adjacencias);

    // Opcional: Imprimir a matriz para verificar (apenas uma seção para não sobrecarregar)
    printf("Matriz de Adjacências (seção 10x10 inicial):\n");
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            printf("%d ", matriz_adjacencias[i][j]);
        }
        printf("\n");
    }

    salvar_matriz_adj(matriz_adjacencias, "grafo_adjacencias.csv");

    return 0;
}

// Implementações das funções (mesmas que as mostradas acima)

void carregar_dados(DadosIris *dados, const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }
    char linha[256];
    fgets(linha, sizeof(linha), arquivo); // Pula o cabeçalho

    int i = 0;
    while (fgets(linha, sizeof(linha), arquivo) && i < NUM_VERTICES) {
        sscanf(linha, "%*[^,],%lf,%lf,%lf,%lf",
               &dados[i].comprimento_sepala,
               &dados[i].largura_sepala,
               &dados[i].comprimento_petala,
               &dados[i].largura_petala);
        i++;
    }
    fclose(arquivo);
}

double calcular_distancia_euclidiana(DadosIris v1, DadosIris v2) {
    return sqrt(
        pow(v1.comprimento_sepala - v2.comprimento_sepala, 2) +
        pow(v1.largura_sepala - v2.largura_sepala, 2) +
        pow(v1.comprimento_petala - v2.comprimento_petala, 2) +
        pow(v1.largura_petala - v2.largura_petala, 2)
    );
}

void calcular_todas_distancias_euclidianas(DadosIris *dados, double matriz_de[NUM_VERTICES][NUM_VERTICES]) {
    for (int i = 0; i < NUM_VERTICES; i++) {
        for (int j = i; j < NUM_VERTICES; j++) {
            double dist = calcular_distancia_euclidiana(dados[i], dados[j]);
            matriz_de[i][j] = dist;
            matriz_de[j][i] = dist;
        }
    }
}

void normalizar_distancias(double matriz_de[NUM_VERTICES][NUM_VERTICES], double matriz_den[NUM_VERTICES][NUM_VERTICES]) {
    double min_dist = INFINITY;
    double max_dist = 0.0;

    for (int i = 0; i < NUM_VERTICES; i++) {
        for (int j = 0; j < NUM_VERTICES; j++) {
            if (i != j) {
                if (matriz_de[i][j] < min_dist) min_dist = matriz_de[i][j];
                if (matriz_de[i][j] > max_dist) max_dist = matriz_de[i][j];
            }
        }
    }

    double alcance = max_dist - min_dist;
    for (int i = 0; i < NUM_VERTICES; i++) {
        for (int j = 0; j < NUM_VERTICES; j++) {
            if (i == j) {
                matriz_den[i][j] = 0.0;
            } else if (alcance > 0) {
                matriz_den[i][j] = (matriz_de[i][j] - min_dist) / alcance;
            } else {
                matriz_den[i][j] = 0.0;
            }
        }
    }
}

void construir_grafo(double matriz_den[NUM_VERTICES][NUM_VERTICES], int matriz_adj[NUM_VERTICES][NUM_VERTICES]) {
    for (int i = 0; i < NUM_VERTICES; i++) {
        for (int j = 0; j < NUM_VERTICES; j++) {
            if (i == j) {
                matriz_adj[i][j] = 0;
            } else if (matriz_den[i][j] <= 0.3) {
                matriz_adj[i][j] = 1;
            } else {
                matriz_adj[i][j] = 0;
            }
        }
    }
}

// Exemplo de função em C para salvar a matriz
void salvar_matriz_adj(int matriz_adj[NUM_VERTICES][NUM_VERTICES], const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "w");
    if (!arquivo) {
        perror("Erro ao salvar o arquivo");
        return;
    }

    for (int i = 0; i < NUM_VERTICES; i++) {
        for (int j = 0; j < NUM_VERTICES; j++) {
            fprintf(arquivo, "%d", matriz_adj[i][j]);
            if (j < NUM_VERTICES - 1) {
                fprintf(arquivo, ",");
            }
        }
        fprintf(arquivo, "\n");
    }
    fclose(arquivo);
}
