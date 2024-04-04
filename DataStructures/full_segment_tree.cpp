
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;


void DoBuild(const vector <ll> &arr, vector <pair<ll, ll>> &res, ll ver, ll l, ll r) {
    if (r - l == 1) {
        res[ver].first = arr[l];
    } else {
        ll med = (r + l) / 2;
        DoBuild(arr, res, 2 * ver + 1, l, med);
        DoBuild(arr, res, 2 * ver + 2, med, r);
        res[ver].first = res[ver * 2 + 1].first + res[ver * 2 + 2].first;
    }
}

void DoPush(vector <pair<ll, ll>> &tree, ll ver, ll l, ll r) {
    if (tree[ver].second != 0 && r - l > 1) {
        tree[2 * ver + 1].second += tree[ver].second;
        tree[2 * ver + 2].second += tree[ver].second;
        ll med = (l + r) / 2;
        tree[2 * ver + 1].first += tree[ver].second * (med - l);
        tree[2 * ver + 2].first += tree[ver].second * (r - med);
    }
    tree[ver].second = 0;
}

ll DoFind(vector <pair<ll, ll>> &tree, ll ver, ll l, ll r, ll il, ll ir) {
    if (l == il && r == ir) {
        return tree[ver].first;
    }
    DoPush(tree, ver, l, r);
    auto med = (r + l) / 2;
    if (ir <= med) {
        return DoFind(tree, 2 * ver + 1, l, med, il, ir);
    }
    if (il >= med) {
        return DoFind(tree, 2 * ver + 2, med, r, il, ir);
    }
    return DoFind(tree, 2 * ver + 1, l, med, il, med) + DoFind(tree, 2 * ver + 2, med, r, med, ir);
}

void DoAdd(vector <pair<ll, ll>> &tree, ll ver, ll l, ll r, ll il, ll ir, ll value) {
    if (l == il && r == ir) {
        tree[ver].second += value;
        tree[ver].first += value * (r - l);
        return;
    }
    DoPush(tree, ver, l, r);
    auto med = (r + l) / 2;
    if (ir <= med) {
        DoAdd(tree, 2 * ver + 1, l, med, il, ir, value);
    } else if (il >= med) {
        DoAdd(tree, 2 * ver + 2, med, r, il, ir, value);
    } else {
        DoAdd(tree, 2 * ver + 1, l, med, il, med, value);
        DoAdd(tree, 2 * ver + 2, med, r, med, ir, value);
    }
    tree[ver].first = tree[2 * ver + 1].first + tree[2 * ver + 2].first;
}

int main() {
    srand(5);
    vector <ll> data(10);
    vector <pair<ll, ll>> tree(45);
    for (ll i = 0; i < 10000; ++i) {
        ll oper = rand() % 2;
        ll l, r;
        l = rand() % 10;
        r = rand() % (10 - l) + l + 1;
        if (oper) {
            ll val;
            val = rand() % 10;
            for (ll j = l; j < r; ++j) {
                data[j] += val;
            }
            DoAdd(tree, 0, 0, 10, l, r, val);
        } else {
            ll dum = accumulate(data.begin() + l, data.begin() + r, 0ll);
            ll res = DoFind(tree, 0, 0, 10, l, r);
            if (dum != res) {
                cout << l << ' ' << r << ' ' << i << '\n';
            }
        }
    }
}
