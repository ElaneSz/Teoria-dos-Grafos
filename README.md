# Implementação de Grafo com Dados da Flor Iris

Este projeto demonstra a criação e visualização de um grafo a partir de dados reais, utilizando **C** para o processamento e **Python** para a visualização.

O objetivo principal é representar as **150 observações** do famoso conjunto de dados da flor *Iris* como um grafo.  
- Cada flor é um **vértice**.  
- Uma **aresta** é criada entre dois vértices se a **distância euclidiana normalizada** entre eles for **menor ou igual a 0.3**.  

A visualização tridimensional do grafo é gerada para mostrar os agrupamentos naturais das três espécies de flores:  
- *Iris setosa*  
- *Iris versicolor*  
- *Iris virginica*  

---

## 📊 Fluxo do Projeto

1. **Criação dos Dados**  
   - O programa em **C** lê o arquivo `IrisDataset.csv`.  
   - Calcula a distância euclidiana entre todas as 150 flores.  
   - Normaliza esses valores.

2. **Construção do Grafo**  
   - Com base na distância normalizada, o programa gera uma **matriz de adjacências** (`grafo_adjacencias.csv`).  
   - Também exporta as **coordenadas 3D** de cada vértice (`coordenadas_vertices.csv`).  

3. **Visualização**  
   - Um script em **Python** lê os arquivos de saída.  
   - Plota o grafo em **3D** destacando os agrupamentos naturais.

---

## ▶️ Como Executar

Certifique-se de que os arquivos `main.c`, `IrisDataset.csv` e `visualizar_grafo.py` estão todos no mesmo diretório.

### 1. Executar o Programa em C

Compile e execute o programa em **C** para gerar a matriz de adjacências e as coordenadas dos vértices.

```bash
# Compila o código C e cria o executável 'main'
# A flag -lm é necessária para linkar a biblioteca de matemática
gcc main.c -o main -lm

# Executa o programa compilado
# Isso irá gerar os arquivos: grafo_adjacencias.csv e coordenadas_vertices.csv
./main

```

### 2. Executar o Script Python

Após o programa em C gerar os arquivos CSV, execute o script Python para criar a visualização do grafo.

Certifique-se de que as bibliotecas numpy, matplotlib e networkx estão instaladas no seu ambiente Python:

```bash
python -m pip install numpy matplotlib networkx

# Agora, execute o script:
python visualizar_grafo.py

```

🔹 Caso esteja em um ambiente como o Codespaces, o comando irá gerar um arquivo de imagem chamado visualizacao_grafo.png em vez de abrir uma janela pop-up. Você pode baixar este arquivo para visualizá-lo.

## 📂 Arquivos Gerados

- `grafo_adjacencias.csv` → matriz de adjacências do grafo.

- `coordenadas_vertices.csv` → coordenadas tridimensionais de cada vértice.

- `visualizacao_grafo.png` → imagem do grafo em 3D (quando rodado em ambiente sem suporte gráfico).

## ✅ Tecnologias Utilizadas

- **C** → processamento dos dados, cálculo das distâncias e construção do grafo.

- **Python** → leitura dos dados e visualização em 3D.

- **Bibliotecas**: `numpy`, `matplotlib`, `networkx`.
