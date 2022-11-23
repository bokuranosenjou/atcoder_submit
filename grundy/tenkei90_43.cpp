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

int getgrundy(vector<vector<int>> &grundy,int w, int b){
    if (grundy[w][b] != -1) return grundy[w][b];
    set<int> st;
    if (w >= 1){
        st.insert(getgrundy(grundy,w-1,b+w));
    }
    if (b >= 2){
        for (int k=1;k<=(b/2);k++){
            st.insert(getgrundy(grundy,w,b-k));
        }
    }
    int num = 0;
    while(st.count(num))num++;
    grundy[w][b] = num;
    return num;
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    vector<vector<int>> grundy(51,vector<int>(2551,-1));
    grundy[0][0] = 0;
    grundy[0][1] = 0;
    //
    int N; cin >> N;
    vector<int> W(N),B(N);
    rep(i,N) cin >> W[i];
    rep(i,N) cin >> B[i];
    int val = 0;
    for(int i=0;i<N;i++){
        val = val ^ getgrundy(grundy,W[i],B[i]);
    }
    if (val) cout << "First" << endl;
    else cout << "Second" << endl;
}