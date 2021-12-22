#include <bits/stdc++.h>
using Int = int;  // clang-format off
using pii = std::pair<Int, Int>;
#define REP_(i, a_, b_, a, b, ...) for (Int i = (a), lim##i = (b); i < lim##i; i++)
#define REP(i, ...) REP_(i, __VA_ARGS__, __VA_ARGS__, 0, __VA_ARGS__)
#define RREP_(i, a_, b_, a, b, ...) for (Int i = Int(b) - 1, low##i = (a); i >= low##i; i--)
#define RREP(i, ...) RREP_(i, __VA_ARGS__, __VA_ARGS__, 0, __VA_ARGS__)
#define ALL(v) std::begin(v), std::end(v)
#define RALL(v) std::rbegin(v), std::rend(v)
struct SetupIO { SetupIO() { std::cin.tie(nullptr), std::ios::sync_with_stdio(false), std::cout << std::fixed << std::setprecision(13); } } setup_io;
#ifndef dump
#define dump(...)
#endif  // clang-format on
struct in {
    int n;
    in() {}
    in(int n_) : n(n_){};
    template <class T> operator T() {
        T ret;
        std::cin >> ret;
        return ret;
    }
    template <class T> operator std::vector<T>() {
        std::vector<T> ret(n);
        for (int i = 0; i < n; i++) std::cin >> ret[i];
        return ret;
    }
};
void out() { std::cout << std::endl; }
template <class Head, class... Tail> void out(Head&& h, Tail&&... t) {
    std::cout << h << (sizeof...(Tail) == 0 ? "" : " "), out(std::forward<Tail>(t)...);
}
template <class T> bool chmin(T& a, const T& b) { return a > b ? a = b, true : false; }
template <class T> bool chmax(T& a, const T& b) { return a < b ? a = b, true : false; }
template <class T> using V = std::vector<T>;

/**
 *    author:  knshnb
 *    created: Sun Dec 12 15:57:46 JST 2021
 **/

struct UnionFind {
    std::vector<int> number;  // 0以上のとき親のindex, 負のときは集合サイズ
    UnionFind(int n) : number(n, -1) {}
    int root(int x) { return number[x] < 0 ? x : number[x] = root(number[x]); }
    void unite(int x, int y) {
        x = root(x), y = root(y);
        if (x == y) return;
        if (number[y] < number[x]) std::swap(x, y);
        // yをxにマージ
        number[x] += number[y];
        number[y] = x;
    }
    bool is_same(int x, int y) { return root(x) == root(y); }
    int size(int x) { return -number[root(x)]; }
};

std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
Int rnd_from(Int low, Int high) {  // [low, high)
    return low + rnd() % (high - low);
}

constexpr Int n = 400, m = 1995;
Int X[n], Y[n];
pii es[m];
Int e_ds[m];
constexpr Int n_sample = 170;
using Edge = std::tuple<Int, Int, Int, Int>;  // {dist, u, v, id}
Edge rand_dists[n_sample][m];

signed main() {
    REP(v, n) X[v] = in(), Y[v] = in();
    REP(i, m) {
        Int u = in(), v = in();
        es[i] = {u, v};
    }
    auto exp_dist = [&](Int u, Int v) -> Int {
        Int dx = X[u] - X[v], dy = Y[u] - Y[v];
        return sqrt(dx * dx + dy * dy);
    };
    REP(i, m) e_ds[i] = exp_dist(es[i].first, es[i].second);
    REP(sample, n_sample) {
        REP(i, m) {
            // Int dist = rnd_from(e_ds[i], e_ds[i] * 3 + 1);
            // Int dist = rnd_from(e_ds[i] * 106 / 100, e_ds[i] * 3 * 106 / 100 + 1);
            Int dist = rnd_from(e_ds[i] * 113 / 100, e_ds[i] * 287 / 100 + 1);
            rand_dists[sample][i] = {dist, es[i].first, es[i].second, i};
        }
        std::sort(ALL(rand_dists[sample]));
    }

    UnionFind global_uf(n);
    REP(step, m) {
        Int d = in();
        Int s = global_uf.root(es[step].first), t = global_uf.root(es[step].second);
        if (global_uf.is_same(s, t)) {
            out(0);
            continue;
        }
        Int sum = 0;
        REP(sample, n_sample) {
            auto uf = global_uf;
            for (auto& [dist, u, v, id] : rand_dists[sample]) {
                if (id <= step || uf.is_same(u, v)) continue;
                uf.unite(u, v);
                if (uf.is_same(s, t)) {
                    sum += dist - d;
                    break;
                }
            }
            if (!uf.is_same(s, t)) {
                sum = 1e9;
                break;
            }
        }
        bool use = sum >= 0;
        out(use);
        if (use) global_uf.unite(s, t);
    }
}
