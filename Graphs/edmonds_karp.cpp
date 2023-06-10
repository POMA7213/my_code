#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <limits>
#include <queue>

int64_t Compute(const std::vector<std::unordered_map<size_t, int64_t>> &forward) {
    std::vector<std::unordered_map<size_t, int64_t>> backward(forward.size());
    while (!forward.empty()) {
        std::vector<size_t> from(forward.size(), std::numeric_limits<size_t>::max() / 2);
        std::vector<int> half_queue(forward.size());
        from[0] = 0;
        std::queue<size_t> queue;
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
        if (from[forward.size() - 1] == std::numeric_limits<size_t>::max() / 2) {
            break;
        }
        int64_t flow = std::numeric_limits<int64_t>::max();
        size_t cur = forward.size() - 1;
        while (cur != 0) {
            flow = std::min(flow, forward[from[cur]].at(cur) - backward[from[cur]][cur]);
            cur = from[cur];
        }
        cur = static_cast<int>(forward.size() - 1);
        while (cur != 0) {
            backward[from[cur]][cur] += flow;
            backward[cur][from[cur]] -= flow;
            cur = from[cur];
        }
    }
    int64_t res = 0;
    for (auto c: forward[0]) {
        res += backward[0][c.first];
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout << Compute(ParseData(std::cin));
    return 0;
}
