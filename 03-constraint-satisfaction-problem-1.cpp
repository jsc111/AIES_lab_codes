#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

bool isSafe(int node, vector<int> &colors, vector<vector<int>> &graph, int color) {
    for (int neighbor : graph[node]) {
        if (colors[neighbor] == color) {
            return false;
        }
    }
    return true;
}

bool solveMapColoring(vector<vector<int>> &graph, int m, vector<int> &colors, int node) {
    if (node == graph.size()) {
        return true;
    }

    for (int color = 1; color <= m; color++) {
        if (isSafe(node, colors, graph, color)) {
            colors[node] = color;
            if (solveMapColoring(graph, m, colors, node + 1)) {
                return true;
            }
            colors[node] = 0;
        }
    }
    return false;
}

int main() {
    int n = 4; // Number of regions/nodes
    vector<vector<int>> graph = {
        {1, 2, 3},
        {0, 2},
        {0, 1, 3},
        {0, 2}
    };

    int m = 3; // Number of colors
    vector<int> colors(n, 0);

    if (solveMapColoring(graph, m, colors, 0)) {
        cout << "Solution exists with the following color assignment:\n";
        for (int i = 0; i < n; i++) {
            cout << "Region " << i << " -> Color " << colors[i] << endl;
        }
    } else {
        cout << "No solution exists.\n";
    }

    return 0;
}
