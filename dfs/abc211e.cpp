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

set<vector<string>> check;
vector<int> di = {1,-1,0,0};
vector<int> dj = {0,0,1,-1};
int N,K,ans = 0;

void dfs(vector<string> &S, int cnt){
    if (check.find(S) != check.end()) return;
    check.insert(S);
    if (cnt == 0){
        ans += 1;
        return;
    }
    vector<int> nxt_red;
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            if (S[i][j] == '.'){
                int boo = 0;
                for (int num=0;num<4;num++){
                    int ni = i + di[num];
                    int nj = j + dj[num];
                    if (ni < 0 || ni >= N || nj < 0 || nj >= N) continue;
                    if (S[ni][nj] == 'X') boo = 1;
                }
                if (boo == 1) nxt_red.push_back(i * N + j);
            }
        }
    }
    for (auto rNc:nxt_red){
        S[rNc/N][rNc%N] = 'X';
        dfs(S,cnt-1);
        S[rNc/N][rNc%N] = '.';
    }
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    cin >> N >> K;
    vector<string> S(N);
    for(int i=0;i<N;i++) cin >> S[i];
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            if (S[i][j] == '.'){
                S[i][j] = 'X';
                dfs(S,K-1);
                S[i][j] = '.';
            }
        }
    }
    cout << ans << endl;
}