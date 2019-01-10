#include <iostream>
#include <cstring>
#include <string>
#include <vector>

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define loop(i, a) for (auto &i: a)

using namespace std;

struct TRIE{
    bool eow;
    TRIE *F[26];
    TRIE() {
        eow = false;
        memset(F, NULL, sizeof F);
    }
};

int update(TRIE *root, string s) {
    TRIE *crawl = root;
    int res = 0;
    loop(it, s) {
        int idx = it - 'a';
        if (!crawl->F[idx]) crawl->F[idx] = new TRIE;
        crawl = crawl->F[idx];
        if (crawl->eow) res++;
    }
    crawl->eow = true;
    return res + 1;
}

int main() {
    string s;
    int m, res = 0; cin >> m;
    TRIE *root = new TRIE;
    rep(i, 1, m) {
        cin >> s;
        res = max(res, update(root, s));
    }
    cout << res;
    return 0;
}
