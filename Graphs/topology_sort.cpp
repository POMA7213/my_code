#include <queue>
#include <vector>
#include <unordered_set>
#include <algorithm>

std::vector<std::unordered_set<size_t>> ComputeIn(const std::vector<std::unordered_set<size_t>> &out) {
    std::vector<std::unordered_set<size_t>> in(out.size());
    for (size_t i = 0; i < out.size(); ++i) {
        for (size_t c: out[i]) {
            in[c].emplace(i);
        }
    }
    return in;
}

std::vector<size_t>
TopologySort(std::vector<std::unordered_set<size_t>> out) {
    auto in= ComputeIn(out);
    std::queue<size_t> queue;
    std::vector<size_t> res;
    for (size_t i = 0; i < in.size(); ++i) {
        if (in[i].empty()) {
            queue.emplace(i);
        }
    }
    while (!queue.empty()) {
        size_t top = queue.front();
        queue.pop();
        res.push_back(top);
        for (size_t vertex: out[top]) {
            in[vertex].erase(top);
            if (in[vertex].empty()) {
                queue.emplace(vertex);
            }
        }
    }
    return res;
}
