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
    const double inf = numeric_limits<double>::infinity();
    vector<vector<double>> dp(1LL<<n, vector<double>(n, inf));
    dp[1][0] = 0;
    rep(i, 1LL<<n) rep(j, n) {
        if (dp[i][j] == inf) continue;
        rep(k, n) {
            if (i>>k & 1) continue;
            chmin(dp[i|(1LL<<k)][k], dp[i][j] + dist[j][k]);
        }
    }
    double ans = inf;
    rep(i, n) {
        chmin(ans, dp[(1LL<<n)-1][i] + dist[i][0]);
    }
    cout << ans << endl;
}
