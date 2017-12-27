#include <iostream>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

#define rep(i, a, b) for (int i = a; i <= b; i++)
#define rep2(i, a, b) for (int i = a; i >= b; i--)
int T, N;
vector<int> Soldiers, L, R;
deque<int> dq;

void Output(const int res, const int left, const int right) {
	cout << res << " " << left << " " << right << endl;
}

void maximize(int &a, int b, int &index) {
	int ans = (R[b] - L[b] + 1) * Soldiers[b];
	if (ans > a) {
		index = b; a = ans;
	}
}

void Compute() {
	cin >> N;
	/*-------Init-------*/
	Soldiers.assign(N + 1, 0); L.assign(N + 1, 0); R.assign(N + 1, 0);
	dq = deque<int> (); 
	/*------------------*/
	rep(i, 1, N) cin >> Soldiers[i];
	rep(i, 1, N) {
		while(!dq.empty() && Soldiers[dq.back()] >= Soldiers[i]) dq.pop_back();
		L[i] = dq.empty() ? 1 : dq.back() + 1;
		dq.push_back(i);
	}
	dq = deque<int> ();
	rep2(i, N, 1) {
		while(!dq.empty() && Soldiers[dq.back()] >= Soldiers[i]) dq.pop_back();
		R[i] = dq.empty() ? N : dq.back() - 1;
		dq.push_back(i);
	}
	int res = 0, index = 0;
	rep(i, 1, N) maximize(res, i, index);
	/*------------------*/
	Output(res, L[index], R[index]);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> T;
	while(T--) Compute();
	return 0;
}
