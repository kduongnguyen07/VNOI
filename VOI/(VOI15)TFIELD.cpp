#include <iostream>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define rep2(i, a, b) for (int i = (a); i >= (b); i--)
#define loop(i, a) for (auto &i: a)
#define fi first
#define se second

using namespace std;

typedef long int int32;
typedef long long int64;
typedef pair<int64, int32> pii;

int32 m, k, n, c;
vector<pii> field;
vector<int32> F;

int64 getS(int32 n, vector<int64> x, vector<int64> y) {
    int64 res = 0;
    rep(i, 0, n - 1) res += (x[i] - x[(i + 1) % n]) * (y[i] + y[(i + 1) % n]);
    return abs(res);
}

int64 solve(int32 color) {
    F[0] = (field[0].se != color);
    rep(i, 1, m - 1) F[i] = F[i - 1] + (field[i].se != color);
    //
    int64 res = 0, tmp = 0;
    for (int32 i = 0, j = 0; j < m; j++) {
        tmp += field[j].fi;
        while(i < j && F[j] - (!i ? 0: F[i - 1]) > k) {
            tmp -= field[i].fi;
            i++;
        }
        res = max(res, tmp);
    }
    return res;
}

int main() {
    scanf("%ld %ld", &m, &k);
    F.assign(m, 0);
    rep(i, 1, m) {
        scanf("%ld %ld", &n, &c);
        vector<int64> x(n), y(n);
        rep(i, 1, n) scanf("%lld %lld", &x[i - 1], &y[i - 1]);
        field.push_back({getS(n, x, y), c});
    }
    sort(field.begin(), field.end());
    rep2(i, m - 1, 1) field[i].fi -= field[i - 1].fi;
    int64 res = 0;
    rep(i, 1, m) res = max(res, solve(i));
    if (res & 1) printf("%lld.5", res / 2);
    else printf("%lld.0", res / 2);
    return 0;
}
