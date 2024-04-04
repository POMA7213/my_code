#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void Update(vector<ll> &tree, ll pos, ll val) {
    while (pos < tree.size()) {
        tree[pos] += val;
        pos = pos | (pos + 1);
    }
}

ll Pref(const vector<ll> &tree, ll pos) {
    ll res = 0;
    while (pos > -1) {
        res += tree[pos];
        pos = (pos & (pos + 1)) - 1;
    }
    return res;
}

ll Sum(const vector<ll> &tree, ll l, ll r) {
    if (l > 0) {
        return Pref(tree, r) - Pref(tree, l - 1);
    }
    return Pref(tree, r);
}

void Init(vector<ll> &tree, const vector<ll> &arr) {
    for (ll i = 0; i < arr.size(); ++i) {
        Update(tree, i, arr[i]);
    }
}
