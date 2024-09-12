#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <limits>
#include <queue>

using namespace std;

typedef long long ll;

ll Compute(const vector<unordered_map<ll, ll>> &forward) {
    vector<unordered_map<ll, ll>> backward(forward.size());
    while (!forward.empty()) {
        vector<ll> from(forward.size(), numeric_limits<ll>::max() / 2);
        vector<int> half_queue(forward.size());
        from[0] = 0;
        queue<ll> queue;
        queue.push(0);
        while (!queue.empty()) {
            auto front = queue.front();
            queue.pop();
            for (auto c: forward[front]) {
                if (from[c.first] > forward.size() && c.second - backward[front][c.first] > 0) {
                    queue.push(c.first);
                    from[c.first] = front;
                }
            }
        }
        if (from[forward.size() - 1] == numeric_limits<ll>::max() / 2) {
            break;
        }
        ll flow = numeric_limits<ll>::max();
        ll cur = forward.size() - 1;
        while (cur != 0) {
            flow = min(flow, forward[from[cur]].at(cur) - backward[from[cur]][cur]);
            cur = from[cur];
        }
        cur = static_cast<int>(forward.size() - 1);
        while (cur != 0) {
            backward[from[cur]][cur] += flow;
            backward[cur][from[cur]] -= flow;
            cur = from[cur];
        }
    }
    ll res = 0;
    for (auto c: forward[0]) {
        res += backward[0][c.first];
    }
    return res;
}
