#include <iostream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <string>

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define loop(i, a) for (auto &i: a)

using namespace std;

typedef long int int32;

int m, n, T;
int32 A[2000], B[2000], C[2000];

bool check1(int x) {
    int cnt = 0, idx = 1;
    rep(i, 1, n) {
        if (C[idx] == B[i]) idx++, cnt++;
        if (cnt == x) break;
    }
    if (cnt < x) return false;
    rep(i, 1, x - 1) if (2 * C[i] > C[i + 1]) return false;
    return true;
}

bool check2(int x) {
    int cnt = 0, idx = 1;
    rep(i, 1, m) {
        if (C[idx] == A[i]) idx++, cnt++;
        if (cnt == x) break;
    }
    if (cnt < x) return false;
    rep(i, 1, x - 1) if (2 * C[i] > C[i + 1]) return false;
}

void subtask1() {
    int res = 0;
    if (m < n) {
        rep(i, 0, (1 << m) - 1) {
            int x = 1;
            rep(j, 0, m - 1) if (i >> j & 1) C[x++] = A[j + 1];
            if (check1(x - 1)) res = max(res, x - 1);
        }
    } else {
        rep(i, 0, (1 << n) - 1) {
            int x = 1;
            rep(j, 0, n - 1) if (i >> j & 1) C[x++] = B[j + 1];
            if (check2(x - 1)) res = max(res, x - 1);
        }
    }
    printf("%d\n", res);
}

void subtask23() {
    int32 pre, cur, res = 0;
    memset(C, 0, sizeof C);
    rep(i, 1, m) {
        cur = 0;
        rep(j, 1, n) {
            pre = cur;
            if (A[i] >= 2 * B[j]) cur = max(cur, C[j]);
            if (A[i] == B[j]) C[j] = max(C[j], pre + 1);
        }
    }
    rep(i, 1, n) res = max(res, C[i]);
    printf("%ld\n", res);
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d %d", &m, &n);
        rep(i, 1, m) scanf("%ld", A + i);
        rep(i, 1, n) scanf("%ld", B + i);
        A[0] = B[0] = -1e9;
        // solve
        if (m <= 15 && n <= 15) subtask1();
        else subtask23();
    }
    return 0;
}
