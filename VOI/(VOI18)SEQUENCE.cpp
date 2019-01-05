#include <iostream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cmath>
#define rep(i, a, b) for (int i = (a); i <= (b); i++)

#define rep2(i, a, b) for (int i = (a); i >= (b); i--)
#define loop(i, a) for (auto &i: a)

using namespace std;

typedef long int int32;
typedef long long int64;

int32 n;
int64 F[101010];
vector<int64> A, B;

bool check(int64 k, int32 idx) {
    int64 tmp = 0, des = -1;
    vector<int64> C(B);
    C[idx] = k;
    rep2(i, idx - 1, 1) while(C[i] >= C[i + 1]) C[i]--;
    rep(i, 1, idx) tmp += abs(C[i] - A[i]);
    if (tmp > F[idx]) return false;
    B = C;
    while(true) {
        C[idx - 1]--;
        rep2(i, idx - 2, 1) if (C[i] == C[i + 1]) C[i]--;
        rep(i, 1, idx) tmp += abs(C[i] - A[i]);
        if (tmp > F[idx]) break;
        B = C;
    }
    return true;
}

int main() {
    freopen("SEQUENCE.INP", "r", stdin);
    freopen("SEQUENCE.OUT", "w", stdout);
    scanf("%ld", &n);
    A.assign(n + 1, 0); B.assign(n + 1, 0);
    rep(i, 1, n) scanf("%ld", &A[i]);
    //
    int64 ans = 0;
    F[1] = 0;
    B[1] = A[1];    
    rep(i, 2, n) {
        B[i] = max(B[i - 1] + 1, A[i]);
        F[i] = F[i - 1] + abs(B[i] - A[i]);
        // Thu giam
        int64 l, r, mid, best;
        l = min(B[i - 1] + 1, A[i]), r = max(B[i - 1] + 1, A[i]);
        mid = l + r >> 1;
        while(l <= r) {
            if (check(mid, i)) { //Tim nho nhat co the
                best = mid;
                r = mid - 1;
            } else l = mid + 1;
            mid = l + r >> 1;
        }
    }
    printf("%lld\n", F[n]);
    rep(i, 1, n) printf("%lld ", B[i]);
    return 0;
}