#include <bits/stdc++.h>
using namespace std;

/**
 * DP State Definition:
 * dp[u][0]: Max matching in subtree of u, where u is NOT matched with a child.
 * dp[u][1]: Max matching in subtree of u, where u IS matched with exactly one child.
 */

const int MAXN = 200005;
vector<int> adj[MAXN];
long long dp[MAXN][2];

void dfs(int u, int p) {
    long long sum_best_children = 0;
    
    // Step 1: Visit children first (Post-order)
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
        // If u is not matched, we just take the best from each child's subtree
        sum_best_children += max(dp[v][0], dp[v][1]);
    }
    
    // Step 2: Assign dp[u][0]
    dp[u][0] = sum_best_children;
    
    // Step 3: Compute dp[u][1] using the subtraction optimization
    // We want to pick one child 'v' to match with 'u'.
    // The matching increases by 1 (the edge u-v) + dp[v][0] (since v is now matched with u)
    // plus the best results from all OTHER children.
    dp[u][1] = -1e18; // Initialize with a very small number (negative infinity)
    
    for (int v : adj[u]) {
        if (v == p) continue;
        
        // Optimized formula: total - (best of v) + (u-v edge) + (v's result if v is free)
        long long current_option = sum_best_children - max(dp[v][0], dp[v][1]) + 1 + dp[v][0];
        dp[u][1] = max(dp[u][1], current_option);
    }
}

int main() {
    // Faster I/O for competitive programming
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    if (!(cin >> n)) return 0;
    
    // Edge case: A tree with 1 node has 0 matching
    if (n == 1) {
        cout << 0 << endl;
        return 0;
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Start DFS from root (node 1)
    dfs(1, 0);

    // The answer is the best of either matching the root or not
    cout << max(dp[1][0], dp[1][1]) << endl;

    return 0;
}