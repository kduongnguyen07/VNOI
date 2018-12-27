#include <iostream>
#include <cstring>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define loop(i, a) for (auto &i: a)

using namespace std;

int n, m, F[1010][1010];
int A[1010], B[1010];

int main() {
	scanf("%d %d", &m, &n);
	rep(i, 1, m) scanf("%d", A + i);
	rep(i, 1, n) scanf("%d", B + i);
	//
	memset(F, 0, sizeof F);
	rep(i, 1, m) {
		rep(j, 1, n) if (A[i] == B[j]) {
			if (i == 1 || j == 1) F[i][j] = 1;
			else F[i][j] = F[i - 2][j - 2] + 1;
	   	} else F[i][j] = max(F[i - 1][j], F[i][j - 1]);
	}
	printf("%d", F[m][n]);
	return 0;
}
