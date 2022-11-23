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

//LCA with Euler tour
//https://qiita.com/recuraki/items/72e37eb9be9f71bc623a#%E4%BB%BB%E6%84%8F%E3%81%AE%EF%BC%92%E7%82%B9%E9%96%93%E3%81%AE%E8%B7%9D%E9%9B%A2
//重み付き木の任意のニ頂点の距離が得られる(構築O(NlogN),クエリO(logN))
//頂点や辺のコストは逆元を持つ必要あり
struct Edge{
    int to;
    ll cost;
};
using Graph = vector<vector<Edge>>;
pii op_min_idx(pii a, pii b){
    if (a.first < b.first) return a;
    else return b;
}
pii e_min_idx(){
    return make_pair(INF,-1);
}
ll op_rsq(ll a,ll b){ return a + b; }
ll e_rsq(){ return 0; }
struct Euler_tour{
    int N, cnt = 0;
    vector<int> visited,depth,discovery,finishing,ivisit;
    vector<ll> vcost1,vcost2,ecost1,ecost2,icost;
    segtree<pii,op_min_idx,e_min_idx> seg_min_idx;
    segtree<ll,op_rsq,e_rsq> seg_rsq_e1; 
    segtree<ll,op_rsq,e_rsq> seg_rsq_v1; 
    segtree<ll,op_rsq,e_rsq> seg_rsq_e2; 
    segtree<ll,op_rsq,e_rsq> seg_rsq_v2; 
    Euler_tour(Graph &G, int root = 0){ init(G,root) ;}
    //初期化
    void init(Graph &G , int root = 0){
        int N = G.size();
        visited.assign(2*N,-1);
        depth.assign(2*N,-1);
        discovery.assign(N,-1);
        finishing.assign(N,-1);
        ivisit.assign(N,0); // 訪れたか否か
        icost.assign(N,1LL);//頂点iのコスト
        init_vertex_cost(N);//入力で与えるならグローバル領域に書く
        //LCA用
        seg_min_idx = segtree<pii,op_min_idx,e_min_idx>(2*N);
        //部分木クエリ用
        vcost1.assign(2*N,0LL);
        ecost1.assign(2*N,0LL);
        seg_rsq_v1 = segtree<ll,op_rsq,e_rsq>(2*N); //vcost1
        seg_rsq_e1 = segtree<ll,op_rsq,e_rsq>(2*N); //ecost1
        //パスクエリ用
        vcost2.assign(2*N,-1LL);
        ecost2.assign(2*N,-1LL);
        seg_rsq_v2 = segtree<ll,op_rsq,e_rsq>(2*N); //vcost2
        seg_rsq_e2 = segtree<ll,op_rsq,e_rsq>(2*N); //ecost2
        //////////////////////
        //////Euler_tour//////
        vcost1[root] = icost[root];
        vcost2[root] = icost[root];
        dfs(G,root,-1,0);
        vcost2[2*N-1] = -icost[root];
        init_dis_fin(N);
        //////////////////////
        //////////////////////
        //LCA用
        rep(i,2*N-1) seg_min_idx.set(i,make_pair(depth[i],visited[i]));
        //部分木クエリ用
        rep(i,2*N-1) seg_rsq_e1.set(i,ecost1[i]);
        rep(i,2*N-1) seg_rsq_v1.set(i,vcost1[i]);
        //パスクエリ用
        rep(i,2*N-1) seg_rsq_e2.set(i,ecost2[i]);
        rep(i,2*N-1) seg_rsq_v2.set(i,vcost2[i]);
    }
    void init_vertex_cost(int cnt_v){
        for (int i=0;i<cnt_v;i++){
            //icost[i] = 1; //任意の二頂点間の頂点数の総和を求める
            icost[i] = i + 1;
        }
    }
    void dfs(Graph &G, int now , int par , int dep){
        visited[cnt] = now;
        depth[cnt] = dep;
        cnt++;
        for(auto edge : G[now]){
            int nxt = edge.to , c = edge.cost;
            if (nxt == par)continue;
            vcost1[cnt] = icost[nxt];
            ecost1[cnt] = c;
            vcost2[cnt] = icost[nxt];
            ecost2[cnt] = c;
            dfs(G , nxt ,now , dep+1);
            vcost2[cnt] = -icost[nxt];
            ecost2[cnt] = -c;
            visited[cnt] = now;
            depth[cnt] = dep;
            cnt++;
        }
    }
    void init_dis_fin(int cnt_v){
        for (int i=0;i<2*cnt_v-1;i++){
            int v = visited[i];
            if (ivisit[v] == 0){
                discovery[v] = i;
                ivisit[v] = 1;
            }
            finishing[v] = i+1;
        }
    }
    int get_lca(int x , int y){
        int l = min(discovery[x],discovery[y]);
        int r = max(finishing[x],finishing[y]);
        int lca = seg_min_idx.prod(l,r).second; 
        return lca;
    }
    ll get_ecost1(int v){ //自身含め部分木の辺のコストの総和
        return seg_rsq_e1.prod(discovery[v]+1,finishing[v]);
    }
    ll get_vcost1(int v){ //自身含め部分木の頂点のコストの総和
        return seg_rsq_v1.prod(discovery[v],finishing[v]);
    }
    ll get_ecost2_from_root(int v){
        return seg_rsq_e2.prod(1,discovery[v]+1);
    }
    ll get_ecost2_two(int x, int y){
        int lca = get_lca(x,y);
        return get_ecost2_from_root(x) + get_ecost2_from_root(y) - 2 * get_ecost2_from_root(lca);
    }
    ll get_vcost2_from_root(int v){
        return seg_rsq_v2.prod(0,discovery[v]+1);
    }
    ll get_vcost2_two(int x, int y){
        int lca = get_lca(x,y);
        return get_vcost2_from_root(x) + get_vcost2_from_root(y) - 2 * get_vcost2_from_root(lca) + icost[lca];
    }
};

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    //ABC014D
    int N; cin >> N;
    Graph g(N);
    rep(i,N-1){
        int x,y; cin >> x >> y;
        x--;
        y--;
        g[x].push_back(Edge{y,1LL});
        g[y].push_back(Edge{x,1LL});
    }
    Euler_tour et(g,0);
    int Q; cin >> Q;
    while(Q--){
        int a,b; cin >> a >> b;
        cout << et.get_ecost2_two(a-1,b-1) + 1 << endl;
    }
}