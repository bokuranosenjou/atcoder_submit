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

struct Eratosthenes{
    int N;
    vector<bool> isprime;
    vector<int> minfactor, mobius;
    Eratosthenes(int N_max = 1e7){init(N_max);}
    //初期化
    void init(int N_max = 1e7){
        int N = N_max;
        isprime.assign(N+1,true);
        minfactor.assign(N+1,-1);
        mobius.assign(N+1,1);
        //Eratosthenes O(NloglogN)
        isprime[0] = false;
        isprime[1] = false;
        for(int p=2;p<=N;p++){
            if (!isprime[p])continue;
            minfactor[p] = p;
            mobius[p] = -1;
            //pの倍数の処理
            for(int q=2*p;q<=N;q+=p){
                isprime[q] = false;
                if (minfactor[q] == -1){
                    minfactor[q] = p;
                }
                if ((q/p) % p == 0) mobius[q] = 0;
                else mobius[q] *= -1;
            }
        }
    }
    //素数判定,O(1)
    bool judge_prime(int num){
        return isprime[num];
    }
    //素数列挙,O(N)
    vector<int> list_primes(int num = -1){
        if (num == -1) num = N;
        vector<int> primes;
        for(int p=0;p<=num;p++){
            if (isprime[p]) primes.push_back(p);
        }
        return primes;
    }
    //高速素因数分解,O(logN),{(素因数,個数)...}
    vector<pii> factorize(int x){
        vector<pii> ans;
        while(x > 1){
            int p = minfactor[x];
            int e = 0;
            while(minfactor[x] == p){
                x /= p;
                e++;
            }
            ans.push_back(make_pair(p,e));
        }
        return ans;
    }
    //高速約数列挙 O(240(N <= 1e6),1344(N <= 1e9))
    vector<int> divisors(int x){
        vector<int> ans; ans.push_back(1);
        vector<pii> facts = factorize(x);
        for(auto [p,e]:facts){
            int s = ans.size();
            for(int i=0;i<s;i++){
                int v = 1;
                for(int j=0;j<e;j++){
                    v *= p;
                    ans.push_back(ans[i] * v);
                }
            }
        }
        sort(all(ans));
        return ans;
    }
    //メビウス関数
    //mobius[1] = 1
    //nが素数pで2回以上割り切れる -> mobius[n] = 0
    //mobius[n] = pow(-1,Nの素数の種類)
    int my_mobius(int x){
        return mobius[x];
    }
};

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    //AOJ_prime_gap
    int N_max = 1299709 + 100;
    Eratosthenes era(N_max);
    auto primes = era.list_primes(N_max);
    while(true){
        int N; cin >> N;
        if (N == 0)return 0;
        if (era.judge_prime(N)) cout << 0 << endl;
        else{
            auto itr = lower_bound(all(primes),N);
            int r = *itr;
            itr--;
            int l = *itr;
            cout << r-l << endl;
        }
    }
}