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
const int MOD2 = 1e9+7;
const double PI = acos(-1);
vector<int> di = {1,0,-1,0};
vector<int> dj = {0,1,0,-1};

//https://drken1215.hatenablog.com/entry/2018/06/08/210000
//COMinit()を忘れない!!!
const ll NMAX = 20002000;
const ll MOD = 998244353;

ll fac[NMAX],finv[NMAX],inv[NMAX];

void COMinit(){
    fac[0] = fac[1] = 1LL;
    finv[0] = finv[1] = 1LL;
    inv[1] = 1LL;
    for (int i=2;i<NMAX;i++){
        fac[i] = fac[i-1] * i % MOD;
        inv[i] = MOD - inv[MOD%i] * (MOD/i) % MOD;
        finv[i] = finv[i-1] * inv[i] % MOD;
    }
}

ll cmb(int n,int k){
    if (n<k) return 0LL;
    if (n < 0 || k < 0) return 0LL;
    return fac[n] * (finv[k] * finv[n-k] % MOD) % MOD;
}

using mint = modint998244353;
vector<ll> c = {1,2,3,2,1};
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    COMinit();
    int N,M; cin >> N >> M;
    vector<ll> F(N*2+3,0);
    for(int i=0;i<=N-1;i++){
        ll val = cmb(N-1,i);
        for (int j=0;j<5;j++){
            F[N-1+i+j] = (F[N-1+i+j] + (val * c[j] % MOD)) % MOD;
        }
    }
    vector<ll> G(M+1,0);
    for(int i=0;3*i<=M;i++){
        G[3*i] = cmb(i+N,N);
    }
    ll ans = 0ll;
    for(int i=0;i<=N*2+2;i++){
        if (i <= M){
            ans = (ans + (F[i] * G[M-i]) % MOD) % MOD;
        }
    }
    ans %= MOD;
    cout << ans << endl;
}