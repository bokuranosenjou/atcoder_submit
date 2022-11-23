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
S op(S a, S b) {return min(a,b);}
S e() {return INF;}
using F = int;
S mapping(F f, S x){return x + f;}
F composition(F f, F g){return f + g;}
F id(){return 0;}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int N,Q;
    cin >> N >> Q;
    string St;
    cin >> St;
    St = "$" + St;
    vector<int> wa(N+1,0);
    for (int i=1;i<=N;i++){
        if (St[i] == '(') wa[i] = wa[i-1] + 1;
        else wa[i] = wa[i-1] - 1;
    }
    lazy_segtree<S,op,e,F,mapping,composition,id> seg(wa);
    while(Q--){
        int flag,l,r;
        cin >> flag >> l >> r;
        if (flag == 1){
            if (St[l] == St[r]) continue;
            if (St[l] == '('){
                seg.apply(l,r,-2);
                swap(St[l],St[r]);
            }
            else{
                seg.apply(l,r,+2);
                swap(St[l],St[r]);
            }
        }
        else{
            if ((seg.get(l-1) == seg.get(r)) && seg.prod(l,r+1) - seg.get(l-1) >= 0) cout << "Yes" << endl;
            else cout << "No" << endl;
        }
    }
}