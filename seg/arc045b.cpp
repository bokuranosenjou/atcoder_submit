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

int op(int a, int b){ return min(a,b) ;}
int e(){return INF;}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int N,M; cin >> N >> M;
    vector<int> cnt(N+2,0);
    vector<pii> st;
    rep(i,M){
        int s,t; cin >> s >> t;
        cnt[s]++;
        cnt[t+1]--;
        st.push_back(make_pair(s,t));
    }
    for(int i=0;i<=N;i++){
        cnt[i+1] += cnt[i];
    }
    segtree<int,op,e> seg(cnt);
    vector<int> ans;
    for(int i=0;i<M;i++){
        if (seg.prod(st[i].first,st[i].second+1) >= 2){
            ans.push_back(i+1);
        }
    }
    cout << ans.size() << endl;
    for(auto x :ans ) cout << x << endl;
}