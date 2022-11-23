//event_sort
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

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int N,Q; cin >> N >> Q;
    vector<tuple<int,int,int>> events;
    rep(i,N){
        int s,t,x;
        cin >> s >> t >> x;
        events.push_back(make_tuple(s-x,1,x));
        events.push_back(make_tuple(t-x,2,x));
    }
    vector<int> query(Q);
    rep(i,Q){
        int d;cin >> d;
        query[i] = d;
        events.push_back(make_tuple(d,3,i));
    }
    sort(all(events));
    multiset<int> ms;
    vector<int> ans(Q,-1);
    for (int i=0;i<Q+2*N;i++){
        int time,flag,val;
        tie(time,flag,val) = events[i];
        //cout << time << ' ' << flag << ' ' << val << endl;
        if (flag == 1){
            ms.insert(val);
        }
        else if (flag == 2){
            ms.erase(ms.find(val));
        }
        else{
            if (ms.empty()) {
                ans[val] = -1;
            }
            else{
                ans[val] = *ms.begin();
            }
        }
    }
    rep(i,Q) cout << ans[i] << endl;
}