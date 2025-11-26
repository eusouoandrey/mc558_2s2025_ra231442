#include <bits/stdc++.h>
using namespace std;

struct Aresta { int destino; double peso; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int quantidadeVertices, quantidadeArestas, origem, destino;
    if (!(cin >> quantidadeVertices >> quantidadeArestas >> origem >> destino)) return 0;

    vector<vector<Aresta>> grafo(quantidadeVertices);
    for (int i = 0; i < quantidadeArestas; ++i) {
        int u, v;
        double w;
        cin >> u >> v >> w;
        grafo[u].push_back({v, w});
        grafo[v].push_back({u, w});
    }

    const double INFINITO = 1e18;
    vector<double> distanciaIda(quantidadeVertices, INFINITO);
    vector<double> distanciaVolta(quantidadeVertices, INFINITO);
    vector<char> visitadoIda(quantidadeVertices, 0);
    vector<char> visitadoVolta(quantidadeVertices, 0);

    if (origem < 0 || origem >= quantidadeVertices || destino < 0 || destino >= quantidadeVertices) {
        cout << "INF\n";
        return 0;
    }

    if (origem == destino) {
        cout << fixed << setprecision(3) << 0.0 << "\n";
        return 0;
    }

    distanciaIda[origem] = 0.0;
    distanciaVolta[destino] = 0.0;

    priority_queue<pair<double,int>, vector<pair<double,int>>, greater<pair<double,int>>> heapIda;
    priority_queue<pair<double,int>, vector<pair<double,int>>, greater<pair<double,int>>> heapVolta;

    heapIda.push({0.0, origem});
    heapVolta.push({0.0, destino});

    double melhor = INFINITO;
    const double EPS = 1e-12;

    while (!heapIda.empty() || !heapVolta.empty()) {
        double topoIda = heapIda.empty() ? INFINITO : heapIda.top().first;
        double topoVolta = heapVolta.empty() ? INFINITO : heapVolta.top().first;

        if (melhor < INFINITO && topoIda + topoVolta >= melhor) break;

        if (topoIda <= topoVolta) {
            auto p = heapIda.top();
            heapIda.pop();
            double d = p.first;
            int u = p.second;
            if (d > distanciaIda[u] + EPS) continue;
            if (visitadoIda[u]) continue;
            visitadoIda[u] = 1;

            if (distanciaVolta[u] < INFINITO) {
                double candidato = distanciaIda[u] + distanciaVolta[u];
                if (candidato < melhor) melhor = candidato;
            }

            for (auto &a : grafo[u]) {
                int v = a.destino;
                double nd = distanciaIda[u] + a.peso;
                if (nd + EPS < distanciaIda[v]) {
                    distanciaIda[v] = nd;
                    heapIda.push({nd, v});
                }
            }
        } else {
            auto p = heapVolta.top();
            heapVolta.pop();
            double d = p.first;
            int u = p.second;
            if (d > distanciaVolta[u] + EPS) continue;
            if (visitadoVolta[u]) continue;
            visitadoVolta[u] = 1;

            if (distanciaIda[u] < INFINITO) {
                double candidato = distanciaIda[u] + distanciaVolta[u];
                if (candidato < melhor) melhor = candidato;
            }

            for (auto &a : grafo[u]) {
                int v = a.destino;
                double nd = distanciaVolta[u] + a.peso;
                if (nd + EPS < distanciaVolta[v]) {
                    distanciaVolta[v] = nd;
                    heapVolta.push({nd, v});
                }
            }
        }
    }

    if (melhor >= INFINITO) cout << "INF\n";
    else cout << fixed << setprecision(3) << melhor << "\n";

    return 0;
}
