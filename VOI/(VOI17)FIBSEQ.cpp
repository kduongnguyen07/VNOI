#include <iostream>
#include <cstring>
#include <cmath>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <map>
#include <stack>

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define loop(i, a) for (auto &i: a)

using namespace std;

typedef long int int32;
typedef long long int64;
typedef pair<int32, int32> pii;

int T;
int32 n, k, chuki, pre[1010101];
int64 p, F[6060606], S[1010101];

int main() {
    freopen("FIBSEQ.INP", "r", stdin);
    freopen("FIBSEQ.OUT", "w", stdout);
    scanf("%d", &T);
    while(T--) {
        scanf("%ld %lld %ld", &n, &p, &k);
        F[1] = F[2] = 1 % k;
        //Tim chu ki pisano
        for (int i = 3;; i++) {
            F[i] = (F[i - 1] + F[i - 2]) % k;
            if (F[i] == F[2] && F[i - 1] == F[1]) {
                chuki = i - 2;
                break;
            }
        }
        F[0] = F[chuki];
        // Tong lien tiep
        memset(pre, 0, sizeof pre);
        S[0] = 0;
        rep(i, 1, n) S[i] = (S[i - 1] + F[(i + p - 1) % chuki]) % k;
        bool OK = false;
        rep(i, 1, n) {
            if (!S[i]) {
                printf("%ld ", i);
                rep(j, 1, i) printf("%lld ", p + j - 1);
                OK = true;
                break;
            }
            if (pre[S[i]]) { //Tong tu prev[S[i]] -> i = 0
                printf("%ld ", i - pre[S[i]]);
                rep(j, pre[S[i]] + 1, i) printf("%lld ", p + j - 1);
                OK = true;
                break;
            } else pre[S[i]] = i;
        }
        if (!OK) printf("NO");
        printf("\n");
    }
    return 0;
}
