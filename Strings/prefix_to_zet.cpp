#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

vector<int64_t> ComputeZet(const vector<int64_t> &pref) {
    vector<int64_t> zet(pref.size(), 0);
    for (ll i = 1; i < pref.size(); ++i) {
        if (pref[i] != 0) {
            zet[i - pref[i] + 1] = pref[i];
        }
    }

    zet[0] = static_cast<int64_t>(zet.size());
    if (zet[1] != 0) {
        for (int64_t i = 1; i < zet[1]; ++i) {
            zet[i + 1] = zet[1] - i;
        }
    }

    ll step;
    for (ll i = zet[1] + 1; i + 1 < zet.size(); ++i) {
        step = i;
        if (zet[i] != 0 && zet[i + 1] == 0) {
            for (ll j = 1; j < static_cast<ll>(zet[i]) && zet[i + j] <= zet[j]; ++j) {
                zet[i + j] = min(zet[j], zet[i] - static_cast<int64_t>(j));
                step = i + j;
            }
        }
        i = step;
    }
    return zet;
}
