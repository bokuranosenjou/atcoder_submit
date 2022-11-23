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

using mint = modint1000000007;

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    string S; cin >> S;
    int N = S.size();
    vector<vector<int>> nex(N+1, vector<int>(26,N));
    for(int i=N-1;i>=0;i--){
        for(int c=0;c<26;c++){
            nex[i][c] = nex[i+1][c];
        }
        nex[i][S[i]-'a'] = i;
    }
    vector<mint> dp(N+2,0);
    dp[0] = 1;
    for(int i=0;i<N;i++){
        for(int c=0;c<26;c++){
            if (i>0 && nex[i][c] == i){
                dp[nex[i+1][c]+1] += dp[i];
            }
            else{
                dp[nex[i][c]+1] += dp[i];
            }
        }
    }
    mint ans = 0;
    for(int i=1;i<=N;i++)ans += dp[i];
    cout << ans << endl;
}