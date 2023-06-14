#include <vector>
#include <iostream>

std::vector<uint64_t> Sieve(uint64_t number = 10000000) {
    std::vector<bool> visited(number + 1);
    std::vector<uint64_t> res(number + 1);
    for (size_t i = 2; i < number; ++i) {
        while (visited[i]) {
            ++i;
            if (i >= visited.size()) {
                break;
            }
        }
        auto p = i * i;
        while (p <= number) {
            if (!visited[p]) {
                visited[p] = true;
                res[p] = i;
            }
            p += i;
        }
    }
    for (size_t i = 2; i < visited.size(); ++i) {
        if (!visited[i]) {
            res[i] = i;
        }
    }
    return res;
}
