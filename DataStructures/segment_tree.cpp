#include <iostream>
#include <vector>

class SegmentTree {
public:
    explicit SegmentTree(const std::vector<int64_t> &arr) : arr_(arr) {
        tree_sum_.assign(4 * arr.size() + 4, 0);
        tree_min_.assign(4 * arr.size() + 4, 0);
        tree_max_.assign(4 * arr.size() + 4, 0);
        DoBuild(arr, tree_sum_, 1, 0, arr.size(), [](int64_t a, int64_t b) {
            return a + b;
        });
        DoBuild(arr, tree_min_, 1, 0, arr.size(), [](int64_t a, int64_t b) {
            return std::min(a, b);
        });
        DoBuild(arr, tree_max_, 1, 0, arr.size(), [](int64_t a, int64_t b) {
            return std::max(a, b);
        });
    }

    int64_t FindMin(size_t l, size_t r) {
        return DoFind(tree_min_, 1, 0, arr_.size(), l, r, [](int64_t a, int64_t b) {
            return std::min(a, b);
        });
    }

    int64_t FindMax(size_t l, size_t r) {
        return DoFind(tree_max_, 1, 0, arr_.size(), l, r, [](int64_t a, int64_t b) {
            return std::max(a, b);
        });
    }

    int64_t FindSum(size_t l, size_t r) {
        return DoFind(tree_sum_, 1, 0, arr_.size(), l, r, [](int64_t a, int64_t b) {
            return a + b;
        });
    }

    void AddSegment(size_t left, size_t right, int64_t value) {
        DoAdd(tree_sum_, 1, 0, arr_.size(), left, right, value, [](int64_t a, int64_t b) {
            return a + b;
        });
        DoAdd(tree_max_, 1, 0, arr_.size(), left, right, value, [](int64_t a, int64_t b) {
            return std::max(a, b);
        });
        DoAdd(tree_min_, 1, 0, arr_.size(), left, right, value, [](int64_t a, int64_t b) {
            return std::min(a, b);
        });
        for (size_t i = left; i < right; ++i) {
            arr_[i] += value;
        }
    }

    void SetValue(size_t index, int64_t value) {
        AddSegment(index, index + 1, value - arr_[index]);
    }

private:

    template<class Func>
    static void
    DoBuild(const std::vector<int64_t> &arr, std::vector<int64_t> &res, size_t ver, size_t l, size_t r, Func func) {
        if (r - l == 1) {
            res[ver] = arr[l];
        } else {
            size_t med = (r + l) / 2;
            DoBuild(arr, res, 2 * ver, l, med, func);
            DoBuild(arr, res, 2 * ver + 1, med, r, func);
            res[ver] = func(res[ver * 2], res[ver * 2 + 1]);
        }
    }

    template<class Func>
    static int64_t
    DoFind(const std::vector<int64_t> &tree, size_t ver, size_t l, size_t r, size_t il, size_t ir, Func func) {
        if (l == il && r == ir) {
            return tree[ver];
        }
        auto med = (r + l) / 2;
        if (ir <= med) {
            return DoFind(tree, 2 * ver, l, med, il, ir, func);
        }
        if (il >= med) {
            return DoFind(tree, 2 * ver + 1, med, r, il, ir, func);
        }
        return func(DoFind(tree, 2 * ver, l, med, il, med, func), DoFind(tree, 2 * ver + 1, med, r, med, ir, func));
    }

    template<class Func>
    static void
    DoAdd(std::vector<int64_t> &tree, size_t ver, size_t l, size_t r, size_t il, size_t ir, int64_t value, Func func) {
        if (r - l == 1) {
            tree[ver] += value;
            return;
        }
        auto med = (r + l) / 2;
        if (il < med) {
            DoAdd<Func>(tree, 2 * ver, l, med, il, ir, value, func);
        }
        if (ir > med) {
            DoAdd<Func>(tree, 2 * ver + 1, med, r, il, ir, value, func);
        }
        tree[ver] = func(tree[ver * 2], tree[ver * 2 + 1]);
    }

    std::vector<int64_t> tree_sum_;
    std::vector<int64_t> tree_min_;
    std::vector<int64_t> tree_max_;
    std::vector<int64_t> arr_;
};
