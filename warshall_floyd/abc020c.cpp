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

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int N,M;
    cin >> N >> M;
    vector<vector<ll>> dist(N,vector<ll>(N,LINF));
    for(int i=0;i<M;i++){
        int s,t;
        ll l;
        cin >> s >> t >> l;
        dist[s-1][t-1] = l;
        dist[t-1][s-1] = l;
    }
    //warshall_floyd
    for(int k=1;k<N;k++){
        for (int i=1;i<N;i++){
            for (int j=1;j<N;j++){
                dist[i][j] = min(dist[i][j] , dist[i][k] + dist[k][j]);
            }
        }
    }
    ll ans = LINF;
    for (int st=1;st<N;st++){
        for (int en=st+1;en<N;en++){
            if (dist[0][st] == LINF || dist[st][en] == LINF || dist[0][en] == LINF) continue;
            chmin(ans , dist[0][st] + dist[st][en] + dist[en][0]);
        }
    }
    if (ans < LINF) cout << ans << endl;
    else cout << -1 << endl;
}