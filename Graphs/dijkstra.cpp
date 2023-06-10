#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <queue>
#include <limits>

struct Comp {
    bool operator()(const std::pair<size_t, size_t> &l, const std::pair<size_t, size_t> &r) const {
        return l.first > r.first;
    }
};

size_t Compute(const std::vector<std::vector<std::pair<size_t, size_t>>> &data) {
    std::priority_queue<std::pair<size_t, size_t>, std::vector<std::pair<size_t, size_t>>, Comp> queue;
    std::vector<bool> visited(data.size(), false);
    std::vector<size_t> dists(data.size(), std::numeric_limits<size_t>::max());
    dists[0] = 0;
    queue.emplace(0, 0);
    while (!queue.empty()) {
        auto top = queue.top();
        queue.pop();
        if(visited[top.second]){
            continue;
        }
        visited[top.second] = true;
        for (auto p: data[top.second]) {
            if (!visited[p.second] && dists[p.second] > dists[top.second] + p.first) {
                queue.emplace(dists[top.second] + p.first, p.second);
                dists[p.second] = dists[top.second] + p.first, p.second;
            }
        }
    }
    return dists.back();
}
