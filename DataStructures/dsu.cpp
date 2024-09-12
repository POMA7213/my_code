#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll FindPar(ll n, vector<ll> &parents) {
    if (parents[n] == n) {
        return n;
    }
    return parents[n] = FindPar(parents[n], parents);
}

bool Unite(ll a, ll b, vector<ll> &parents) {
    ll fir = FindPar(a, parents);
    ll sec = FindPar(b, parents);
    bool res = fir == sec;
    parents[sec] = fir;
    return res;
}
