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
    int H,W; cin >> H >> W;
    vector<vector<char>> C(H,vector<char>(W));
    int si,sj;
    for (int i=0;i<H;i++){
        for (int j=0;j<W;j++){
            cin >> C[i][j];
            if (C[i][j] == 'S'){
                si = i;
                sj = j;
            }
        }
    }
    int V = H * W;
    mf_graph<int> g(V);
    for (int i=0;i<H;i++){
        for (int j=0;j<W;j++){
            if (C[i][j] == '#') continue;
            for (int idx=0;idx<4;idx++){
                int ni = i + di[idx], nj = j + dj[idx];
                if (ni < 0 || ni >= H || nj < 0 || nj >= W)continue;
                if (C[ni][nj] == '#') continue;
                g.add_edge(i * W + j , ni * W + nj ,1);
            }
        }
    }
    for (int idx = 0;idx < 4;idx++){
        int ti = si + di[idx] , tj = sj + dj[idx];
        if (ti < 0 || ti >= H || tj < 0 || tj >= W)continue;
        if (C[ti][tj] == '#') continue;
        auto f = g.flow(si * W + sj , ti * W + tj);
        if (f >= 2){
            cout << "Yes" << endl;
            exit(0);
        }
    }
    cout << "No" << endl;
}