#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;

ld PolygonArea(const vector<pair<ld, ld>>& points)
{
    ld res = 0;
    ll n = points.size();
    for (ll i = 0; i < n; ++i) {
        ll j = (i + 1) % n;
        res += points[i].first * points[j].second - points[i].second * points[j].first;
    }
    return fabsl(res) / 2;
}
