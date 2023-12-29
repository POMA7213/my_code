#include <bits/stdc++.h>

using namespace std;
typedef long long ll;


void DoBuild(const vector<ll> &arr, vector<ll> &res, ll ver, ll l, ll r) {
    if (r - l == 1) {
        res[ver] = arr[l];
    } else {
        ll med = (r + l) / 2;
        DoBuild(arr, res, 2 * ver + 1, l, med);
        DoBuild(arr, res, 2 * ver + 2, med, r);
        res[ver] = res[ver * 2 + 1] + res[ver * 2 + 2];
    }
}

ll DoFind(const vector<ll> &tree, ll ver, ll l, ll r, ll il, ll ir) {
    if (l == il && r == ir) {
        return tree[ver];
    }
    auto med = (r + l) / 2;
    if (ir <= med) {
        return DoFind(tree, 2 * ver + 1, l, med, il, ir);
    }
    if (il >= med) {
        return DoFind(tree, 2 * ver + 2, med, r, il, ir);
    }
    return DoFind(tree, 2 * ver + 1, l, med, il, med) + DoFind(tree, 2 * ver + 2, med, r, med, ir);
}

void DoAdd(vector<ll> &tree, ll ver, ll l, ll r, ll pos, ll value) {
    if (r - l == 1) {
        tree[ver] += value;
        return;
    }
    auto med = (r + l) / 2;
    if (pos < med) {
        DoAdd(tree, 2 * ver + 1, l, med, pos, value);
    } else {
        DoAdd(tree, 2 * ver + 2, med, r, pos, value);
    }
    tree[ver] = tree[ver * 2 + 1] + tree[ver * 2 + 2];
}
