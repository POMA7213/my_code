#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ll Random(ll l, ll r){
    return uniform_int_distribution<ll>(l,r)(rng);
}
