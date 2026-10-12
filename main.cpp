#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

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

// Binary search to find the compressed index
int compress(const vector<int>& sorted_vars, int val) {
    int left = 0, right = sorted_vars.size() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (sorted_vars[mid] == val) {
            return mid;
        } else if (sorted_vars[mid] < val) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1; // Should never happen
}

int main() {
    // Use faster I/O
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    scanf("%d", &t);
    
    while (t--) {
        int n;
        scanf("%d", &n);
        
        vector<pair<int, int>> equalities;
        vector<pair<int, int>> inequalities;
        vector<int> variables;
        
        // Read all constraints and collect all variable indices
        for (int i = 0; i < n; i++) {
            int x, y, e;
            scanf("%d %d %d", &x, &y, &e);
            variables.push_back(x);
            variables.push_back(y);
            
            if (e == 1) {
                equalities.emplace_back(x, y);
            } else {
                inequalities.emplace_back(x, y);
            }
        }
        
        // Coordinate compression
        sort(variables.begin(), variables.end());
        auto last = unique(variables.begin(), variables.end());
        variables.erase(last, variables.end());
        
        // Create UnionFind with compressed indices
        UnionFind uf(variables.size());
        bool possible = true;
        
        // Process equality constraints
        for (auto& [x, y] : equalities) {
            int cx = compress(variables, x);
            int cy = compress(variables, y);
            uf.unite(cx, cy);
        }
        
        // Check inequality constraints
        for (auto& [x, y] : inequalities) {
            int cx = compress(variables, x);
            int cy = compress(variables, y);
            if (uf.connected(cx, cy)) {
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