#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void buildTree(const vector<ll> &arr, vector<vector<ll>> &tree, ll ver, ll l, ll r) {
    if (l + 1 == r) {
        tree[ver].push_back(arr[l]);
        return;
    }
    ll mid = (l + r) / 2;
    buildTree(arr, tree, 2 * ver + 1, l, mid);
    buildTree(arr, tree, 2 * ver + 2, mid, r);
    merge(tree[2 * ver + 1].begin(),
          tree[2 * ver + 1].end(),
          tree[2 * ver + 2].begin(),
          tree[2 * ver + 2].end(),
          back_inserter(tree[ver]));
}

ll queryRec(vector<vector<ll>> &tree, ll k, ll ver, ll l, ll r, ll li, ll ri) {
    if (li == l && ri == r) {
        return upper_bound(tree[ver].begin(),
                           tree[ver].end(), k)
               - tree[ver].begin();
    }
    ll mid = (l + r) / 2;
    if (li >= mid) {
        return queryRec(tree, k, 2 * ver + 2, mid, r, li, ri);
    }
    if (ri <= mid) {
        return queryRec(tree, k, 2 * ver + 1, l, mid, li, ri);
    }
    return queryRec(tree, k, 2 * ver + 1, l, mid, li, mid) + queryRec(tree, k, 2 * ver + 2, mid, r, mid, ri);
}