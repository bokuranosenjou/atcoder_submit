#include <bits/stdc++.h>
using namespace std;

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

struct RollingHash{
    ll base1 = 1000007;
    ll base2 = 10000007;
    ll mod1 = 1000000007;
    ll mod2 = 1000000009;
    int N;
    vector<ll> hash1,hash2,pow1,pow2;
    RollingHash(string &S){init(S);}
    void init(string &S){
        int N = S.size();
        hash1.assign(N+1,0ll);
        hash2.assign(N+1,0ll);
        pow1.assign(N+1,1ll);
        pow2.assign(N+1,1ll);
        for(int i=0;i<N;i++){
            hash1[i+1] = (hash1[i] * base1 % mod1 + S[i]) % mod1;
            hash2[i+1] = (hash2[i] * base2 % mod2 + S[i]) % mod2;
            pow1[i+1] = pow1[i] * base1 % mod1;
            pow2[i+1] = pow2[i] * base2 % mod2;
        }
    }
    pll get(int l, int r){
        ll res1 = (hash1[r] - (hash1[l] * pow1[r-l]) % mod1 + mod1) % mod1; 
        ll res2 = (hash2[r] - (hash2[l] * pow2[r-l]) % mod2 + mod2) % mod2; 
        return make_pair(res1,res2);
    }
    int LCP(int l1, int r1, int l2, int r2){
        //[l1,r1)と[l2,r2)のLCPを返す,O(logN)
        int len = min(r1-l1,r2-l2);
        int ok = -1, ng = len+1;
        while(abs(ok - ng) > 1){
            int mid = (ok+ng)/2;
            if (get(l1,l1+mid) == get(l2,l2+mid)) ok = mid;
            else ng = mid;
        }
        return ok;
    }
};

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    string t; cin >> t;
    string p; cin >> p;
    int N = t.size(), M = p.size();
    RollingHash rht(t), rhp(p);
    for (int l=0;l<N;l++){
        int r = M + l;
        if (r > N) break;
        if (rht.get(l,r) == rhp.get(0,M))cout << l << endl;
    }
}