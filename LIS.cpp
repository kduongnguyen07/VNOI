#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define loop(i, a) for (auto &i: a)

using namespace std;

typedef long int int32;

int32 n, val, F[30303], res = 0;
vector<int32> A;

int main() {
    scanf("%ld", &n);
    rep(i, 1, n) {
        scanf("%ld", &val); A.push_back(val);
    }
    memset(F, 0x3f3f3f3f, sizeof F);
    loop(it, A) {
        auto idx = lower_bound(F + 1, F + n + 1, it) - F;
        F[idx] = it;
        res = max(res, int32(idx));
    }
    printf("%ld", res);
    return 0;
}
