#include <vector>
#include <algorithm>

std::vector<int64_t> ComputeZet(const std::vector<int64_t> &pref) {
    std::vector<int64_t> zet(pref.size(), 0);
    for (size_t i = 1; i < pref.size(); ++i) {
        if (pref[i] != 0) {
            zet[i - pref[i] + 1] = pref[i];
        }
    }

    zet[0] = static_cast<int64_t>(zet.size());
    if (zet[1] != 0) {
        for (int64_t i = 1; i < zet[1]; ++i) {
            zet[i + 1] = zet[1] - i;
        }
    }

    size_t step;
    for (size_t i = zet[1] + 1; i + 1 < zet.size(); ++i) {
        step = i;
        if (zet[i] != 0 && zet[i + 1] == 0) {
            for (size_t j = 1; j < static_cast<size_t>(zet[i]) && zet[i + j] <= zet[j]; ++j) {
                zet[i + j] = std::min(zet[j], zet[i] - static_cast<int64_t>(j));
                step = i + j;
            }
        }
        i = step;
    }
    return zet;
}
