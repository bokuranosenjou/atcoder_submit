//https://atcoder.jp/contests/ukuku09/tasks/ukuku09_d
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

int op(int a, int b){
    return max(a,b);
}
int e(){
    return 0;
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int N,Q; cin >> N >> Q;
    string S; cin >> S;
    //https://snuke.hatenablog.com/entry/2014/12/02/235837
    int i = 0, j = 0;
    vector<int> R(N);
    while (i < S.size()) {
        while (i-j >= 0 && i+j < S.size() && S[i-j] == S[i+j]) ++j;
        R[i] = j;
        int k = 1;
        while (i-k >= 0 && k+R[i-k] < j) R[i+k] = R[i-k], ++k;
        i += k; j -= k;
    }
    segtree<int,op,e> seg(R);
    while(Q--){
        int l,r; cin >> l >> r;
        l--;
        r--;
        int ok = 1,ng = (N+1)/2 + 1;
        while(abs(ok - ng) > 1){
            int mid = (ok+ng)/2;
            int ll = l + mid - 1, rr = r - mid + 1;
            if (ll > rr) ng = mid;
            else if (seg.prod(ll,rr+1) >= mid) ok = mid;
            else ng = mid;
        }
        cout << 2 * ok - 1 << endl;
    }
}