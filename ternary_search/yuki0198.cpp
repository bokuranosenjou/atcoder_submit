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

ll B;
int N;
vector<ll> C;

pair<ll,bool> f(ll x){
    ll res = B;
    ll cnt = 0;
    for(int i=0;i<N;i++){
        cnt += abs(x - C[i]);
        if (x > C[i]) res -= (x - C[i]);
        else res += (C[i]-x);
    }
    if (res >= 0) return make_pair(cnt,true);
    else return make_pair(cnt,false);
}


int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    cin >> B >> N;
    C.resize(N);
    rep(i,N) cin >> C[i];
    ll l = -1ll, r = 1ll<<30;
    while( abs(l-r) > 3){
        ll t1 = (2ll*l + r) / 3ll;
        ll t2 = (l + 2ll*r) / 3ll;
        if (f(t1).second == false && f(t2).second == false){
            if (f(t1).first < f(t2).first) r = t2;
            else l = t1;
        }
        else if (f(t1).second == true && f(t2).second == false){
            r = t2;
        }
        else if (f(t1).second == false && f(t2).second == true){
            l = t1;
        }
        else{
            if (f(t1).first < f(t2).first) r = t2;
            else l = t1;
        }
    }
    ll ans = LINF;
    for(int i=l;i<=r;i++){
        if (f(i).second == false)continue;
        chmin(ans,f(i).first);
    }
    cout << ans << endl;
}