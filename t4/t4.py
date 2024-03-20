class Edge:
    def __init__(self, a, b, w):
        self.a = a
        self.b = b
        self.w = w


class Graph:
    def __init__(self, vertices):
        self.V = vertices
        self.graph = []

    def addEdge(self, edge):
        self.graph.append(edge)

    def find(self, parent, i):
        if parent[i] == i:
            return i

        return self.find(parent, parent[i])

    def union(self, parent, rank, x, y):
        if rank[x] < rank[y]:
            parent[x] = y
        elif rank[x] > rank[y]:
            parent[y] = x
        else:
            parent[y] = x
            rank[x] += 1

    def KruskalMST(self, k):
        result = []
        i_sorted = 0
        i_result = 0

        self.graph = sorted(self.graph, key=lambda item: item.w)

        parent = []
        rank = []

        for node in range(self.V):
            parent.append(node)
            rank.append(0)

        while i_result < self.V - k:
            a = self.graph[i_sorted].a
            b = self.graph[i_sorted].b
            w = self.graph[i_sorted].w
            i_sorted += 1

            x = self.find(parent, a)
            y = self.find(parent, b)

            if x != y:
                i_result += 1
                result.append(Edge(a, b, w))
                self.union(parent, rank, x, y)

        minimumCost = 0
        for edge in result:
            minimumCost += edge.w

        print(minimumCost)


def main():
    n, m, k = map(int, input().split())
    graph = Graph(n)

    for i in range(m):
        a, b, w = map(int, input().split())
        graph.addEdge(Edge(a, b, w))

    graph.KruskalMST(k)


main()
