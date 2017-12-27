#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<int> A, F;

int main() {
	cin >> n;
	A.assign(n + 1, 0);
	F.assign(n + 1, 0);
	for (int i = 1; i < n; i++) cin >> A[i];
	F[0] = 0; F[1] = A[1]; A[n] = 1e9;
	for (int i = 2; i <= n; i++) {
		F[i] = min(F[i - 2] + A[i - 1], F[i - 1] + A[i]);
	}
	cout << F[n];
	return 0;
}