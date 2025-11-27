import sys
from gurobipy import Model, GRB

def resolver():
    dados = sys.stdin.read().split()
    it = iter(dados)

    n = int(next(it))
    m = int(next(it))
    s = int(next(it))
    t = int(next(it))

    origem = []
    destino = []
    peso = []

    min_v = s
    max_v = s
    if t < min_v: min_v = t
    if t > max_v: max_v = t

    for _ in range(m):
        u = int(next(it)); v = int(next(it)); w = float(next(it))
        origem.append(u); destino.append(v); peso.append(w)
        if u < min_v: min_v = u
        if v < min_v: min_v = v
        if u > max_v: max_v = u
        if v > max_v: max_v = v

    modelo = Model()
    modelo.Params.OutputFlag = 0
    modelo.Params.LogToConsole = 0

    dist = {}
    for v in range(min_v, max_v + 1):
        dist[v] = modelo.addVar(lb=-GRB.INFINITY, ub=GRB.INFINITY)

    modelo.setObjective(dist[t], GRB.MAXIMIZE)
    modelo.addConstr(dist[s] == 0)

    for i in range(m):
        u = origem[i]; v = destino[i]; w = peso[i]
        modelo.addConstr(dist[v] - dist[u] <= w)
        modelo.addConstr(dist[u] - dist[v] <= w)

    modelo.optimize()

    if modelo.Status == GRB.OPTIMAL:
        val = dist[t].X
        if abs(val - round(val)) < 5e-4:
            print(int(round(val)))
        else:
            print("{:.3f}".format(val))
    else:
        print("INF")

if __name__ == "__main__":
    resolver()
