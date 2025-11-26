#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int totalVertices, totalArestas, verticeOrigem, verticeDestino;
    if (!(cin >> totalVertices >> totalArestas >> verticeOrigem >> verticeDestino)) return 0;

    vector<vector<pair<int,int>>> listaAdjacencia(totalVertices);
    int maiorPesoInteiro = 0;

    for (int i = 0; i < totalArestas; ++i) {
        int u, v;
        double pesoDouble;
        cin >> u >> v >> pesoDouble;
        int pesoInteiro = static_cast<int>(floor(pesoDouble + 0.5));
        listaAdjacencia[u].push_back({v, pesoInteiro});
        listaAdjacencia[v].push_back({u, pesoInteiro});
        if (pesoInteiro > maiorPesoInteiro) maiorPesoInteiro = pesoInteiro;
    }

    const long long VALOR_INFINITO = (long long)1e18;
    vector<long long> menorDistancia(totalVertices, VALOR_INFINITO);
    vector<char> visitado(totalVertices, 0);

    if (verticeOrigem < 0 || verticeOrigem >= totalVertices || verticeDestino < 0 || verticeDestino >= totalVertices) {
        cout << "INF\n";
        return 0;
    }

    menorDistancia[verticeOrigem] = 0;
    int numeroBaldes = maiorPesoInteiro + 1;
    if (numeroBaldes <= 0) numeroBaldes = 1;
    vector<vector<int>> baldes(numeroBaldes);

    baldes[0].push_back(verticeOrigem);
    long long elementosNosBaldes = 1;
    int indiceBalde = 0;
    long long distanciaAtual = 0;

    while (elementosNosBaldes > 0) {
        while (baldes[indiceBalde].empty()) {
            indiceBalde = (indiceBalde + 1) % numeroBaldes;
            distanciaAtual++;
        }

        int verticeAtual = baldes[indiceBalde].back();
        baldes[indiceBalde].pop_back();
        elementosNosBaldes--;

        if (menorDistancia[verticeAtual] != distanciaAtual) continue;
        if (visitado[verticeAtual]) continue;
        visitado[verticeAtual] = 1;
        if (verticeAtual == verticeDestino) break;

        for (auto &aresta : listaAdjacencia[verticeAtual]) {
            int vizinho = aresta.first;
            int pesoAresta = aresta.second;
            long long novaDistancia = menorDistancia[verticeAtual] + (long long)pesoAresta;
            if (novaDistancia < menorDistancia[vizinho]) {
                menorDistancia[vizinho] = novaDistancia;
                int indiceInsercao = static_cast<int>(novaDistancia % numeroBaldes);
                baldes[indiceInsercao].push_back(vizinho);
                elementosNosBaldes++;
            }
        }
    }

    if (menorDistancia[verticeDestino] == VALOR_INFINITO) {
        cout << "INF\n";
    } else {
        cout << menorDistancia[verticeDestino] << "\n";
    }

    return 0;
}
