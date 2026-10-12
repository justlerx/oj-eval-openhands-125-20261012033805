#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

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
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        vector<pair<pair<int, int>, int>> constraints;
        
        for (int i = 0; i < n; i++) {
            int x, y, e;
            cin >> x >> y >> e;
            constraints.push_back({{x, y}, e});
        }
        
        UnionFind uf;
        bool possible = true;
        
        // First pass: process all equality constraints
        for (auto& constraint : constraints) {
            int x = constraint.first.first;
            int y = constraint.first.second;
            int e = constraint.second;
            
            if (e == 1) { // equality constraint
                uf.unite(x, y);
            }
        }
        
        // Second pass: check all inequality constraints
        for (auto& constraint : constraints) {
            int x = constraint.first.first;
            int y = constraint.first.second;
            int e = constraint.second;
            
            if (e == 0) { // inequality constraint
                if (uf.connected(x, y)) {
                    possible = false;
                    break;
                }
            }
        }
        
        if (possible) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    
    return 0;
}