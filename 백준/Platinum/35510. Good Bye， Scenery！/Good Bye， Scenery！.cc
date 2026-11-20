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
constexpr ll MAX = 301010; // SET MAX SIZE
constexpr ll MOD = 998244353;
int a[MAX];
vector <pll> arr;

struct action{
    struct node {
        ll v, idx;
        node(ll v = 0, ll idx = 0) : v(v), idx(idx){}
    };
    struct lazy{
        ll v;
        lazy(ll v) : v(v){}
        bool operator==(const lazy&) const = default;
    };
    static node id(){ return {0, 0}; }
    static node leaf(){ return {0, 0}; }
    static lazy lz_id(){ return {0}; }
    static node op(const node& l, const node& r){
        return l.v > r.v ? l : r;
    }
    static void apply(node& seg, const lazy& lz){ seg.v += lz.v; }
    static void compose(lazy& s, const lazy& p){ s.v += p.v; }
};

template <class policy = action>
class _prop {
    bool base;
public:
    using node = typename policy::node;
    using lazy = typename policy::lazy;
    node op(const node& l, const node& r) const{ return policy::op(l, r); }
    node id() const{ return policy::id(); }
private:
    vector <node> seg; vector <lazy> lz; int sz, h, n;
    lazy lz_id() const{ return policy::lz_id(); }
    void prop(node& seg, const lazy& lz) const{ policy::apply(seg, lz); }
    void comp(lazy& s, const lazy& p) const{ policy::compose(s, p); }
    node join(const node& a, const node& b, bool right) const{ return right ? op(a, b) : op(b, a); }

    void reset_storage(int n){
        this->n = n; sz = 1; while(sz < n + 1) sz <<= 1;
        h = __lg(sz);
        seg.assign(2 * sz, id());
        lz.assign(2 * sz, lz_id());
    }

    void push(int idx){
        if(lz[idx] == lz_id()) return;
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
            if(lz[idx] == lz_id()) continue;
            prop(seg[idx], lz[idx]);
        }
    }

    template<class F>
    int bisect(int p, bool right, const F& f) {
        assert(right ? base <= p && p <= n + 1 : base - 1 <= p && p <= n); assert(f(id()));
        if(right) { if (p == n + 1) return n; }
        else { if (p == base - 1) return base; }
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
        return right ? n : base;
    }
public:
    _prop(int n = 0, bool base = 1){ clear(n, base); } // O(n)
    _prop(span<const node> arr, bool base = 1) : base(base){ make(arr); } // O(n)
    void clear(int n, bool base = 1){ // O(n)
        this->base = base; reset_storage(n);
        for(int i = base;i <= n;i++) seg[i + sz] = policy::leaf();
        for(int i = sz - 1;i >= 1;i--) seg[i] = op(seg[i << 1], seg[i << 1 | 1]);
    }

    void make(span<const node> arr){ // O(n)
        reset_storage(arr.empty() ? base - 1 : (int)arr.size() - 1);
        for(int i = base;i < (int)arr.size();i++) seg[i + sz] = arr[i];
        for(int i = sz - 1;i >= 1;i--) seg[i] = op(seg[i << 1], seg[i << 1 | 1]);
    }

    node query(int idx){ // O(log n)
        assert(base <= idx && idx <= n); idx += sz;
        propagate(idx);
        return seg[idx];
    }
    node query(int st, int en) { // O(log n)
        st = max((int)base, st); en = min(n, en);
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
        st = max((int)base, st); en = min(n, en);
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

vector <action::node> tmp;
void run(){
    cin >> n; arr.clear(); seg.clear(n);
    for(int i = 1;i <= n;i++) cin >> a[i], arr.push_back({a[i], i});
    sort(all(arr)); 

    for(int i = 0;i <= n;i++) tmp.push_back({0, i});
    seg.make(tmp); tmp.clear();

    bool flag = 1; ll result = 0;
    for(int i = n;i >= 1;i--){
        while(!arr.empty() && arr.back().x == i){
            auto [v, idx] = arr.back();
            arr.pop_back();
            seg.update(idx, idx);
        }

        auto [v, idx] = seg.query(1, n);
        if(v <= 0) flag = 0;
        else{
            result += i - v;
            seg.update(idx + 1, n, -1);
            seg.update(idx, MINF);
        }
    }

    if(!flag) result = -1;
    cout << result << "\n";
}

int main() {
    fastio; cin >> t;
    while(t--) run(); 

    return 0;
}
