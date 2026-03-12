#include <bits/stdc++.h>
#define fastio cin.tie(0), cout.tie(0), ios::sync_with_stdio(0);
#define all(x) (x).begin(), (x).end()
#define x first 
#define y second
using namespace std; using ll = long long; using u64 = uint64_t;
using ld = long double; using pld = pair<ld, ld>;
using i128 = __int128_t; using f128 = __float128; 
using pll = pair<ll, ll>; using tll = tuple<ll, ll, ll>;
ll n, m, k, t = 1; string s;

constexpr ll INF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MINF = 0xc0c0c0c0c0c0c0c0;
constexpr ll MAX = 1010101; // SET MAX SIZE
constexpr ll MOD = 1e9 + 7;

ll pow2(int p){
    if(!p) return 1;
    if(p == 1) return 2;
    ll cur = (pow2(p / 2) * pow2(p / 2)) % MOD;
    return (cur * (p % 2 ? 2 : 1)) % MOD;
}

int norm_mod(int x){
    return (x % MOD + MOD) % MOD;
}

int p[MAX], o[MAX], sum = 1, dp[MAX];
struct action{
    struct node {
        ll v; int sz;
        node(ll v = 0, int sz = 0) : v(v), sz(sz){}
    };
    struct lazy{
        ll v, mul;
        lazy(ll v = -1, ll mul = 0) : mul(mul), v(v){}
    };
    static node op(const node& l, const node& r){
        return node{
            (l.v + r.v) % MOD,
            l.sz + r.sz
        };
    }
    static bool is_lz_id(const lazy& now){ return !now.mul && now.v == -1; }
    static void apply(node& seg, const lazy& lz){ 
        if(lz.v != -1) seg.v += lz.v * seg.sz;
        seg.v *= pow2(lz.mul); seg.v %= MOD;
    }
    static void compose(lazy& s, const lazy& p){ s.v = p.v; s.mul += p.mul; }
};

template <class policy = action>
class _prop { 
public:
    using node = typename policy::node;
    using lazy = typename policy::lazy;
    node op(const node& l, const node& r) const{ return policy::op(l, r); }
    node id() const{ return node(); }
private:
    vector <node> seg; vector <lazy> lz; int sz, h, n;
    lazy lz_id() const{ return lazy(); }
    bool is_lz_id(const lazy& now) const{ return policy::is_lz_id(now); }
    void prop(node& seg, const lazy& lz) const{ policy::apply(seg, lz); }
    void comp(lazy& s, const lazy& p) const{ policy::compose(s, p); }
    node join(const node& a, const node& b, bool right) const{ return right ? op(a, b) : op(b, a); }

    void push(int idx){
        if(is_lz_id(lz[idx])) return;
        apply(idx << 1, lz[idx]);
        apply(idx << 1 | 1, lz[idx]);
        lz[idx] = lz_id();
    }

    void propagate(int idx){
        for(int i = h;i > 0;i--){
            int cur = idx >> i;
            push(cur);
        }
    }

    void apply(int idx, const lazy& now){
        prop(seg[idx], now);
        if(idx < sz) comp(lz[idx], now); 
    }

    void rebuild(int idx){
        while(idx > 1){
            idx >>= 1;
            seg[idx] = op(seg[idx << 1], seg[idx << 1 | 1]);
            if(is_lz_id(lz[idx])) continue;
            prop(seg[idx], lz[idx]);
        }
    }

    template<class F>
    int bisect(int p, bool right, const F& f) {
        assert(0 <= p && p <= n); assert(f(id()));
        if(right) { if (p == n) return n; }
        else { if (p == 0) return 0; }
        int i = right ? (p + sz) : (p + 1 + sz);
        if(right) propagate(i); else propagate(i - 1);
        node v = id();
        while(1){
            if(!right) --i;
            if(right) while ((i & 1) == 0) i >>= 1;
            if(!right) while (i > 1 && (i & 1)) i >>= 1;
            node tmp1 = join(v, seg[i], right);
            if (!f(tmp1)) {
                while (i < sz) {
                    push(i);
                    i = (i << 1) | (!right);
                    node tmp2 = join(v, seg[i], right);
                    if(f(tmp2)){ v = tmp2; i += right ? 1 : -1; }
                }
                return right ? (i - sz - 1) : (i + 1 - sz);
            }
            v = tmp1;
            if(right) ++i; if((i & -i) == i) break;
        }
        return right ? n : 0;
    }
public:
    _prop(int n = 0){ clear(n); } // O(n)
    _prop(span<const node> arr){ build(arr); } // O(n)
    void clear(int n){ // O(n)
        this->n = n;
        sz = 1; while(sz < n + 1) sz <<= 1;
        h = __lg(sz);
        seg.assign(2 * sz, id());
        lz.assign(2 * sz, lz_id());
    }

    void build(span<const node> arr){ // O(n)
        if(arr.empty()){ clear(0); return; }
        clear((int)arr.size() - 1);
        for(int i = 0;i < (int)arr.size();i++) seg[i + sz] = arr[i];
        for(int i = sz - 1;i >= 1;i--) seg[i] = op(seg[i << 1], seg[i << 1 | 1]);
    }

    node query(int idx){ return query(idx, idx); } // O(log n)
    node query(int st, int en) { // O(log n)
        st = max(0, st); en = min(n, en);
        if(st > en) return id();

        int l = (int)st + sz, r = (int)en + sz;
        propagate(l); propagate(r);

        node nl = id(), nr = id();
        while(l <= r){
            if(l & 1) nl = op(nl, seg[l++]);
            if(!(r & 1)) nr = op(seg[r--], nr);
            l >>= 1; r >>= 1;
        }

        return op(nl, nr);
    }

    void update(int idx, const lazy& lz){ update(idx, idx, lz); } // O(log n)
    void update(int st, int en, const lazy& lz){ // O(log n)
        st = max(0, st); en = min(n, en);
        if(st > en) return;

        int l = (int)st + sz, r = (int)en + sz;
        int tl = l, tr = r;
        propagate(l); propagate(r);

        while(l <= r){
            if(l & 1) apply(l++, lz);
            if(!(r & 1)) apply(r--, lz);
            l >>= 1; r >>= 1;
        }
        
        rebuild(tl); rebuild(tr);
    }

    template<class F>
    int max_right(int l, const F& f){ return bisect(l, 1, f); } // O(log n)

    template<class F>
    int min_left(int r, const F& f){  return bisect(r, 0, f); } // O(log n)
}; _prop seg;

vector <action::node> arr;
void run(){
    cin >> n >> m; seg.clear(n); arr.resize(n + 1);
    for(int i = 1;i <= n;i++){
        cin >> p[i] >> o[i];
        arr[i] = {0, 1};
    }
    arr[0] = {0, 1};
    seg.build(arr);

    seg.update(0, {1, 0});
    for(int i = 1;i <= n;i++){
        if(o[i]){
            ll sum = seg.query(0, i).v;
            seg.update(i, {sum, 0});
        }
        else{
            auto idx = upper_bound(p, p + n + 1, p[i] - m - 1) - p;
            seg.update(max<int>(idx, 1ll), i, {0, 1});
        }
    }

    cout << seg.query(1, n).v;
}   

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}