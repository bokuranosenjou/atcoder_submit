#include <bits/stdc++.h>
//#include <atcoder/all>
using namespace std;
//using namespace atcoder;
//istream &operator>>(istream &is, modint &a) { long long v; is >> v; a = v; return is; }
//ostream &operator<<(ostream &os, const modint &a) { return os << a.val(); }
//istream &operator>>(istream &is, modint998244353 &a) { long long v; is >> v; a = v; return is; }
//ostream &operator<<(ostream &os, const modint998244353 &a) { return os << a.val(); }
//istream &operator>>(istream &is, modint1000000007 &a) { long long v; is >> v; a = v; return is; }
//ostream &operator<<(ostream &os, const modint1000000007 &a) { return os << a.val(); } 

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

struct Edge{
    int to;
    ll cost;
};

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int V,E,r;
    cin >> V >> E >> r;
    vector<vector<Edge>> g(V);
    for(int i=0;i<E;i++){
        int s,t;
        ll d;
        cin >> s >> t >> d;
        g[s].push_back(Edge{t,d});
    }
    vector<ll> dist(V,LINF);
    dist[r] = 0ll;
    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> pq;
    pq.push(make_pair(0ll,r));
    while(!pq.empty()){
        ll time = pq.top().first;
        int now = pq.top().second;
        pq.pop();
        if (time > dist[now]) continue;
        for (auto e:g[now]){
            int nxt = e.to;
            ll c = e.cost;
            if (c + time < dist[nxt]){
                dist[nxt] = c + time;
                pq.push(make_pair(c+time,nxt));
            }
        }
    }
    for(int i=0;i<V;i++){
        if (dist[i] < LINF) cout << dist[i] << endl;
        else cout << "INF" << endl;
    }
}