#include <bits/stdc++.h>
using namespace std;

using ll = long long;

vector<ll> dialUnico(int totalVertices, vector<vector<pair<int,int>>> &listaAdjacencia, int origem, int maiorPeso) {
    const ll INF = (1LL<<60);
    int numBaldes = max(1, maiorPeso + 1);
    vector<vector<int>> baldes(numBaldes);
    vector<ll> distancia(totalVertices, INF);
    vector<char> visitado(totalVertices, 0);

    distancia[origem] = 0;
    baldes[0].push_back(origem);
    ll contador = 1;
    int indice = 0;
    ll distanciaAtual = 0;

    while (contador > 0) {
        while (contador > 0 && baldes[indice].empty()) {
            indice = (indice + 1) % numBaldes;
            distanciaAtual++;
        }
        if (baldes[indice].empty()) break;
        int u = baldes[indice].back();
        baldes[indice].pop_back();
        contador--;
        if (visitado[u]) continue;
        if (distancia[u] != distanciaAtual) continue;
        visitado[u] = 1;
        for (auto &e : listaAdjacencia[u]) {
            int v = e.first;
            int w = e.second;
            ll nd = distancia[u] + (ll)w;
            if (nd < distancia[v]) {
                distancia[v] = nd;
                int pos = (int)(nd % numBaldes);
                baldes[pos].push_back(v);
                contador++;
            }
        }
    }
    return distancia;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, s, d;
    if (!(cin >> n >> m >> s >> d)) return 0;

    vector<vector<pair<int,int>>> grafo(n);
    int maiorPeso = 0;

    for (int i = 0; i < m; ++i) {
        int u, v;
        double w;
        cin >> u >> v >> w;
        int p = (int)llround(w);
        grafo[u].push_back({v, p});
        grafo[v].push_back({u, p});
        if (p > maiorPeso) maiorPeso = p;
    }

    if (s < 0 || s >= n || d < 0 || d >= n) {
        cout << "INF\n";
        return 0;
    }
    if (s == d) {
        cout << 0 << "\n";
        return 0;
    }

    vector<ll> distS = dialUnico(n, grafo, s, maiorPeso);
    vector<ll> distD = dialUnico(n, grafo, d, maiorPeso);

    const ll INF = (1LL<<60);
    ll melhor = INF;
    for (int i = 0; i < n; ++i) {
        if (distS[i] < INF && distD[i] < INF) {
            ll soma = distS[i] + distD[i];
            if (soma < melhor) melhor = soma;
        }
    }

    if (melhor >= INF) cout << "INF\n";
    else cout << melhor << "\n";

    return 0;
}
