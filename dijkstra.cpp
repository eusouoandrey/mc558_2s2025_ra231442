#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int totalVertices, totalArestas;
    int origem, destino;
    cin >> totalVertices >> totalArestas >> origem >> destino;

    vector<vector<pair<int,double>>> grafo(totalVertices);

    for (int i = 0; i < totalArestas; i++) {
        int u, v;
        double peso;
        cin >> u >> v >> peso;
        grafo[u].push_back({v, peso});
        grafo[v].push_back({u, peso});
    }

    const double INF = numeric_limits<double>::infinity();
    vector<double> distancia(totalVertices, INF);
    vector<char> visitado(totalVertices, 0);

    priority_queue<pair<double,int>, vector<pair<double,int>>, greater<pair<double,int>>> fila;

    distancia[origem] = 0.0;
    fila.push({0.0, origem});

    while (!fila.empty()) {
        double distAtual = fila.top().first;
        int verticeAtual = fila.top().second;
        fila.pop();

        if (distAtual > distancia[verticeAtual]) continue;
        if (visitado[verticeAtual]) continue;

        visitado[verticeAtual] = 1;
        if (verticeAtual == destino) break;

        for (auto &par : grafo[verticeAtual]) {
            int vizinho = par.first;
            double peso = par.second;
            double novaDist = distAtual + peso;

            if (novaDist < distancia[vizinho]) {
                distancia[vizinho] = novaDist;
                fila.push({novaDist, vizinho});
            }
        }
    }

    if (distancia[destino] == INF) {
        cout << "INF\n";
    } else {
        cout.setf(std::ios::fixed);
        cout << setprecision(3) << distancia[destino] << "\n";
    }

    return 0;
}
