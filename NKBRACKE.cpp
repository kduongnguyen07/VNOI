#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <string>

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define loop(i, a) for (auto &i: a)
#define fi first
#define se second

using namespace std;

typedef long int int32;
typedef pair<int32, int32> pii;

int32 n, m;
string s;
pii ST[404040];

pii merge(pii A, pii B) {
    int32 x = min(A.fi, B.se);
    return {A.fi - x + B.fi, B.se - x + A.se};
}

void update(int32 root, int32 l, int32 r, int32 idx, char key) {
    if (l > r || l > idx || r < idx) return;
    if (l == idx && r == idx) {
        if (key == '(') ST[root] = {1, 0};
        else ST[root] = {0, 1};
        return;
    }
    int32 mid = l + r >> 1;
    update(root * 2, l, mid, idx, key);
    update(root * 2 + 1, mid + 1, r, idx, key);
    ST[root] = merge(ST[root * 2], ST[root * 2 + 1]);
}

pii query(int32 root, int32 l, int32 r, int32 u, int32 v) {
    if (l > r || l > v || r < u) return {0, 0};
    if (u <= l && r <= v) return ST[root];
    int32 mid = l + r >> 1;
    pii left = query(root * 2, l, mid, u, v);
    pii right = query(root * 2 + 1, mid + 1, r, u, v);
    return merge(left, right);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    cin >> s;
    rep(i, 0, s.size() - 1) update(1, 1, n, i + 1, s[i]);
    while(m--) {
        int32 c, u, v; char x;
        cin >> c;
        if (!c) {
            cin >> u >> x; update(1, 1, n, u, x);
        } else {
            cin >> u >> v;
            pii res = query(1, 1, n, u, v);
            if (res == pii(0, 0)) cout << 1;
            else cout << 0;
        }
    }
    return 0;
}
