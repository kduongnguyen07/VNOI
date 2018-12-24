#include <iostream>
#include <vector>

using namespace std;

#define rep(i, a, b) for (int i = a; i <= b; i++)

int P, root[101010];

int getRoot(int p) {
    return root[p] == p ? p : getRoot(root[p]);
}

void join(int p, int q) {
    root[getRoot(p)] = getRoot(q);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> P;
    while(P--) {
        int u, v, c; cin >> u >> v >> c;
        if (c == 1) {
            if (getRoot(u) != getRoot(v)) join(u, v);
        } else {
            if (getRoot(u) == getRoot(v)) cout << 1 << endl;
            else cout << 0 << endl;
        }
    }
    return 0;
}
