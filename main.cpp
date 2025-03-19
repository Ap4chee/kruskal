#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v;
    double probability;
};

bool comparator(const Edge &a, const Edge &b) {
    return a.probability > b.probability;
}

vector<int> parent, rankSet;

int find(int v) {
    if (parent[v] != v) {
        parent[v] = find(parent[v]);
    }
    return parent[v];
}

void unite(int a, int b) {
    int rootA = find(a);
    int rootB = find(b);
    if (rootA != rootB) {
        if (rankSet[rootA] < rankSet[rootB]) {
            parent[rootA] = rootB;
        } else if (rankSet[rootA] > rankSet[rootB]) {
            parent[rootB] = rootA;
        } else {
            parent[rootB] = rootA;
            rankSet[rootA]++;
        }
    }
}

double kruskal(int n, vector<Edge>& edges) {
    double toReturn = 1;
    parent.resize(n);
    rankSet.resize(n, 0);
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    for (auto edge : edges) {
        if (find(edge.u) != find(edge.v)) {
            unite(edge.u, edge.v);
            toReturn *= edge.probability;
        }
    }

    return toReturn;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<Edge> edges(m);

    for (int i = 0; i < m; i++) {
        int u, v;
        double x;
        cin >> u >> v >> x;
        edges[i] = {u, v, x};
    }

    sort(edges.begin(), edges.end(), comparator);

    cout << fixed << setprecision(5) << kruskal(n, edges) << endl;

    return 0;
}
