#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

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

multiset<ll> MS;

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int Q,flag,k,boo;
    ll x;
    cin >> Q;
    while(Q--){
        cin >> flag;
        if (flag == 1){
            cin >> x;
            MS.insert(x);
        }
        else if(flag == 2){
            ll ans=0;
            cin >> x;
            cin >> k;
            auto iter = MS.upper_bound(x);
            rep(i,k){
                if (iter == MS.begin()){
                    ans = -1LL;
                    break;
                }
                else{
                    iter--;
                    ans = *iter;
                }
            }
            cout << ans << endl;
        }
        else if (flag == 3){
            ll ans = 0;
            cin >> x;
            cin >> k;
            auto iter = MS.lower_bound(x);
            rep(i,k){
                if (iter == MS.end()){
                    ans = -1LL;
                    break;
                }
                else{
                    ans = *iter;
                    iter++;
                }
            }
            cout << ans << endl;;
        }
    }
}