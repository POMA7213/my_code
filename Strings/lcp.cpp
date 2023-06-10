#include <vector>
#include <string>

std::vector<size_t> ComputeLCP(const std::string &string, const std::vector<size_t> &suff_arr) {
    std::vector<size_t> rk(suff_arr.size());
    for (size_t i = 0; i < suff_arr.size(); i++) {
        rk[suff_arr[i]] = i;
    }

    std::vector<size_t> lcp_rang(suff_arr.size() - 1);
    std::vector<size_t> lcp_pos(suff_arr.size());
    if (rk[0] + 1 == suff_arr.size()) {
        lcp_pos[0] = 0;
    } else {
        size_t l0 = suff_arr[rk[0] + 1];
        for (size_t i = 0; l0 < string.size() && string[l0] == string[i]; i++) {
            l0++;
        }
        lcp_pos[0] = l0 - suff_arr[rk[0] + 1];
    }
    for (size_t counter = 1; counter < suff_arr.size(); counter++) {
        if (rk[counter] + 1 == suff_arr.size()) {
            lcp_pos[counter] = 0;
            continue;
        }
        size_t l = suff_arr[rk[counter] + 1];
        size_t k = counter;
        if (lcp_pos[counter - 1] > 1) {
            l += lcp_pos[counter - 1] - 1;
            k += lcp_pos[counter - 1] - 1;
        }
        while (k < string.size() && l < string.size() && string[k] == string[l]) {
            k++;
            l++;
        }
        lcp_pos[counter] = k - counter;
    }
    for (size_t i = 0; i < lcp_rang.size(); i++) {
        lcp_rang[i] = lcp_pos[suff_arr[i]];
    }
    return lcp_rang;
}
