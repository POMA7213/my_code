#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

vector<vector<ll>> Manacher(const string &str) {
    ll n = str.size();
    vector<vector<ll>> res(2, vector<ll>(n));
    for (ll type = 0; type < 2; type++) {
        ll l = 0, r = 0;
        for (ll i = 0; i < n; ++i) {
            if (i < r) {
                res[type][i] = min(r - i + (1 - type), res[type][l + r - i + (1 - type)]);
            }
            ll li = i - res[type][i], ri = i + res[type][i] - (1 - type);
            while (li > 0 && ri + 1 < n && str[li - 1] == str[ri + 1]) {
                res[type][i]++;
                li--;
                ri++;
            }
            if (ri > r) {
                r = ri, l = li;
            }
        }
    }
    return res;
}
