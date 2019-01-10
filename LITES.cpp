#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define loop(i, a) for (auto &i: a)

using namespace std;

typedef long int int32;

struct node {
    int32 lazy, val;
    node() {}
    node(int32 lazy, int32 val): lazy(lazy), val(val) {}
};

int32 n, m;
node ST[505050];

void updateLazy(int32 root, int32 l, int32 r) {
    if (l > r || ST[root].lazy == 0) return;
    if (ST[root].lazy % 2)
        ST[root].val = (r - l + 1) - ST[root].val;
    if (l != r) {
        ST[root * 2].lazy += ST[root].lazy;
        ST[root * 2 + 1].lazy += ST[root].lazy;
    }
    ST[root].lazy = 0;
}

void update(int32 root, int32 l, int32 r, int32 u, int32 v, int32 k) {
    updateLazy(root, l, r);
    if (l > r || l > v || r < u) return;
    if (u <= l && r <= v) {
        ST[root].val = (r - l + 1) - ST[root].val;
        if (l != r) {
            ST[root * 2].lazy++, ST[root * 2 + 1].lazy++;
        }
        return;
    }
    int32 mid = l + r >> 1;
    update(root * 2, l, mid, u, v, k);
    update(root * 2 + 1, mid + 1, r, u, v, k);
    ST[root].val = ST[root * 2].val + ST[root * 2 + 1].val;
}

int32 query(int32 root, int32 l, int32 r, int32 u, int32 v) {
    updateLazy(root, l, r);
    if (l > r || l > v || r < u) return 0;
    if (u <= l && r <= v) return ST[root].val;
    int32 mid = l + r >> 1;
    int32 s1, s2;
    s1 = query(root * 2, l, mid, u, v);
    s2 = query(root * 2 + 1, mid + 1, r, u, v);
    return s1 + s2;
}

int main() {
    memset(ST, 0, sizeof ST);
    scanf("%ld %ld", &n, &m);
    rep(i, 1, m) {
        int32 u, v, c;
        scanf("%ld %ld %ld", &c, &u, &v);
        if (!c) update(1, 1, n, u, v, 1);
        else printf("%ld\n", query(1, 1, n, u, v));
    }
    return 0;
}
