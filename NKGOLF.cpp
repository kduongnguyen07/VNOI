#include <iostream>
#include <stdio.h>
#include <deque>
#include <cstring>
#include <algorithm>

#define rep(i, a, b) for (int i (a); i <= (b); i++)
#define rep2(i, a, b) for (int i = (a); i >= (b); i--)
#define loop(i, a) for (auto &i: a)

using namespace std;

typedef long int int32;

int32 m, n, grid[1010][1010], h[1010], res = 1;
int32 L[1010], R[1010];
bool F[1010][1010];
deque<int32> dq;

int main() {
    scanf("%ld %ld", &m, &n);
    rep(i, 1, m) rep(j, 1, n) scanf("%ld", &grid[i][j]);
    //Init
    memset(h, 0, sizeof h);
    memset(F, 0, sizeof F);
    rep(i, 1, m - 1) rep(j, 1, n - 1)
        F[i][j] = (grid[i][j] <= grid[i][j + 1] && grid[i][j] <= grid[i + 1][j])
                   && (grid[i][j + 1] <= grid[i + 1][j + 1] && grid[i + 1][j] <= grid[i + 1][j + 1]);
    //
    int32 tmp = 1;
    rep(i, 1, n) {
        tmp = 1;
        rep(j, 1, m - 1)
            if (grid[j][i] <= grid[j + 1][i]) tmp++, res = max(res, tmp);
            else tmp = 1;
    }
    tmp = 1;
    //printf("%ld\n", res);
    rep(i, 1, m) {
        tmp = 1;
        rep(j, 1, n - 1)
            if (grid[i][j] <= grid[i][j + 1]) tmp++, res = max(res, tmp);
            else tmp = 1;
    }
    //printf("%ld\n", res);
    memset(L, 0, sizeof L); memset(R, 0, sizeof R);
    rep(i, 1, m - 1) {
        rep(j, 1, n - 1) if (F[i][j]) h[j]++;
            else h[j] = 0;
        dq.clear();
        rep(j, 1, n - 1) {
            while(!dq.empty() && h[j] <= h[dq.back()]) dq.pop_back();
            L[j] = dq.empty() ? 1 : dq.back() + 1;
            dq.push_back(j);
        }
        dq.clear();
        rep2(j, n - 1, 1) {
            while(!dq.empty() && h[j] <= h[dq.back()]) dq.pop_back();
            R[j] = dq.empty() ? n - 1 : dq.back() - 1;
            dq.push_back(j);
        }
        rep(j, 1, n - 1) if (h[j] > 0) res = max(res, (h[j] + 1) * (R[j] - L[j] + 2));
    }
    printf("%ld", res);
    return 0;
}
