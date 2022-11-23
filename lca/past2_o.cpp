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
typedef pair<int, int> pii;
typedef vector<vector<pii>> Graph;
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

//https://algo-logic.info/lca/
//ABC235E
struct LCA_max_edgecost{
    vector<vector<int>> doubling; //doubling[k][u]...頂点uからpow(2,k)遡った頂点番号
    vector<vector<int>> doubling_max; //doubling_max[k][u]...頂点uからpow(2,k)遡った間の辺の長さの最大
    vector<int> dist; //dist[u]...頂点uからrootまでの距離
    LCA_max_edgecost(const Graph &G , int root = 0){ init(G,root) ;}
    
    void init(const Graph &G , int root = 0){
        int N = G.size();
        int logN = 1;
        while((1<<logN) <= N) logN++;
        doubling.assign(logN,vector<int>(N,-1));
        doubling_max.assign(logN,vector<int>(N,-1));
        dist.assign(N,-1);;
        dfs(G,root,-1,0);
        for (int k=0;k<logN-1;k++){
            for (int now=0;now<N;now++){
                if (doubling[k][now] < 0){
                    doubling[k+1][now] = -1;
                }
                else {
                    doubling[k+1][now] = doubling[k][doubling[k][now]];
                    doubling_max[k+1][now] = max(doubling_max[k][now], doubling_max[k][doubling[k][now]]);
                }
            }
        }
    }
    void dfs(const Graph &G, int now, int par ,int depth){
        doubling[0][now] = par;
        dist[now] = depth;
        for(auto [cost,nxt] : G[now]){
            if (nxt == par) continue;
            doubling_max[0][nxt] = cost;
            dfs(G,nxt,now,depth+1);
        }
    }
    int query(int u, int v){// 頂点uと頂点vのLCA
        if (dist[u] < dist[v]) swap(u,v);
        int logN = doubling.size();
        int res = -1; //costの最大値
        //LCAまでの距離を同じにする、O(logN)
        for (int k=0;k<logN;k++){
            if ((dist[u] - dist[v]) >> k & 1){
                chmax(res,doubling_max[k][u]);
                u = doubling[k][u];
            }
        }
        if (u == v) return res;
        for (int k=logN-1;k>=0;k--){
            if (doubling[k][u] != doubling[k][v]){
                chmax(res,doubling_max[k][u]);
                chmax(res,doubling_max[k][v]);
                u = doubling[k][u];
                v = doubling[k][v];
            }
        }
        chmax(res,doubling_max[0][u]);
        chmax(res,doubling_max[0][v]);
        return res;
    }
};

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int N,M; cin >> N >> M;
    vector<tuple<int,int,int,int>> edges;
    rep(i,M){
        int a,b,c; cin >> a >> b >> c;
        edges.push_back(make_tuple(c,a-1,b-1,i));
    }
    sort(all(edges));
    dsu uf(N);
    Graph g(N);
    ll wa = 0;
    for (auto [c,a,b,i]:edges){
        if (uf.same(a,b)) continue;
        uf.merge(a,b);
        wa += c;
        g[a].push_back(make_pair(c,b));
        g[b].push_back(make_pair(c,a));
    }
    LCA_max_edgecost lca(g,0);
    vector<ll> ans(M);
    for (auto [c,a,b,i]:edges){
        int val = lca.query(a,b);
        if (val > c) ans[i] = wa;
        else ans[i] = wa - val + c;
    }
    rep(i,M) cout << ans[i] << endl;
}