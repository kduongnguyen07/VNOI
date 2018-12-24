#include <stdio.h>
#include <cstring>
#include <algorithm>

using namespace std;

#define rep(i, a, b) for (int i = a; i <= b; i++)

int adj[110][110], F[110][110];
int m, n, ans = -1e9;

int main() {
    scanf("%ld %ld", &m, &n);
    rep(i, 1, m) rep(j, 1, n) scanf("%ld", &adj[i][j]);
    rep(i, 1, m) rep(j, 1, n) F[i][j] = -1e9;
    rep(i, 1, m) F[i][1] = adj[i][1];
    rep(j, 2, n) rep(i, 1, m) {
        F[i][j] = F[i][j - 1];
        if (i > 1) F[i][j] = max(F[i][j], F[i - 1][j - 1]);
        if (i < m) F[i][j] = max(F[i][j], F[i + 1][j - 1]);
        F[i][j] += adj[i][j];
    }
    rep(i, 1, m) ans = max(ans, F[i][n]);
    printf("%ld", ans);
    return 0;
}
