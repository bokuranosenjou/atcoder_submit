//abc135f
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
    string s,T ; cin >> s >> T;
    string S = "";
    while (S.length() < T.length()) S += s;
    int NS = S.length() , NT = T.length();
    auto z = z_algorithm(T + "S" + S + S);
    //topological_sort
    Graph g(NS);
    vector<int> cnt(NS);
    for (int i=0;i<NS;i++){
        if (z[NT + 1 + i] == NT){
            g[i].push_back((i+NT) % NS);
            cnt[(i+NT)%NS]++;
        }
    }
    queue<int> dq;
    vector<int> dp(NS,-1);
    for (int i=0;i<NS;i++){
        if (cnt[i] == 0){
            dq.push(i);
            dp[i] = 0;
        }
    }
    vector<int> ts;
    while (!dq.empty()){
        int now = dq.front();dq.pop();
        ts.push_back(now);
        for (auto nxt : g[now]){
            cnt[nxt]--;
            if (cnt[nxt] == 0){
                dq.push(nxt);
                chmax(dp[nxt],dp[now] + 1);
            }
        }
    }
    if (ts.size() < NS) cout << -1 << endl;
    else cout << *max_element(all(dp)) << endl;
}