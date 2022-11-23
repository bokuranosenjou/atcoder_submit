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

int a[202020] , ans[202020];
pii nums[202020];//（前の数,そのidx)
vector<int> lis;

void dfs(Graph &g, int now , int par){
    //lis更新
    auto itr = lower_bound(all(lis),a[now]);
    if(itr == lis.end()){
        nums[now] = make_pair(-1,-1);
        lis.push_back(a[now]);
    }
    else{
        nums[now] = make_pair(*itr,itr - lis.begin());
        *itr = a[now];
    }
    ans[now] = lis.size();
    for (int nxt : g[now]){
        if (nxt == par)continue;
        dfs(g,nxt,now);
    }
    //lis復元
    if (nums[now].second == -1) lis.pop_back();
    else{
        int idx = nums[now].second;
        lis[idx] = nums[now].first;
    }
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int N; cin >> N;
    rep(i,N) cin >> a[i];
    Graph g(N);
    rep(i,N-1){
        int u,v; cin >> u >> v;
        g[u-1].push_back(v-1);
        g[v-1].push_back(u-1);
    }
    nums[0] = make_pair(-1,-1);
    dfs(g,0,-1);
    rep(i,N) cout << ans[i] << endl;
}