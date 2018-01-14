#include <iostream>
#include <bitset>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstring>
using namespace std;

#define rep(i, a, b) for (int i = a; i <= b; i++)
typedef bitset<10101> bits;
int n, m, u, v;
vector<int> edge[10101];
vector<bits> adj(10101);

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m; 
    while(m--) {
        cin >> u >> v;
        if (!adj[u].test(v)) {
            edge[u].push_back(v); edge[v].push_back(u);
            adj[u].set(v, 1); adj[v].set(u, 1);
        }    
    }
    rep(i, 1, n) {
        bits pre_vertices;
        vector<int>::iterator it;
        for (it = edge[i].begin(); it != edge[i].end(); it++) {
            adj[*it][i] = false;
            if ((pre_vertices & adj[*it]).any()) {
                pre_vertices &= adj[*it];
                int w = 1; while(!pre_vertices[w]) w++;
                vector<int>::iterator p;
                for (p = edge[w].begin(); p != edge[w].end(); p++) {
                    if (adj[i][*p]) {
                        cout << i << " " << *it << " " << w << " " << *p;
                        return 0;
                    }
                }
            } else pre_vertices |= adj[*it];
            adj[*it][i] = true;
        }
    }
    cout << -1;
    return 0;
}
