#ifndef __mylib__
#define __mylib__

#include <iostream>
#include <vector>

#define each(i,a) for (auto&& i : a)
#define FOR(i,a,b) for (int i=(a),__last_##i=(b);i<__last_##i;i++)
#define RFOR(i,a,b) for (int i=(b)-1,__last_##i=(a);i>=__last_##i;i--)
#define REP(i,n) FOR(i,0,n)
#define RREP(i,n) RFOR(i,0,n)
#define __GET_MACRO3(_1, _2, _3, NAME, ...) NAME
#define rep(...) __GET_MACRO3(__VA_ARGS__, FOR, REP)(__VA_ARGS__)
#define rrep(...) __GET_MACRO3(__VA_ARGS__, RFOR, RREP)(__VA_ARGS__)

template<typename T>
std::istream& operator>>(std::istream& is, std::vector<T>& vec) {
    each(x,vec) is >> x;
    return is;
}
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    rep(i,vec.size()) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<T>>& vec) {
    rep(i,vec.size()) {
        if (i) os << std::endl;
        os << vec[i];
    }
    return os;
}
const double eps = 1e-12;

#endif
