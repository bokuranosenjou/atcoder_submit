//LCA with Euler tour
//https://qiita.com/recuraki/items/72e37eb9be9f71bc623a#%E4%BB%BB%E6%84%8F%E3%81%AE%EF%BC%92%E7%82%B9%E9%96%93%E3%81%AE%E8%B7%9D%E9%9B%A2
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

const int N_MAX = 101010;
int visited[2*N_MAX];
int vcost1[2*N_MAX];
int vcost2[2*N_MAX];
int ecost1[2*N_MAX];
int ecost2[2*N_MAX];
int depth[2*N_MAX];
int discovery[N_MAX];
int finishing[N_MAX];
int ivisit[N_MAX];

struct Edge{
    int to;
    ll cost;
};
using Graph = vector<vector<Edge>>;

pii op1(pii a, pii b){
    if (a.first < b.first) return a;
    else return b;
}
pii e1(){
    return make_pair(INF,-1);
}
int op2(int a , int b){
    return a + b;
}
int e2(){
    return 0;
}

void dfs(Graph &G , int now, int par , int dep , int &cnt){
    visited[cnt] = now;
    depth[cnt] = dep;
    cnt++;
    for(auto edge : G[now]){
        int nxt = edge.to , c = edge.cost;
        if (nxt == par)continue;
        ecost2[cnt] = c;
        dfs(G , nxt ,now , dep+1 ,cnt);
        ecost2[cnt] = -c;
        visited[cnt] = now;
        depth[cnt] = dep;
        cnt++;
    }
}
void init_dis_fin(int N){
    for (int i=0;i<2*N-1;i++){
        int v = visited[i];
        if (ivisit[v] == 0){
            discovery[v] = i;
            ivisit[v] = 1;
        }
        finishing[v] = i+1;
    }
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int N; cin >> N;
    Graph g(N);
    rep(i,N-1){
        int x,y; cin >> x >> y;
        x--;
        y--;
        g[x].push_back(Edge{y,1LL});
        g[y].push_back(Edge{x,1LL});
    }
    int cnt = 0;
    dfs(g,0,-1,0,cnt);
    init_dis_fin(N);
    //LCA用
    segtree<pii,op1,e1> seg1(2*N);//最小値の頂点番号を返す
    rep(i,2*N-1) seg1.set(i,make_pair(depth[i],visited[i]));
    //距離用
    segtree<int,op2,e2> seg2(2*N);//距離の和を返す
    rep(i,2*N-1) seg2.set(i,ecost2[i]);
    int Q; cin >> Q;
    while(Q--){
        int x,y; cin >> x >> y;
        x--;
        y--;
        int l = min(discovery[x],discovery[y]);
        int r = max(finishing[x],finishing[y]);
        int lca = seg1.prod(l,r).second;
        int dist_x = seg2.prod(1,discovery[x]+1);
        int dist_y = seg2.prod(1,discovery[y]+1);
        int dist_lca = seg2.prod(1,discovery[lca]+1);
        cout << dist_x + dist_y - 2 * dist_lca + 1<< endl;
    }
}