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

template <typename T, typename F>
struct SegmentTree2D {
    private:
        int id(int h, int w) { return h * 2 * W + w; }
    public:
        int H, W;
        vector<T> seg;
        const F f;
        const T I;
    SegmentTree2D(int h, int w, F _f, const T& i) : f(_f), I(i) { init(h, w); }

    void init(int h, int w) {
        H = W = 1;
        while (H < h) H <<= 1;
        while (W < w) W <<= 1;
        seg.assign(4 * H * W, I);
    }

    // build にのみ呼ぶ
    void set(int h, int w, const T& x) { seg[id(h + H, w + W)] = x; }

    void build() {
    // w in [W, 2W)
        for (int w = W; w < 2 * W; w++) {
            for (int h = H - 1; h; h--) {
                seg[id(h, w)] = f(seg[id(2 * h + 0, w)], seg[id(2 * h + 1, w)]);
            }
        }
    // h in [0, 2H)
        for (int h = 0; h < 2 * H; h++) {
            for (int w = W - 1; w; w--) {
                seg[id(h, w)] = f(seg[id(h, 2 * w + 0)], seg[id(h, 2 * w + 1)]);
            }
        }
    }

    T get(int h, int w)  { return seg[id(h + H, w + W)]; }
    // T operator()(int h, int w) const { return seg[id(h + H, w + W)]; }

    void update(int h, int w, const T& x) {
        h += H, w += W;
        seg[id(h, w)] = x;
        for (int i = h >> 1; i; i >>= 1) {
            seg[id(i, w)] = f(seg[id(2 * i + 0, w)], seg[id(2 * i + 1, w)]);
        }
        for (; h; h >>= 1) {
            for (int j = w >> 1; j; j >>= 1) {
                seg[id(h, j)] = f(seg[id(h, 2 * j + 0)], seg[id(h, 2 * j + 1)]);
            }
        }
    }

    T _inner_query(int h, int w1, int w2) {
        T res = I;
        for (; w1 < w2; w1 >>= 1, w2 >>= 1) {
            if (w1 & 1) res = f(res, seg[id(h, w1)]), w1++;
            if (w2 & 1) --w2, res = f(res, seg[id(h, w2)]);
        }
        return res;
    }

  // [ (h1,w1), (h2,w2) ) 半開
    T prod(int h1, int w1, int h2, int w2) {
        if (h1 >= h2 || w1 >= w2) return I;
        T res = I;
        h1 += H, h2 += H, w1 += W, w2 += W;
        for (; h1 < h2; h1 >>= 1, h2 >>= 1) {
            if (h1 & 1) res = f(res, _inner_query(h1, w1, w2)), h1++;
            if (h2 & 1) --h2, res = f(res, _inner_query(h2, w1, w2));
        }
        return res;
    }
};

/**
 * @brief 二次元セグメント木
 * @docs docs/data-structure-2d/2d-segment-tree.md
 */
// 
// ll f(ll a, ll b){return a + b;}
// ll e(){return 0ll;}
// SegmentTree2D seg(H,W,f,e());


// https://atcoder.jp/contests/tessoku-book/submissions/36789850
ll f(ll a, ll b){return a + b;}
ll e(){return 0ll;}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int H,W; cin >> H >> W;
    SegmentTree2D seg(H,W,f,e());
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            ll x; cin >> x;
            seg.set(i,j,x);
        }
    }
    seg.build();
    int Q; cin >> Q;
    while(Q--){
        int a,b,c,d; cin >> a >> b >> c >> d;
        a--;
        b--;
        c--;
        d--;
        auto val = seg.prod(a,b,c+1,d+1);
        cout << val << endl;
    }
}