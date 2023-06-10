#include <vector>
#include <algorithm>

std::vector<int64_t> ComputePrefix(const std::vector<int64_t> &data) {
    std::vector<int64_t> pref(data.size(), 0);
    size_t pref_index = 1;
    pref[0] = 0;
    for (size_t zet_index = 1; zet_index < data.size(); ++zet_index) {
        if (data[zet_index] != 0) {
            for (size_t i = pref_index; i < zet_index + data[zet_index]; ++i) {
                pref[i] = i - zet_index + 1ul;
            }
        }
        pref_index = std::max(pref_index, zet_index + data[zet_index]);
    }
    return pref;
}
