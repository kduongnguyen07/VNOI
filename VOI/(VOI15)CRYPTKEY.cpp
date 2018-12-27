#include <iostream>
#include <cstring>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <map>

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rep2(i, a, b) for (int i = (a); i >= (b); i--)
#define loop(i, a) for (auto &i: a)

using namespace std;

typedef long long int64;

int T, n;
int64 A[5050], k;
map<string, bool> F;

int64 gcd(int64 A, int64 B) {
    while(B > 0) {
        int64 tmp = B;
        B = A % B;
        A = tmp;
    }
    return A;
}

string mul(string A, int64 B) {
    string C = "";
    int64 s = 0, nho = 0;
    rep2(i, A.size() - 1, 0) {
        s = (A[i] - 48) * B + nho;
        nho = s / 10;
        C = char(s % 10 + 48) + C;
    }
    if (nho > 0) C = to_string(nho) + C;
    return C;
}

string div(string A, int64 B) {
    string C = "";
    int64 s = 0, nho = 0;
    rep(i, 0, A.size() - 1) {
        s = nho * 10 + A[i] - 48;
        nho = s % B;
        C += char(s / B + 48);
    }
    while(C.size() > 1 && C[0] == '0') C.erase(C.begin());
    return C;
}

string lcm(int64 A, int64 B) {
    string res = mul(to_string(A), B);
    res = div(res, gcd(A, B));
    return res;
}

int main() {
    scanf("%d", &T);
    while(T--) {
        bool OK = true;
        F.clear();
        scanf("%d", &n);
        rep(i, 1, n) {
            scanf("%lld", A + i);
            F[to_string(A[i])] = true;
        }
        scanf("%lld", &k);
        F[to_string(k)] = true;
        rep(i, 1, n) if (!F[to_string(gcd(A[i], k))] || !F[lcm(A[i], k)]) {
            printf("NO\n"); OK = false; break;
        }
        if (OK) printf("YES\n");
    }
    return 0;
}
