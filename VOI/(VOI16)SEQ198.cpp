#include <iostream>
#include <cstring>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cmath>

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define loop(i, a) for (auto &i: a)

using namespace std;

int m, A[2020], F[2020][1030];
const int mask = (1 << 1) + (1 << 8) + (1 << 9);

void subtask1() {
    int ans = 1e9;
    rep(i, 0, (1 << m) - 1) {
        bool OK = true;
        int res = 0;
        rep(j, 0, m - 1) if (i >> j & 1) {
            rep(k, 0, j - 1) if (i >> k & 1) {
                int tmp = abs(A[j + 1] - A[k + 1]);
                if (tmp == 1 || tmp == 8 || tmp == 9) OK = false;
                if (!OK) break;
            }
            if (!OK) break;
            res++;
        }
        if (OK && res >= 2) ans = min(ans, m - res);
    }
    printf("%d", ans);
}

void subtask2() {
    memset(F, -1, sizeof F);
    F[1][0] = 0; // Khog chon A1
    F[1][1] = 1; // Chon A1
    rep(i, 2, m) {
        int dis = A[i] - A[i - 1];
        rep(j, 0, 1023) {
            if (F[i - 1][j] > -1) {
                int stt = dis >= 10 ? 0 : (j << dis) & 1023; // trang thai moi
                F[i][stt] = max(F[i][stt], F[i - 1][j]); //Khong chon Ai
                if ((stt & mask) == 0) //Chon Ai
                    F[i][stt|1] = max(F[i][stt|1], F[i - 1][j] + 1); //stt | 1 bat bit thu 0 => chon Ai
            }
        }
    }
    int tmp = 0;
    rep(i, 0, 1023) tmp = max(tmp, F[m][i]);
    printf("%d", m - tmp);
}

int main() {
    //freopen("input.INP", "r", stdin);
    scanf("%d", &m);
    rep(i, 1, m) scanf("%d", A + i);
    sort(A + 1, A + m + 1);
    if (m <= 20) subtask1();
    else subtask2();
    return 0;
}
