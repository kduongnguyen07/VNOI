#include <iostream>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

#define rep(i, a, b) for (int i = a; i <= b; i++)
int n, m, F[101010];
vector<int> r, A;
string bridge;

int getTime(int fstep) {
	int res = 0, cur = 0;
	while(1) {
		cur += fstep; res++;
		if (cur > m) return res;
		while(bridge[cur - 1] == '1') cur--;
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	r.assign(n + 1, 0); A.assign(n, 0);
	rep(i, 1, n) cin >> r[i];
	cin >> bridge;
	//--------------------------------------
	rep(i, 1, n) A[i - 1] = getTime(r[i]);
	sort(A.begin(), A.end());
	F[1] = A[0]; F[2] = A[1];
	rep(i, 3, n) 
	    F[i] = min(A[i - 1] + A[0] + F[i - 1], A[1] * 2 + A[i - 1] + A[0] + F[i - 2]);
	cout << F[n];
	//--------------------------------------
	return 0;
}
