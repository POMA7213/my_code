#include <vector>
#include <string>

std::vector<size_t> ComputePrefix(const std::string &pattern) {
    std::vector<size_t> res(pattern.size());
    for (size_t counter = 1; counter < res.size(); ++counter) {
        size_t cur_pos = counter;
        while (cur_pos != 0) {
            cur_pos = res[cur_pos - 1];
            if (pattern[cur_pos] == pattern[counter]) {
                if (cur_pos == 0) {
                    res[counter] = 1;
                } else {
                    res[counter] = cur_pos + 1;
                }
                break;
            }
        }
    }
    return res;
}
