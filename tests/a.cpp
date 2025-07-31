int foo(int n, int k, int budget, std::vector<std::vector<int>> composition, std::vector<int> stock, std::vector<int> cost) {
    auto check = [&](auto kth, auto m) {
        std::vector<int> need(stock.size());
        for (auto i = 0; i < composition[k].size(); ++i) {
            need[i] = composition[k][i] * m;
        }
        auto total = 0;
        for (auto i = 0; i < need.size(); ++i) {
            total += std::max(0, need[i] - stock[i]) * cost[i];
        }
        return total <= budget;
    };

    auto get = [&](auto kth) {
        auto lo = 0, hi = std::numeric_limits<int>::max() / 2;
        while (lo < hi) {
            auto mid = (lo + hi) / 2;
            if (check(kth, mid)) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }

        return lo;
    };

    auto ans = 0;
    for (int i = 0; i < k; ++i) {
        ans = std::max(ans, get(i));
    }

    return ans;
}
