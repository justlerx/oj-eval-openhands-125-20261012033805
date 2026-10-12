#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cstdio>

using namespace std;

class UnionFind {
private:
    unordered_map<int, int> parent;
    unordered_map<int, int> rank;
    
public:
    int find(int x) {
        if (parent.find(x) == parent.end()) {
            parent[x] = x;
            rank[x] = 0;
            return x;
        }
        
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
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
    
    void clear() {
        parent.clear();
        rank.clear();
    }
};

int main() {
    // Use faster I/O
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    scanf("%d", &t);
    
    UnionFind uf;
    
    while (t--) {
        int n;
        scanf("%d", &n);
        
        // Clear the union-find structure for each test case
        uf.clear();
        
        // We'll store inequality constraints to check after processing equalities
        vector<pair<int, int>> inequalities;
        bool possible = true;
        
        // Process constraints
        for (int i = 0; i < n; i++) {
            int x, y, e;
            scanf("%d %d %d", &x, &y, &e);
            
            if (e == 1) { // equality constraint
                uf.unite(x, y);
            } else { // inequality constraint
                inequalities.push_back({x, y});
            }
        }
        
        // Check all inequality constraints
        for (auto& p : inequalities) {
            if (uf.connected(p.first, p.second)) {
                possible = false;
                break;
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