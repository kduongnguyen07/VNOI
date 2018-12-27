#include <iostream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <algorithm>

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define loop(i, a) for (auto &i: a)

using namespace std;

typedef long int int32;
typedef long long int64;

int32 n, A[1010101];
int64 best, F[1010101][2];
// 0: +  || 1: -

void subtask1() {
    best = -1e15;
    rep(i, 0, (1 << n) - 1) {
        int64 res = 0;
        int op = 0;
        rep(j, 0, n - 1) if (i >> j & 1) {
            if (!op) res += A[j + 1];
            else res -= A[j + 1];
            op ^= 1;
        }
        best = max(best, res);
    }
    printf("%lld", best);
}

void subtask2() {
    F[1][0] = A[1];
    F[1][1] = 0;
    rep(i, 2, n) {
        F[i][0] = max(F[i - 1][0], F[i - 1][1] + A[i]);
        F[i][1] = max(F[i - 1][1], F[i - 1][0] - A[i]);
    }
    printf("%lld", max(F[n][0], F[n][1]));
}

int main() {
    scanf("%ld", &n);
    rep(i, 1, n) scanf("%ld", A + i);
    if (n <= 20) subtask1();
    else subtask2();
    return 0;
}
