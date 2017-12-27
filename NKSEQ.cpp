#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
vector<int> a, sum;
int n, x, _count = 0;
bool check(int i) {
	if (a[i] < 0) return false;
	for (int j = i; j <= n; j++) 
		if (sum[j] - sum[i - 1] <= 0) return false;
	for (int j = 1; j < i; j++) 
		if (sum[n] - sum[i - 1] + sum[j] <= 0) return false;
	return true;
}

int main() {
	cin >> n;
	sum.push_back(0);
	a.push_back(0);
	for (int i = 1; i <= n; i++) {
		cin >> x; a.push_back(x);
		sum.push_back(sum[i - 1] + a[i]);
	}
	for (int i = 1; i <= n; i++) {
	 	if (check(i)) _count++;
	}
	cout << _count;
	return 0;
}
