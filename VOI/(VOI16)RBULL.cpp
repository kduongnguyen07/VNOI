#include <iostream>
#include <cstring>
#include <string>
#include <stdio.h>
#include <vector>
#include <algorithm>

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rep2(i, a, b) for (int i = (a); i >= (b); i--)
#define loop(i, a) for (auto &i: a)

using namespace std;

typedef long int int32;
typedef long long int64;

int32 m, n;
int32 F[1010][1010], R[1010][1010], G[2020][2020], S[2020][2020];
char cell[1010][1010];

int32& rotate(int32 i, int32 j) {
    return G[i + n - j][j + i - 1];
}

struct node {
    int32 x, y;
    node() {}
    node(int x, int y): x(x), y(y) {}
};

node locate (int32 i, int32 j) {
    return node(i + n - j, j + i - 1);
}

int32 getS(int32 u, int32 v, int32 x, int32 y) {
    return S[x][y] - S[x][v - 1] - S[u - 1][y] + S[u - 1][v - 1];
}

int main() {
    scanf("%ld %ld", &m, &n);
    rep(i, 1, m) scanf("%s", cell[i] + 1);
    // Tim chu vi cua hinh thoi co tam la o (i;j)
    memset(F, 0, sizeof F);
    memset(R, 0x3f3f, sizeof R);
    rep(i, 2, m) {
        rep(j, 2, n) {
            if (cell[i][j] != '*' || cell[i - 1][j] != '*') {
                if (cell[i][j] != '*' || cell[i][j - 1] != '*')
                    F[i][j] = min(F[i - 1][j], F[i][j - 1]) + 1;
            }
            R[i][j] = min(R[i][j], F[i][j]);
        }
    }
    memset(F, 0, sizeof F);
    rep(i, 2, m) {
        rep2(j, n - 1, 1) {
            if (cell[i][j] != '*' || cell[i - 1][j] != '*') {
                if (cell[i][j] != '*' || cell[i][j + 1] != '*')
                    F[i][j] = min(F[i - 1][j], F[i][j + 1]) + 1;
            }
            R[i][j] = min(R[i][j], F[i][j]);
        }
    }
    memset(F, 0, sizeof F);
    rep2(i, m - 1, 1) {
        rep2(j, n - 1, 1) {
            if (cell[i][j] != '*' || cell[i + 1][j] != '*') {
                if (cell[i][j] != '*' || cell[i][j + 1] != '*')
                    F[i][j] = min(F[i + 1][j], F[i][j + 1]) + 1;
            }
            R[i][j] = min(R[i][j], F[i][j]);
        }
    }
    memset(F, 0, sizeof F);
    rep2(i, m - 1, 1) {
        rep(j, 2, n) {
            if (cell[i][j] != '*' || cell[i + 1][j] != '*') {
                if (cell[i][j] != '*' || cell[i][j - 1] != '*')
                    F[i][j] = min(F[i + 1][j], F[i][j - 1]) + 1;
            }
            R[i][j] = min(R[i][j], F[i][j]);
        }
    }
    rep(i, 1, m) R[i][1] = R[i][n] = 0;
    rep(j, 1, n) R[1][j] = R[m][j] = 0;
    // Xoay hinh
    memset(G, 0, sizeof G);
    memset(S, 0, sizeof S);
    int32 ans = 0, rans;
    node res;
    rep(i, 1, m) rep(j, 1, n) rotate(i, j) = cell[i][j] == '*'? 1 : 0;
    rep(i, 1, max(m, n) * 2 - 1) rep(j, 1, max(m, n) * 2 - 1)
        S[i][j] = G[i][j] + S[i - 1][j] + S[i][j - 1] - S[i - 1][j - 1];
    rep(i, 1, m) {
        rep(j, 1, n) {
            node a = locate(i, j);
            int r = R[i][j];
            if (getS(a.x - r, a.y - r, a.x + r, a.y + r) > ans) {
                ans = getS(a.x - r, a.y - r, a.x + r, a.y + r);
                res = {i, j};
                rans = r;
            }
        }
    }
    printf("%ld %ld %ld %ld", ans, res.x, res.y, rans);
    return 0;
}
