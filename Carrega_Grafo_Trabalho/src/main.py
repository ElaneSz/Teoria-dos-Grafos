# Importa as bibliotecas necessárias
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import networkx as nx

# Função para plotar o grafo 3D
def plot_grafo_3d(matriz_adjacencias, coordenadas):
    """
    Plota um grafo em 3D.

    Args:
        matriz_adjacencias (np.ndarray): Matriz de adjacências do grafo.
        coordenadas (np.ndarray): Coordenadas 3D de cada vértice.
    """
    
    # Cria o objeto do grafo usando a matriz de adjacências
    G = nx.from_numpy_array(matriz_adjacencias)
    
    # Cria a figura e os eixos para o plot 3D
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    
    # Plota os vértices
    ax.scatter(coordenadas[:, 0], coordenadas[:, 1], coordenadas[:, 2], c='skyblue', s=100)
    
    # Plota as arestas
    for aresta in G.edges():
        ax.plot([coordenadas[aresta[0], 0], coordenadas[aresta[1], 0]],
                [coordenadas[aresta[0], 1], coordenadas[aresta[1], 1]],
                [coordenadas[aresta[0], 2], coordenadas[aresta[1], 2]],
                c='black', alpha=0.5)

    # Configura os rótulos dos eixos
    ax.set_xlabel('Comprimento da Sépala')
    ax.set_ylabel('Largura da Sépala')
    ax.set_zlabel('Comprimento da Pétala')

    # Título do plot
    plt.title("Visualização 3D do Grafo de Iris")
    
    # Exibe o plot
    plt.show()

if __name__ == "__main__":
    # Carregue a matriz de adjacências de um arquivo CSV (exemplo)
    # Supondo que 'grafo_adjacencias.csv' é gerado pelo seu código C
    matriz_adj = np.genfromtxt('grafo_adjacencias.csv', delimiter=',')
    
    # Carregue as coordenadas dos vértices de um arquivo CSV (exemplo)
    # Supondo que 'coordenadas_vertices.csv' é gerado pelo seu código C
    # Aqui estamos usando as 3 primeiras características da flor Iris como coordenadas (X, Y, Z) 
    coordenadas_iris = np.genfromtxt('coordenadas_vertices.csv', delimiter=',')
    
    # Chame a função de plotagem
    plot_grafo_3d(matriz_adj, coordenadas_iris)