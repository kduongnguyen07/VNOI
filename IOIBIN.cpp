#include <iostream>
#include <cstring>

using namespace std;

#define rep(i, a, b) for (int i = a; i <= b; i++)

int root[101010];

int getRoot(int u) {
    return root[u] == u ? u : root[u] = getRoot(root[u]);
}

void join(int u, int v) {
    root[getRoot(u)] = getRoot(v);
}

int main() {
    ios::sync_with_stdio(0);
    rep(i, 1, 101010) root[i] = i;
    int P; cin >> P;
    rep(i, 1, P) {
        int u, v, c;
        cin >> u >> v >> c;
        if (c == 1) {
            if (getRoot(u) != getRoot(v))
                join(u, v);
        } else {
            if (getRoot(u) == getRoot(v)) cout << 1 << endl;
            else cout << 0 << endl;
        }
    }
    return 0;
}
