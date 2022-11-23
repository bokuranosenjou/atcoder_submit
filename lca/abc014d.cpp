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

//https://algo-logic.info/lca/
struct LCA{
    vector<vector<int>> doubling; //doubling[k][u]...頂点uからpow(2,k)遡った頂点番号
    vector<int> dist; //dist[u]...頂点uからrootまでの距離
    LCA(const Graph &G , int root = 0){ init(G,root) ;}
    
    void init(const Graph &G , int root = 0){
        int N = G.size();
        int logN = 1;
        while((1<<logN) <= N) logN++;
        doubling.assign(logN,vector<int>(N,-1));
        dist.assign(N,-1);
        dfs(G,root,-1,0);
        for (int k=0;k<logN-1;k++){
            for (int now=0;now<N;now++){
                if (doubling[k][now] < 0) doubling[k+1][now] = -1;
                else doubling[k+1][now] = doubling[k][doubling[k][now]];
            }
        }
    }
    void dfs(const Graph &G, int now, int par , int depth){
        doubling[0][now] = par;
        dist[now] = depth;
        for(auto nxt : G[now]){
            if (nxt == par) continue;
            dfs(G,nxt,now,depth+1);
        }
    }
    int query(int u, int v){// 頂点uと頂点vのLCA
        if (dist[u] < dist[v]) swap(u,v);
        int logN = doubling.size();
        //LCAまでの距離を同じにする、O(logN)
        for (int k=0;k<logN;k++){
            if ((dist[u] - dist[v]) >> k & 1){
                u = doubling[k][u];
            }
        }
        if (u == v) return u;
        for (int k=logN-1;k>=0;k--){
            if (doubling[k][u] != doubling[k][v]){
                u = doubling[k][u];
                v = doubling[k][v];
            }
        }
        return doubling[0][u];
    }
    int get_dist(int u,int v){
        return dist[u] + dist[v] - 2 * dist[query(u,v)];
    }
    bool is_on_path(int u,int v, int target){
        return get_dist(u,v) == get_dist(u,target) + get_dist(target,v);
    }
};

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int N; cin >> N;
    Graph g(N);
    rep(i,N-1){
        int x,y; cin >> x >> y;
        g[x-1].push_back(y-1);
        g[y-1].push_back(x-1);
    }
    LCA my_lca(g,0);
    int Q; cin >> Q;
    while(Q--){
        int a,b; cin >> a >> b;
        cout << 1 + my_lca.get_dist(a-1,b-1) << endl;
    }
}