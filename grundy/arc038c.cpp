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

int op(int a,int b){return min(a,b); }
int e(){return INF; }

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int N; cin >> N;
    vector<int> C(N),A(N);
    for(int i=1;i<=N-1;i++){
        cin >> C[i] >> A[i];
        A[i] %= 2;
    }
    segtree<int,op,e> seg(vector<int>(N+5,-1));
    seg.set(0,0);
    int val = 0;
    for (int i=1;i<=N-1;i++){
        int gr = seg.max_right(0,[&](int x){return x >= i - C[i];});
        seg.set(gr,i);
        if (A[i]) val = val ^ gr;
    }
    if (val) cout << "First" << endl;
    else cout << "Second" << endl;
}