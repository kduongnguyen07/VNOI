#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

#define rep(i, a, b) for (int i = a; i <= b; i++)
typedef pair<int, int> pii;

vector<pii> edge;
int n, m, root[1010];

int getRoot(int p) {
    return root[p] == p ? p : getRoot(root[p]);
}

void join(int p, int q) {
    root[getRoot(p)] = getRoot(q);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    while(m--) {
        int u, v; cin >> u >> v;
        edge.push_back(pii(u, v));
    }
    rep(i, 1, n) root[i] = i;
    vector<pii>::iterator it;
    for (it = edge.begin(); it != edge.end(); it++) {
        int u = it->first, v = it->second;
        if (getRoot(u) != getRoot(v)) join(u, v);
    }
    rep(i, 2, n) if (getRoot(i) != getRoot(1)) cout << i << endl;
    return 0;
}
