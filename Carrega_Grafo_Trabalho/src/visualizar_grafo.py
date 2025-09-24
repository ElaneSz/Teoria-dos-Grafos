import matplotlib as mpl
mpl.use('Agg')  # Usa backend que não abre janela, bom para servidores

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import networkx as nx
import pandas as pd

def plot_grafo_3d(matriz_adjacencias, coordenadas, especies, output="visualizacao_grafo.png"):
    """
    Plota um grafo em 3D com coloração por espécie.

    Args:
        matriz_adjacencias (np.ndarray): Matriz de adjacências do grafo.
        coordenadas (np.ndarray): Coordenadas 3D de cada vértice.
        especies (np.ndarray): Vetor com a espécie de cada vértice (0, 1, 2).
        output (str): Nome do arquivo de saída da figura.
    """
    # Cria o grafo a partir da matriz de adjacências
    G = nx.from_numpy_array(matriz_adjacencias)

    # Cria figura
    fig = plt.figure(figsize=(10, 8))
    ax = fig.add_subplot(111, projection='3d')

    # Define cores para as espécies
    cores = {0: "red", 1: "green", 2: "blue"}
    nomes = {0: "Setosa", 1: "Versicolor", 2: "Virginica"}

    # Plota os vértices por espécie
    for especie in np.unique(especies):
        idx = np.where(especies == especie)[0]
        ax.scatter(coordenadas[idx, 0], coordenadas[idx, 1], coordenadas[idx, 2],
                   c=cores[especie], s=40, edgecolors='k', alpha=0.8, label=nomes[especie])

    # Plota as arestas
    for aresta in G.edges():
        ax.plot([coordenadas[aresta[0], 0], coordenadas[aresta[1], 0]],
                [coordenadas[aresta[0], 1], coordenadas[aresta[1], 1]],
                [coordenadas[aresta[0], 2], coordenadas[aresta[1], 2]],
                c='gray', alpha=0.3)

    # Configura eixos
    ax.set_xlabel('Comprimento da Sépala')
    ax.set_ylabel('Largura da Sépala')
    ax.set_zlabel('Comprimento da Pétala')
    ax.set_title("Visualização 3D do Grafo de Iris")

    # Legenda
    ax.legend()

    # Ângulo da câmera
    ax.view_init(elev=20, azim=30)

    # Salva a imagem
    plt.savefig(output, dpi=300)
    plt.close()
    print(f"Grafo salvo em {output}")

if __name__ == "__main__":
    # Carrega a matriz de adjacências
    matriz_adj = np.genfromtxt('grafo_adjacencias.csv', delimiter=',')

    # Carrega as coordenadas
    coordenadas = np.genfromtxt('coordenadas_vertices.csv', delimiter=',')

    # Carrega o dataset original para identificar espécies
    iris_dataset = pd.read_csv('IrisDataset.csv')

    # Mapeia espécies para valores numéricos
    mapa_especies = {"Setosa": 0, "Versicolor": 1, "Virginica": 2}
    especies = iris_dataset["variety"].map(mapa_especies).values

    # Gera o gráfico
    plot_grafo_3d(matriz_adj, coordenadas, especies, output="../img/visualizacao_grafo.png")
