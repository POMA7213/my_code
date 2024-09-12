#include <vector>
#include <cmath>

using namespace std;

typedef long long ll;

class RMQ {
public:
    RMQ(const vector<ll> &lcp) {
        rmq_.push_back(lcp);
        ll deg = 1;
        while (deg * 2 <= lcp.size()) {
            vector<ll> cur;
            for (ll i = 0; i + deg < rmq_.back().size(); i++) {
                cur.push_back(min(rmq_.back()[i], rmq_.back()[i + deg]));
            }
            rmq_.push_back(cur);
            deg *= 2;
        }
    }

    ll FindMin(ll i, ll j) {
        auto index = TwoDeg(j - i + 1);
        return min(rmq_[index][i], rmq_[index][j - (1 << index) + 1]);
    }

private:
    static ll TwoDeg(ll n) {
        return static_cast<ll>(floor(log2(static_cast<double>(n))));
    }

    vector<vector<ll>> rmq_;
};
