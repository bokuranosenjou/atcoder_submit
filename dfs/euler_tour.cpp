//aoj_dfs
#include <bits/stdc++.h>
using namespace std;

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

int cnt = 1;
int d[110];
int f[110];

void dfs(Graph &g,int now,int par){
    if (d[now] == 0){
        d[now] = cnt;
        cnt++;
    }
    for (auto nxt : g[now]){
        if (nxt == par) continue;
        if (d[nxt] > 0) continue;
        dfs(g,nxt,now);
    }
    f[now] = cnt;
    cnt++;
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int N; cin >> N;
    Graph g(N);
    rep(i,N){
        int u; cin >> u;
        int k; cin >> k;
        rep(j,k){
            int to; cin >> to;
            g[u-1].push_back(to-1);
        }
    }
    for (int i=0;i<N;i++){
        if (d[i] > 0) continue;
        dfs(g,i,-1);
    }
    rep(i,N){
        cout << i+1 << ' ' << d[i] << ' ' << f[i] << endl;
    }
}