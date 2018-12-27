#include <iostream>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <algorithm>
#include <bitset>

using namespace std;

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define loop(i, a) for (auto &i: a)

typedef long int int32;
typedef long long int64;
typedef pair<int, int> pii;

const int movex[] = {-1, -2, -2, -1, 1, 2, 2, 1};
const int movey[] = {-2, -1, 1, 2, 2, 1, -1, -2};

struct node {
    int32 c;
    int x, y, dc1, dc2, row, col;
    pii l[10];
    node() {}
    node(int x, int y): x(x), y(y) {}
    node(int x, int y, int32 c): x(x), y(y), c(c) {}
};

int K;
int32 cell[10][10];
node F[10][10], P[10];
vector<node> A, B;
int64 best;

void Init() {
    rep(i, 1, 8) {
        rep(j, 1, 8) {
            F[i][j].dc1 = i - j + 8;
            F[i][j].dc2 = i + j;
            F[i][j].row = i;
            F[i][j].col = j;
            rep(k, 0, 7) F[i][j].l[k] = {i + movex[k], j + movey[k]};
        }
    }
}

void check() {
    int64 res = 0;
    loop(it, A) {
        int r, c, dc1, dc2;
        r = it.x, c = it.y;
        dc1 = it.x - it.y + 8, dc2 = it.x + it.y;
        //
        if (dc1 == P[1].dc1 || dc1 == P[3].dc1) res += it.c;
        else if (dc2 == P[1].dc2 || dc2 == P[3].dc2) res += it.c;
        else if (r == P[1].row || r == P[2].row) res += it.c;
        else if (c == P[1].col || c == P[2].col) res += it.c;
        else rep(j, 0, 7)
            if (it.x == P[4].l[j].first && it.y == P[4].l[j].second) {
                res += it.c; break;
            }
    }
    best = max(best, res);
}

void solve(int u) {
    if (u > 4) {
        check();
        return;
    }
    loop(it, B) {
        int i, j; i = it.x, j = it.y;
        if (!cell[i][j]) {
            P[u] = F[i][j];
            cell[i][j] = -1;
            solve(u + 1);
            cell[i][j] = 0;
        }
    }
}

int main() {
    scanf("%d", &K);
    memset(cell, 0, sizeof cell);
    rep(i, 1, K) {
        int u, v;
        int32 c;
        scanf("%d %d %ld", &u, &v, &c);
        A.push_back(node(u, v, c));
        cell[u][v] = c;
    }
    Init();
    rep(i, 1, 8) rep(j, 1, 8)
        if (!cell[i][j]) B.push_back(node(i, j));
    solve(1);
    printf("%lld", best);
    return 0;
}
