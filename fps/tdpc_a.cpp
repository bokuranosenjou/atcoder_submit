#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
istream &operator>>(istream &is, modint &a) { long long v; is >> v; a = v; return is; }
ostream &operator<<(ostream &os, const modint &a) { return os << a.val(); }
istream &operator>>(istream &is, modint998244353 &a) { long long v; is >> v; a = v; return is; }
ostream &operator<<(ostream &os, const modint998244353 &a) { return os << a.val(); }
istream &operator>>(istream &is, modint1000000007 &a) { long long v; is >> v; a = v; return is; }
ostream &operator<<(ostream &os, const modint1000000007 &a) { return os << a.val(); } 

typedef long long ll;
typedef vector<vector<int>> Graph;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define rep(i,n) for (int i = 0;i < (int)(n); i++)
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define my_sort(x) sort(x.begin(), x.end())
#define my_max(x) *max_element(all(x))
#define my_min(x) *min_element(all(x))
#define cout_vector(x) rep(i,x.size()) cout << x[i] << ' ';
template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }
const int INF = (1<<30) - 1;
const ll LINF = (1LL<<62) - 1;
const int MOD = 998244353;
const int MOD2 = 1e9+7;
const double PI = acos(-1);
vector<int> di = {1,0,-1,0};
vector<int> dj = {0,1,0,-1};

typedef long long ll;
typedef pair<int,int> pii;
//形式的冪級数
 
#define rep2(i, m, n) for (int i = (m); i < (n); ++i)
#define drep2(i, m, n) for (int i = (m)-1; i >= (n); --i)
#define drep(i, n) drep2(i, n, 0)
 
template<class T>
struct FormalPowerSeries : vector<T> {
  using vector<T>::vector;
  using vector<T>::operator=;
  using F = FormalPowerSeries;
 
  F operator-() const {
    F res(*this);
    for (auto &e : res) e = -e;
    return res;
  }
  F &operator*=(const T &g) {
    for (auto &e : *this) e *= g;
    return *this;
  }
  F &operator/=(const T &g) {
    assert(g != T(0));
    *this *= g.inv();
    return *this;
  }
  F &operator+=(const F &g) {
    int n = (*this).size(), m = g.size();
    rep(i, min(n, m)) (*this)[i] += g[i];
    return *this;
  }
  F &operator-=(const F &g) {
    int n = (*this).size(), m = g.size();
    rep(i, min(n, m)) (*this)[i] -= g[i];
    return *this;
  }
  F &operator<<=(const int d) {
    int n = (*this).size();
    (*this).insert((*this).begin(), d, 0);
    (*this).resize(n);
    return *this;
  }
  F &operator>>=(const int d) {
    int n = (*this).size();
    (*this).erase((*this).begin(), (*this).begin() + min(n, d));
    (*this).resize(n);
    return *this;
  }
  F inv(int d = -1) const {
    int n = (*this).size();
    assert(n != 0 && (*this)[0] != 0);
    if (d == -1) d = n;
    assert(d > 0);
    F res{(*this)[0].inv()};
    while (res.size() < d) {
      int m = size(res);
      F f(begin(*this), begin(*this) + min(n, 2*m));
      F r(res);
      f.resize(2*m), internal::butterfly(f);
      r.resize(2*m), internal::butterfly(r);
      rep(i, 2*m) f[i] *= r[i];
      internal::butterfly_inv(f);
      f.erase(f.begin(), f.begin() + m);
      f.resize(2*m), internal::butterfly(f);
      rep(i, 2*m) f[i] *= r[i];
      internal::butterfly_inv(f);
      T iz = T(2*m).inv(); iz *= -iz;
      rep(i, m) f[i] *= iz;
      res.insert(res.end(), f.begin(), f.begin() + m);
    }
    return {res.begin(), res.begin() + d};
  }
 
