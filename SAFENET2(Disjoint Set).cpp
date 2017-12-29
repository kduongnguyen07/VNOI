#include <iostream>
#include <cstring>
#include <stdio.h>
#include <algorithm>
#include <stack>
#include <vector>

using namespace std;

typedef long long ll;
#define rep(i, a, b) for (int i = a; i <= b; i++)

int n, m;
vector<int> adj[101010], active, root;
vector<bool> visit;
stack<int> st;

int getRoot(int p) {
     return (root[p] == p ? p : root[p] = getRoot(root[p]));
}

void joint(int p, int q) {
    root[getRoot(p)] = getRoot(q);
}

void Input() {
    ios::sync_with_stdio(0); cin.tie(0);
    //freopen("SAFENET2.INP", "r", stdin);
    cin >> n >> m;
    rep(i, 1, m) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

void Init() {
    root.assign(n + 1, 0); active.assign(n + 1, 0); visit.assign(n + 1, false);
    rep(i, 1, n) root[i] = i;
}

void dfs(int u) {
    visit[u] = true;
    st.push(u);
    vector<int>::iterator it;
    for(it = adj[u].begin(); it != adj[u].end(); it++) {
        if (visit[*it]) {
             int v = getRoot(active[*it]);
             while(st.top() != v) {
                joint(st.top(), v);
                st.pop();
             }
        }
    }
    for(it = adj[u].begin(); it != adj[u].end(); it++) {
        if (!visit[*it]) {
            active[u] = *it;
            dfs(*it);
        }
    }

    if (st.top() == u) st.pop();
}

void Compute() {
    if(m < 1) {
        cout << 1; return;
    }
    vector<int> dem(n + 1, 0);
    rep(i, 1, n) if(!visit[i]) dfs(i);
    rep(i, 1, n) dem[getRoot(i)]++;
    cout << 1 + *max_element(dem.begin(), dem.end());
}

int main() {
    Input();
    Init();
    Compute();
    return 0;
}
