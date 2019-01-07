#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 13;
string s;
 
ll gt[MAXN+1];
int n, x, a[MAXN+1], b[MAXN+1], i, j;
bool chon[MAXN+1];
ll t;
 
void init() {
    gt[0] = 1;
    gt[1] = 1;
    for (int i=2; i<=MAXN; i++) gt[i] = gt[i-1]*i;
}
 
void query1() {
    ll ans = 0;
    memset(chon,0,sizeof(chon));
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=a[i]-1; j++)
        if (!chon[j]) {
            ans += gt[n-i];
        }
        chon[a[i]] = 1;
    }
    cout << ans+1 << endl;
}
 
void query2() {
    memset(chon,0,sizeof(chon));
    t--;
    for (i=1; i<=n; i++) {
        int tmp = 0;
        for (j=1; j<=n; j++) {
            if (!chon[j]) tmp++;
            if (gt[n-i]*tmp>t) break;
        }
        t -= gt[n-i]*(tmp-1);
        b[i] = j;
        chon[j]=1;
    }
    for (int i=1; i<=n; i++) cout << b[i] << " ";
}
 
int main() {
    	#ifndef ONLINE_JUDGE
    	freopen("test.inp", "r", stdin);
    	freopen("test.out", "w", stdout);
    	#endif
    while (cin>>a[++n]);
    t=a[--n]; n--;
    init();
    query1();
    query2();
    return 0;
}