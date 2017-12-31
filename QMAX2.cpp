#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;

struct NODE{
    ll val, lazy;
    NODE() {
        val = lazy = 0;
    }
};

vector<NODE>ST(505050);

void updateLazy(int root, int start, int end) {
    if (ST[root].lazy == 0) return;
    ll t = ST[root].lazy;
    ST[root].val += t;
    if (start != end) {
        ST[root* 2].lazy += t;
        ST[root * 2 + 1].lazy += t;
    }
    ST[root].lazy = 0;
}

void update(int root, int start, int end, int u, int v, int k) {
    updateLazy(root, start, end);
    if (start > end || start > v || end < u) return;
    if (start >= u && end <= v) {
        ST[root].val += k;
        if (start != end) {
            ST[root * 2].lazy += k;
            ST[root * 2 + 1].lazy += k;
        }
        return;
    }
    int mid = (start + end) >> 1;
    update(root * 2, start, mid, u, v, k);
    update(root * 2 + 1, mid + 1, end, u, v, k);
    ST[root].val = max(ST[root * 2].val, ST[root * 2 + 1].val);
}

ll query(int root, int start, int end, int u, int v) {
    updateLazy(root, start, end);
    if (start > end || start > v || end < u) return 0;
    if (start >= u && end <= v) return ST[root].val;
    int mid = (start + end) >> 1;
    ll p1 = query(root * 2, start, mid, u, v);
    ll p2 = query(root * 2 + 1, mid + 1, end, u, v);
    return max(p1, p2);
}

int main() {
    ios::sync_with_stdio(0);
    int n, m, t, u, v;
    ll val;
    cin >> n >> m;
    while(m--) {
        cin >> t >> u >> v;
        if (!t) {
            cin >> val; update(1, 1, n, u, v, val);
        } else cout << query(1, 1, n, u, v) << endl;
    }
    return 0;
}
