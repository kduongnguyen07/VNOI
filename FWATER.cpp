#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

typedef pair<int, int> pii;
typedef pair<int, pii> piii;

#define rep(i, a, b) for (int i = a; i <= b; i++)

int n, root[1010];
vector<piii> edge;

int getRoot(int p) {
    return root[p] == p ? p : root[p] = getRoot(root[p]);
}

void join(int p, int q) {
    root[getRoot(p)] = getRoot(q);
}

void Input() {
    cin >> n;
    rep(i, 0, n) root[i] = i;
    rep(i, 1, n) {
        int c; cin >> c;
        edge.push_back(make_pair(c, pii(0, i)));
    }
    rep(i, 1, n) rep(j, 1, n) {
        int c; cin >> c;
        if (j > i) edge.push_back(make_pair(c, pii(i, j)));
    }
}

void Compute() {
    int ans = 0;
    sort(edge.begin(), edge.end());
    vector<piii>::iterator it;
    for (it = edge.begin(); it != edge.end(); it++) {
        int u = it->second.first, v = it->second.second;
        int c = it->first;
        if (getRoot(u) != getRoot(v)) {
            ans += c;
            join(u, v);
        }
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    Input();
    Compute();
    return 0;
}
