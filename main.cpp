#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <unordered_map>

using namespace std;

class UnionFind {
private:
    vector<int> parent;
    vector<int> rank;
    
public:
    UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        while (parent[x] != x) {
            parent[x] = parent[parent[x]]; // Path compression by halving
            x = parent[x];
        }
        return x;
    }
    
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX == rootY) return;
        
        // Union by rank
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
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
        
        vector<int> variables;
        vector<tuple<int, int, int>> constraints;
        
        // Read all constraints and collect all variable indices
        for (int i = 0; i < n; i++) {
            int x, y, e;
            scanf("%d %d %d", &x, &y, &e);
            variables.push_back(x);
            variables.push_back(y);
            constraints.emplace_back(x, y, e);
        }
        
        // Coordinate compression
        sort(variables.begin(), variables.end());
        auto last = unique(variables.begin(), variables.end());
        variables.erase(last, variables.end());
        
        // Create a mapping from original variable to compressed index
        unordered_map<int, int> comp;
        for (int i = 0; i < variables.size(); i++) {
            comp[variables[i]] = i;
        }
        
        // Create UnionFind with compressed indices
        UnionFind uf(variables.size());
        bool possible = true;
        
        // Process equality constraints
        for (auto& [x, y, e] : constraints) {
            if (e == 1) {
                uf.unite(comp[x], comp[y]);
            }
        }
        
        // Check inequality constraints
        for (auto& [x, y, e] : constraints) {
            if (e == 0) {
                if (uf.connected(comp[x], comp[y])) {
                    possible = false;
                    break;
                }
            }
        }
        
        if (possible) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    
    return 0;
}