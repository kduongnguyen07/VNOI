#include <iostream>
#include <stdio.h>
#include <cstring>
using namespace std;

#define maxn 1000001
typedef long long ll;
ll ans[maxn], phi[maxn], sum[maxn];
int n;

void pre_cal() {
    for (int i = 1; i < maxn; i++) phi[i] = i;
    for (int i = 2; i < maxn; i++) {
        if (phi[i] == i) {
            for (int j = i; j < maxn; j+=i) phi[j] -= phi[j] / i;
        }
    }
    for (int i = 1; i < maxn; i++) {
        for (int j = i; j < maxn; j+= i) sum[j] += ll(i * phi[j/i]);
    }
    ans[0] = 0;
    for (int i = 1; i < maxn; i++) sum[i] -= i;
    for (int i = 1; i < maxn; i++) ans[i] = ans[i - 1] + sum[i];
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    pre_cal();
    while(1) {
        cin >> n;
        if (!n) break;
        else cout << ans[n] << endl; 
    }
    return 0;
}
