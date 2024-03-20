class Aresta:
    def __init__(self, origem, destino, cor):
        self.origem = origem
        self.destino = destino
        self.cor = cor


def obterCaminhos(adj, cores, caminhos, s, t, ultimaCor):
    # checando se esse valor já foi calculado anteriormente
    if caminhos[s][t][1] == ultimaCor and caminhos[s][t][0] != -1:
        return caminhos[s][t][0]

    # inicializando o número de caminhos
    caminhosArestaVerde = 0
    caminhosArestaVermelha = 0

    # se o vértice atual for o destino, então existe um caminho
    if s == t:
        return 1

    for v in adj[s]:
        if v == t:
            # se chegou no destino, então existe um caminho
            if ultimaCor == -1 or ultimaCor == 0:
                caminhosArestaVerde += 1
            elif ultimaCor == 1 and cores[s][v] == 0:
                caminhosArestaVermelha += 1
        else:
            if ultimaCor == -1 or ultimaCor == 0:
                # pode ter aresta de qualquer cor
                if cores[s][v] == 0:
                    caminhosArestaVerde += obterCaminhos(adj, cores, caminhos, v, t, 0)
                elif cores[s][v] == 1:
                    caminhosArestaVermelha += obterCaminhos(
                        adj, cores, caminhos, v, t, 1
                    )
            elif ultimaCor == 1:
                # só pode ter aresta verde
                if cores[s][v] == 0:
                    caminhosArestaVerde += obterCaminhos(adj, cores, caminhos, v, t, 0)

    # armazenando o resultado dos caminhos em uma tupla
    caminhos[s][t] = (caminhosArestaVerde + caminhosArestaVermelha, ultimaCor)

    return caminhos[s][t][0]


def obterCaminhosViaveis(arestas, n, m, s, t):
    adj = [[] for i in range(n)]  # lista de adjacências
    # matriz para armazenar a cor de cada aresta
    cores = [[-1 for j in range(n)] for i in range(n)]
    # matriz para armazenar os caminhos já calculados
    caminhos = [[(-1, -1) for j in range(n)] for i in range(n)]

    # preenchendo a lista de adjacências e a matriz de cores
    for aresta in arestas:
        adj[aresta.origem].append(aresta.destino)
        cores[aresta.origem][aresta.destino] = aresta.cor

    return obterCaminhos(adj, cores, caminhos, s, t, -1)


def main():
    arestas = []
    n, m, s, t = map(int, input().split())

    for i in range(m):
        x, y, c = map(int, input().split())
        arestas.append(Aresta(x, y, c))

    print(obterCaminhosViaveis(arestas, n, m, s, t))


main()
