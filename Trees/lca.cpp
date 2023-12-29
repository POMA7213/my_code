#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

class RMQ {
public:
    RMQ() = default;

    explicit RMQ(const vector<ll> &data, const vector<ll> &weights) : weights_(weights) {
        rmq_.push_back(data);
        ll deg = 1;
        while (deg * 2 <= data.size()) {
            vector<ll> cur;
            for (ll i = 0; i + deg < rmq_.back().size(); i++) {
                cur.push_back(weights[rmq_.back()[i]] <
                              weights[rmq_.back()[i + deg]] ? rmq_.back()[i] : rmq_.back()[i + deg]);
            }
            rmq_.push_back(cur);
            deg *= 2;
        }
    }

    [[nodiscard]] ll FindMin(ll i, ll j) const {
        if (i > j) {
            swap(i, j);
        }
        auto index = TwoDeg(j - i + 1);
        return weights_[rmq_[index][i]] < weights_[rmq_[index][j - (1 << index) + 1]] ?
               rmq_[index][i] : rmq_[index][j - (1 << index) + 1];
    }

private:
    static ll TwoDeg(ll n) {
        return static_cast<ll>(floor(log2(static_cast<double>(n))));
    }

    vector<vector<ll>> rmq_;
    vector<ll> weights_;
};

class Lca {
public:
    explicit Lca(const vector<unordered_set<ll>> &tree, ll root) {
        vector<ll> order;
        vector<ll> height(tree.size());
        vector<bool> visited(tree.size());
        Dfs(tree, root, order, height, 0, visited);
        rmq_ = RMQ(order, height);
        first_.assign(tree.size(), -1);
        for (ll i = 0; i < order.size(); ++i) {
            if (first_[order[i]] == -1) {
                first_[order[i]] = i;
            }
        }
    }

    ll operator()(ll a, ll b) const {
        return rmq_.FindMin(first_[a], first_[b]);
    }

private:

    RMQ rmq_;
    vector<ll> first_;

    void Dfs(const vector<unordered_set<ll>> &tree, ll cur, vector<ll> &order, vector<ll> &height, ll h,
             vector<bool> &visited) {
        height[cur] = h;
        order.push_back(cur);
        visited[cur] = true;
        for (auto c: tree[cur]) {
            if (visited[c]) {
                continue;
            }
            Dfs(tree, c, order, height, h + 1, visited);
            order.push_back(cur);
        }
    }

};
