#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>

class PushRelabel {
public:
    int64_t ComputeFlow(std::vector<std::unordered_map<int64_t, int64_t>> capacity) {
        capacity_ = std::move(capacity);
        heights_.assign(capacity_.size(), 0);
        heights_[0] = static_cast<int64_t>(heights_.size());
        excesses_.assign(capacity_.size(), 0);
        excesses_[0] = std::numeric_limits<int64_t>::max() / 2;
        flow_ = std::vector<std::unordered_map<int64_t, int64_t>>(capacity_.size());
        for (const auto &c: capacity_[0]) {
            Push(0, c.first);
        }

        while (!to_do_.empty()) {
            int64_t front = to_do_.front();
            to_do_.pop();
            if (front != 0 && front + 1 != capacity_.size()) {
                Discharge(front);
            }
        }
        int64_t res = 0;
        for (const auto &c: flow_[0]) {
            res += c.second;
        }
        return res;
    }

private:
    void Push(int64_t origin, int64_t dest) {
        int64_t fl = std::min(excesses_[origin], capacity_[origin][dest] - flow_[origin][dest]);
        excesses_[origin] -= fl;
        excesses_[dest] += fl;
        flow_[origin][dest] += fl;
        flow_[dest][origin] -= fl;
        if (fl != 0 && excesses_[dest] == fl) {
            to_do_.push(dest);
        }
    }

    void Relabel(int64_t vertex) {
        int64_t height = std::numeric_limits<int64_t>::max() / 2;
        for (auto [key, value]: capacity_[vertex]) {
            if (value - flow_[vertex][key] > 0) {
                height = std::min(height, heights_[key]);
            }
        }
        heights_[vertex] = height + 1;
    }

    void Discharge(int64_t vertex) {
        while (true) {
            for (auto [key, value]: capacity_[vertex]) {
                if (value - flow_[vertex][key] > 0 && heights_[vertex] > heights_[key]) {
                    Push(vertex, key);
                }
                if (excesses_[vertex] == 0) {
                    return;
                }
            }
            Relabel(vertex);
        }
    }

    std::vector<std::unordered_map<int64_t, int64_t>> capacity_;
    std::vector<int64_t> excesses_;
    std::vector<int64_t> heights_;
    std::queue<int64_t> to_do_;
    std::vector<std::unordered_map<int64_t, int64_t>> flow_;
};
