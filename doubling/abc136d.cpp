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

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    string S; cin >> S;
    int N = S.size();
    // K = pow(10,100)
    // doubling[k][i]...初めiにいた子供がpow(2,k)後にいる座標
    int logK = 400;
    vector<vector<int>> doubling(logK+5,vector<int>(N));
    for (int i=0;i<N;i++){
        if (S[i] == 'R') doubling[0][i] = i+1;
        else doubling[0][i] = i-1;
    }
    for (int k=0;k<logK;k++){
        for (int i=0;i<N;i++){
            doubling[k+1][i] = doubling[k][doubling[k][i]];
        }
    }
    vector<int> ans(N);
    for(int i=0;i<N;i++){
        ans[doubling[logK][i]]++;
    }
    rep(i,N) cout << ans[i] << ' ';cout << endl;
}