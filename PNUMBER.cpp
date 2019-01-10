#include <iostream>
#include <cstring>
#include <stdio.h>
#include <cmath>

#define rep(i, a, b) for (int i = (a); i <= (b); i++)

using namespace std;

typedef long int int32;

int main() {
    int32 A, B; scanf("%ld %ld", &A, &B);
    static bool prime[200002];
    memset(prime, true, sizeof prime);
    prime[0] = prime[1] = false;
    for (int i = 2; i * i <= B; i++) {
        if (prime[i]) for (int j = i * i; j <= B; j += i) prime[j] = false;
    }
    rep(i, A, B) if (prime[i]) printf("%ld\n", i);
    return 0;
}
