#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

bool Interacts(ll lx1, ll ly1, ll lx2, ll ly2, ll bx1, ll by1, ll bx2, ll by2)
{
    ll la = ly2 - ly1, lb = lx1 - lx2, lc = ly1 * lx2 - lx1 * ly2;
    ll ba = by2 - by1, bb = bx1 - bx2, bc = by1 * bx2 - bx1 * by2;
    if (la * bb == lb * ba) {
        if (lc * ba != bc * la || lc * bb != bc * lb) {
            return false;
        }
        return max(ly1, ly2) >= min(by1, by2) && max(by1, by2) >= min(ly1, ly2) && max(lx1, lx2) >= min(bx1, bx2) && max(bx1, bx2) >= min(lx1, lx2);
    } else {
        return (la * bx1 + lb * by1 + lc) * (la * bx2 + lb * by2 + lc) <= 0 && (ba * lx1 + bb * ly1 + bc) * (ba * lx2 + bb * ly2 + bc) <= 0;
    }
}