  // fast: FMT-friendly modulus only
  F &operator*=(const F &g) {
    int n = (*this).size();
    *this = convolution(*this, g);
    (*this).resize(n);
    return *this;
  }
  F &operator/=(const F &g) {
    int n = (*this).size();
    *this = convolution(*this, g.inv(n));
    (*this).resize(n);
    return *this;
  }
 
  // // naive
  // F &operator*=(const F &g) {
  //   int n = (*this).size(), m = g.size();
  //   drep(i, n) {
  //     (*this)[i] *= g[0];
  //     rep2(j, 1, min(i+1, m)) (*this)[i] += (*this)[i-j] * g[j];
  //   }
  //   return *this;
  // }
  // F &operator/=(const F &g) {
  //   assert(g[0] != T(0));
  //   T ig0 = g[0].inv();
  //   int n = (*this).size(), m = g.size();
  //   rep(i, n) {
  //     rep2(j, 1, min(i+1, m)) (*this)[i] -= (*this)[i-j] * g[j];
  //     (*this)[i] *= ig0;
  //   }
  //   return *this;
  // }
 
  // sparse
  F &operator*=(vector<pair<int, T>> g) {
    int n = (*this).size();
    auto [d, c] = g.front();
    if (d == 0) g.erase(g.begin());
    else c = 0;
    drep(i, n) {
      (*this)[i] *= c;
      for (auto &[j, b] : g) {
        if (j > i) break;
        (*this)[i] += (*this)[i-j] * b;
      }
    }
    return *this;
  }
  F &operator/=(vector<pair<int, T>> g) {
    int n = (*this).size();
    auto [d, c] = g.front();
    assert(d == 0 && c != T(0));
    T ic = c.inv();
    g.erase(g.begin());
    rep(i, n) {
      for (auto &[j, b] : g) {
        if (j > i) break;
        (*this)[i] -= (*this)[i-j] * b;
      }
      (*this)[i] *= ic;
    }
    return *this;
  }
 
  // multiply and divide (1 + cz^d)
  void multiply(const int d, const T c) { 
    int n = (*this).size();
    if (c == T(1)) drep(i, n-d) (*this)[i+d] += (*this)[i];
    else if (c == T(-1)) drep(i, n-d) (*this)[i+d] -= (*this)[i];
    else drep(i, n-d) (*this)[i+d] += (*this)[i] * c;
  }
  void divide(const int d, const T c) {
    int n = (*this).size();
    if (c == T(1)) rep(i, n-d) (*this)[i+d] -= (*this)[i];
    else if (c == T(-1)) rep(i, n-d) (*this)[i+d] += (*this)[i];
    else rep(i, n-d) (*this)[i+d] -= (*this)[i] * c;
  }
 
  T eval(const T &a) const {
    T x(1), res(0);
    for (auto e : *this) res += e * x, x *= a;
    return res;
  }
 
  F operator*(const T &g) const { return F(*this) *= g; }
  F operator/(const T &g) const { return F(*this) /= g; }
  F operator+(const F &g) const { return F(*this) += g; }
  F operator-(const F &g) const { return F(*this) -= g; }
  F operator<<(const int d) const { return F(*this) <<= d; }
  F operator>>(const int d) const { return F(*this) >>= d; }
  F operator*(const F &g) const { return F(*this) *= g; }
  F operator/(const F &g) const { return F(*this) /= g; }
  F operator*(vector<pair<int, T>> g) const { return F(*this) *= g; }
  F operator/(vector<pair<int, T>> g) const { return F(*this) /= g; }
};
 
using mint = modint998244353;
using fps = FormalPowerSeries<mint>;
using sfps = vector<pair<int, mint>>;

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int N; cin >> N;
    vector<int> p(N);
    rep(i,N) cin >> p[i];
    //https://atcoder.jp/contests/tdpc/submissions/21434993
    fps F(10001,0);
    F[0] = 1;
    for (auto x : p){
        sfps fi = {{0,1},{x,1}};
        F *= fi;
    }
    int ans = 0;
    for(int i=0;i<=10000;i++){
        if (F[i].val()) ans++;
    }
    cout << ans << endl;
}