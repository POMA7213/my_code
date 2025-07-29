#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

vector<vector<ll>> FloydWarshall(const vector<map<ll, ll>> &graph)
{
    ll n = graph.size();
    vector<vector<ll>> res(n, vector<ll>(n, LONG_LONG_MAX / 5));
    for (ll i = 0; i < n; ++i)
    {
        res[i][i] = 0;
        for (const auto &[k, v] : graph[i])
        {
            res[i][k] = v;
        }
    }
    for (ll i = 0; i < n; ++i)
    {
        for (ll k = 0; k < n; ++k)
        {
            for (ll l = 0; l < n; ++l)
            {
                res[k][l] = min(res[k][l], res[k][i] + res[l][i]);
            }
        }
    }
    return res;
}
