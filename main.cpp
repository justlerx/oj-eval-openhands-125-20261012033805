#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <unordered_map>

using namespace std;

// Simple Union-Find with path compression
struct UnionFind {
    vector<int> parent;
    vector<int> rank;
    
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        // Simple path compression
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void unite(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        
        if (rx == ry) return;
        
        // Union by rank
        if (rank[rx] < rank[ry]) {
            parent[rx] = ry;
        } else if (rank[rx] > rank[ry]) {
            parent[ry] = rx;
        } else {
            parent[ry] = rx;
            rank[rx]++;
        }
    }
    
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

int main() {
    // Use faster I/O
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    scanf("%d", &t);
    
    while (t--) {
        int n;
        scanf("%d", &n);
        
        // Vectors to store variables and constraints
        vector<int> vars;
        vector<tuple<int, int, int>> constraints;
        
        // Read all constraints and collect variables
        for (int i = 0; i < n; i++) {
            int x, y, e;
            scanf("%d %d %d", &x, &y, &e);
            vars.push_back(x);
            vars.push_back(y);
            constraints.emplace_back(x, y, e);
        }
        
        // Coordinate compression
        sort(vars.begin(), vars.end());
        vars.erase(unique(vars.begin(), vars.end()), vars.end());
        
        // Create mapping from variable to compressed index
        unordered_map<int, int> comp;
        for (int i = 0; i < vars.size(); i++) {
            comp[vars[i]] = i;
        }
        
        // Create UnionFind structure
        UnionFind uf(vars.size());
        bool possible = true;
        
        // Process equality constraints (e = 1)
        for (const auto& [x, y, e] : constraints) {
            if (e == 1) {
                uf.unite(comp[x], comp[y]);
            }
        }
        
        // Check inequality constraints (e = 0)
        for (const auto& [x, y, e] : constraints) {
            if (e == 0) {
                if (uf.connected(comp[x], comp[y])) {
                    possible = false;
                    break;
                }
            }
        }
        
        printf(possible ? "YES\n" : "NO\n");
    }
    
    return 0;
}