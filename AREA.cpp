#include <iostream>
#include <cstring>
#include <vector>
#include <stdio.h>
#include <algorithm>

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define loop(i, a) for (auto &i: a)

using namespace std;

typedef long int int32;
typedef long long int64;

const int32 maxn = 30010;

struct node {
    int32 x, y1, y2, type;
    node() {}
    node(int32 x, int32 y1, int32 y2, int32 type): x(x), y1(y1), y2(y2), type(type) {}
    bool operator < (node A) { return this->x < A.x || this->x == A.x && this->type < A.type; }
};

struct STNode {
    int32 cnt, len;
    STNode() { cnt = len = 0; }
    STNode(int32 cnt, int32 len): cnt(cnt), len(len) {}
};

int64 res = 0;
vector<node> A;
STNode ST[maxn * 5 + 1];

void update(int32 root, int32 l, int32 r, int32 u, int32 v, int32 k) {
    if (l > r || l > v || r < u) return;
    if (l >= u && r <= v) {
        ST[root].cnt += k;
        if (k == 1) ST[root].len = (r - l + 1);
        else if (ST[root].cnt == 0) ST[root].len = ST[root * 2].len + ST[root * 2 + 1].len;
        return;
    }
    int32 mid = l + r >> 1;
    update(root * 2, l, mid, u, v, k);
    update(root * 2 + 1, mid + 1, r, u, v, k);
    if (ST[root].cnt == 0) ST[root].len = ST[root * 2].len + ST[root * 2 + 1].len;
}

int main() {
    int32 n; scanf("%ld", &n);
    rep(i, 1, n) {
        int32 x, y, u, v;
        scanf("%ld %ld %ld %ld", &x, &y, &u, &v);
        A.push_back(node(x, y, v, 1));
        A.push_back(node(u, y, v, -1));
    }
    sort(A.begin(), A.end());
    int32 prex = 0;
    loop(it, A) {
        res += 1LL * (it.x - prex) * ST[1].len;
        prex = it.x;
        update(1, 0, maxn, it.y1, it.y2 - 1, it.type);
    }
    printf("%lld", res);
    return 0;
}
