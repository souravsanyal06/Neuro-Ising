#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> P;

#define each(i,a) for (auto&& i : a)
#define FOR(i,a,b) for (ll i=(a),__last_##i=(b);i<__last_##i;i++)
#define RFOR(i,a,b) for (ll i=(b)-1,__last_##i=(a);i>=__last_##i;i--)
#define REP(i,n) FOR(i,0,n)
#define RREP(i,n) RFOR(i,0,n)
#define __GET_MACRO3(_1, _2, _3, NAME, ...) NAME
#define rep(...) __GET_MACRO3(__VA_ARGS__, FOR, REP)(__VA_ARGS__)
#define rrep(...) __GET_MACRO3(__VA_ARGS__, RFOR, RREP)(__VA_ARGS__)
#define pb push_back
#define all(a) (a).begin(),(a).end()
#define chmin(x,v) x = min(x, v)
#define chmax(x,v) x = max(x, v)

const ll linf = 1e18;
const double eps = 1e-12;
const double pi = acos(-1);

template<typename T>
istream& operator>>(istream& is, vector<T>& vec) {
    each(x,vec) is >> x;
    return is;
}
template<typename T>
ostream& operator<<(ostream& os, const vector<T>& vec) {
    rep(i,vec.size()) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}
template<typename T>
ostream& operator<<(ostream& os, const vector< vector<T> >& vec) {
    rep(i,vec.size()) {
        if (i) os << endl;
        os << vec[i];
    }
    return os;
}
class UnionFind {
    vector<ll> par, h, sz;
public:
    UnionFind(ll size) : par(size, 0), h(size, 0), sz(size, 1) {
        rep(i, size) par[i] = i;
    }
    void unite(ll u, ll v) {
        u = root(u), v = root(v);
        if (u == v) return;
        if (h[u] < h[v]) {
            par[u] = v;
            sz[v] += sz[u];
        }
        else {
            par[v] = u;
            sz[u] += sz[v];
        }
        if (h[u] == h[v]) ++h[u];
    }
    ll size(ll v) {
        return sz[root(v)];
    }
    bool isUnited(ll u, ll v) {
        return root(u) == root(v);
    }
    ll root(ll v) {
        if (par[v] == v) return v;
        return par[v] = root(par[v]);
    }
};
struct Edge {
    ll from, to;
    double cost;
};
bool operator<(const Edge& e1, const Edge& e2) {
    return e1.cost < e2.cost;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll n; cin >> n;
    vector<complex<double>> v;
    rep(i, n) {
        double x, y; cin >> x >> y;
        v.emplace_back(x, y);
    }
    vector<vector<double>> dist(n, vector<double>(n));
    rep(i, n) rep(j, n) {
        dist[i][j] = abs(v[i] - v[j]);
    }
    vector<Edge> edges;
    rep(i, n) rep(j, i) {
        edges.pb({i, j, dist[i][j]});
    }
    sort(all(edges));
    UnionFind uf(n);
    vector<vector<ll>> G(n);
    each(e, edges) {
        if (uf.isUnited(e.from, e.to)) continue;
        uf.unite(e.from, e.to);
        G[e.from].pb(e.to);
        G[e.to].pb(e.from);
    }
    vector<ll> order;
    function<void(ll,ll)> dfs = [&](ll v, ll pv) {
        order.pb(v);
        each(to, G[v]) {
            if (to == pv) continue;
            dfs(to, v);
        }
    };
    dfs(0, -1);
    assert(order.size() == n);
    double ans = 0;
    rep(i, n) {
        ans += dist[order[i]][order[(i+1)%n]];
    }
    cout << ans << endl;
}
