class UnionFind:
    def __init__(self, n):
        self.parent = [i for i in range(n)]
        self.rank = [0] * n

    def find(self, u):
        if self.parent[u] != u:
            self.parent[u] = self.find(self.parent[u])
        return self.parent[u]

    def union(self, u, v):
        root_u = self.find(u)
        root_v = self.find(v)

        if root_u != root_v:
            if self.rank[root_u] < self.rank[root_v]:
                self.parent[root_u] = root_v
            elif self.rank[root_u] > self.rank[root_v]:
                self.parent[root_v] = root_u
            else:
                self.parent[root_u] = root_v
                self.rank[root_v] += 1


def kruskal(num_vertices, edges):
    edges.sort(key=lambda x: x[2])
    uf = UnionFind(num_vertices)
    total_weight = 0

    for edge in edges:
        u, v, weight = edge
        if uf.find(u) != uf.find(v):
            uf.union(u, v)
            total_weight += weight

    return total_weight


# Exemplo de uso com a entrada fornecida
if __name__ == "__main__":
    input_data = [(0, 1, 3), (1, 2, 5), (0, 2, 6), (3, 4, 6), (0, 3, 8), (1, 3, 10)]

    num_vertices = 5
    result = kruskal(num_vertices, input_data)

    print("Peso da árvore geradora mínima:", result)
