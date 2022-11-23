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

using S = int;
using F = int;

S op(int a,int b){return min(a,b);}
S e(){return INF;}
S mapping(int f,int x){return min(x,f);}
F composition(int f,int g){return min(f,g);}
F id(){return INF;}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int N,Q;
    cin >> N >> Q;
    set<int> st;
    map<int,int> mp;
    vector<tuple<int,int,int>> xst;
    int s,t,x;
    for (int i=0;i<N;i++){
        cin >> s >> t >> x;
        st.insert(max(s-x,0));
        st.insert(max(t-x,0));
        xst.push_back(make_tuple(x,s,t));
    }
    sort(xst.begin(),xst.end(),greater<tuple<int,int,int>>());
    int d;
    vector<int> query;
    for (int i=0;i<Q;i++){
        cin >> d;
        st.insert(d);
        query.push_back(d);
    }
    int idx = 0;
    for (int x:st){
        mp[x] = idx;
        idx += 1;
    }
    lazy_segtree<S,op,e,F,mapping,composition,id> seg(st.size());
    for (int i=0;i<N;i++){
        tie(x,s,t) = xst[i];
        int l = mp[max(s-x,0)] , r = mp[max(t-x,0)];
        seg.apply(l,r,x);
    }
    //for (int i=0;i<st.size();i++){
    //    cout << seg.get(i) << ' ';
    //}
    //cout << endl;
    for (int i=0;i<Q;i++){
        int d = query[i];
        int ans = seg.get(mp[d]);
        if (ans < INF) cout << ans << endl;
        else cout << -1 << endl;
    }
}