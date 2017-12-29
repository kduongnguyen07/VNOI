#include <iostream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

typedef vector< vector<int> > vt2d;
typedef long long ll;
#define rep(i, a, b) for (int i = a; i <= b; i++)

int n, m, counter = 0;
vector<int> low, num, adj[101010];
vt2d component;
stack<int> st;

void Input() {
    //freopen("SAFENET2.INP", "r", stdin);
    cin >> n >> m;
    rep(i, 1, m) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v); adj[v].push_back(u);
    }
}

void Init() {
    low.assign(n + 1, 0); num.assign(n + 1, 0);
}

void visit(int u, bool isRoot) {
    num[u] = low[u] = ++counter;
    if(adj[u].empty()) {
        component.push_back(vector<int>(1, u)); return;
    }
    st.push(u);
    vector<int>::iterator it;
    for (it = adj[u].begin(); it != adj[u].end(); it++) {
        if(num[*it]) low[u] = min(low[u], num[*it]);
        else{
            visit(*it, 0);
            low[u] = min(low[u], low[*it]);
            if(isRoot || low[*it] >= num[u]) {
                component.push_back(vector<int>(1, u));
                while(1) {
                    int u = st.top(); st.pop();
                    component.back().push_back(u);
                    if (u == *it) break;
                }
            }
        }
    }
}

void Compute() {
    int ans = 0;
    rep(i, 1, n) if (!num[i]) visit(i, 1);
    rep(i, 0, component.size() - 1) ans = max(ans, int(component[i].size()));
    cout << ans;
}

int main() {
    Input();
    Init();
    Compute();
    return 0;
}
