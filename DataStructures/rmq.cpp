#include <vector>
#include <cmath>

class RMQ {
public:
    RMQ(const std::vector<size_t> &lcp) {
        rmq_.push_back(lcp);
        size_t deg = 1;
        while (deg * 2 <= lcp.size()) {
            std::vector<size_t> cur;
            for (size_t i = 0; i + deg < rmq_.back().size(); i++) {
                cur.push_back(std::min(rmq_.back()[i], rmq_.back()[i + deg]));
            }
            rmq_.push_back(cur);
            deg *= 2;
        }
    }

    size_t FindMin(size_t i, size_t j) {
        auto index = TwoDeg(j - i + 1);
        return std::min(rmq_[index][i], rmq_[index][j - (1 << index) + 1]);
    }

private:
    static size_t TwoDeg(size_t n) {
        return static_cast<size_t>(floor(log2(static_cast<double>(n))));
    }

    std::vector<std::vector<size_t>> rmq_;
};
