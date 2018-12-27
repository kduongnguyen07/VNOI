#include <iostream>
#include <cstring>
#include <stdio.h>
#include <algorithm>

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define loop(i, a) for (auto &i: a)

using namespace std;

typedef long int int32;

int32 n, m, A[10101], T[10101], F[10101];
string bridge;

int main() {
    scanf("%ld %ld", &n, &m);
    rep(i, 1, n) scanf("%ld", A + i);
    cin >> bridge; bridge = " " + bridge;
    //
    memset(T, 0, sizeof T);
    rep(i, 1, n) {
        int32 pos = 0;
        while(pos <= m) {
            pos += A[i];
            while(bridge[pos] == '1') pos--;
            T[i]++;
        }
    }
    //
    sort(T + 1, T + n + 1);
    F[1] = T[1], F[2] = T[2];
    rep(i, 3, n) F[i] = min(F[i - 1] + T[1] + T[i], F[i - 2] + T[i] + T[2] * 2 + T[1]);
    /* Explain
    -  TH1 : Da co i - 1 nguoi qua => nguoi thu 1 quay ve don nguoi thu i
    -  TH2 : Da co i - 2 nguoi qua => nguoi thu 1 quay ve nguoi thu i - 1 di voi nguoi thu i qua
             nguoi thu 2 quay ve don nguoi thu 1
    */
    printf("%ld", F[n]);
    return 0;
}
