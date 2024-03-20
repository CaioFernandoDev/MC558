#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge
{
    int origin, destiny, color;
};

vector<int> eulerianPath(vector<Edge> edges, int n)
{
    vector<int> degree(n, 0);
    vector<vector<int> > adj(n, vector<int>());
    vector<vector<int> > colors(n, vector<int>(n, -1));

    for (int i = 0; i < int(edges.size()); i++)
    {
        Edge edge = edges[i];
        degree[edge.origin]++;
        degree[edge.destiny]++;
        adj[edge.origin].push_back(edge.destiny);
        adj[edge.destiny].push_back(edge.origin);
        colors[edge.origin][edge.destiny] = edge.color;
        colors[edge.destiny][edge.origin] = edge.color;
    }

    for (int i = 0; i < n; i++)
    {
        if (degree[i] % 2 != 0)
        {
            return vector<int>();
        }
    }

    vector<int> stack;
    stack.push_back(0);
    vector<int> path;
    vector<int> lastColors;
    lastColors.push_back(-1);

    while (!stack.empty())
    {
        int v = stack.back();

        for (int i = 0; i < int(adj[v].size()); i++)
        {
            int u = adj[v][i];
            int color = colors[v][u];

            if (color != lastColors.back())
            {
                adj[v].erase(remove(adj[v].begin(), adj[v].end(), u), adj[v].end());
                adj[u].erase(remove(adj[u].begin(), adj[u].end(), v), adj[u].end());

                degree[v]--;
                degree[u]--;

                stack.push_back(u);
                lastColors.push_back(color);
                break;
            }
        }

        if (v == stack.back())
        {
            lastColors.pop_back();
            int vertice = stack.back();
            stack.pop_back();

            if (degree[vertice] % 2 != 0)
            {
                return vector<int>();
            }

            path.push_back(vertice);
        }
    }

    if (path.size() < edges.size() + 1)
    {
        return vector<int>();
    }

    return path;
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);

    for (int i = 0; i < m; i++)
    {
        int origin, destiny, color;
        cin >> origin >> destiny >> color;
        Edge edge = {origin, destiny, color};
        edges[i] = edge;
    }

    vector<int> path = eulerianPath(edges, n);

    if (path.size() == 0)
    {
        cout << "Não possui trilha Euleriana alternante" << endl;
    }
    else
    {
        for (int i = 0; i < int(path.size()); i++)
        {
            cout << path[i] << " ";
        }
    }

    return 0;
}