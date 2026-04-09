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
constexpr ll MOD = 998244353;
constexpr ll MOD2 = 1e9 + 7;

ll pw[2][MAX], all[2];
int a[MAX], pos[MAX], mp[MAX];
vector <pair<int, int>> arr;
vector <int> result;

struct monoid{
    struct node {
        pair <ll, ll> v;
        int c;
        node(pair <ll, ll> v = {0, 0}, int c = 0) : v(v), c(c){}
    };
    static node op(const node& l, const node& r){
        int c = l.c + r.c;
        pair <ll, ll> v = l.v;
        v.x += (r.v.x * pw[0][l.c + 1]) % MOD;
        v.y += (r.v.y * pw[1][l.c + 1]) % MOD2; 
        if(v.x >= MOD) v.x -= MOD;
        if(v.y >= MOD2) v.y -= MOD2;
        return {v, c};
    }
};

template <class policy = monoid>
class _seg {
public:
    using node = typename policy::node;
    node op(const node& l, const node& r) const{ return policy::op(l, r); }
    node id() const{ return node(); }
private:
    int n, sz; vector <node> seg;
    node join(const node& a, const node& b, bool right) const{ return right ? op(a, b) : op(b, a); }
    template<class F>
    int bisect(int p, bool right, const F& f) {
        assert(0 <= p && p <= n); assert(f(id()));
        if(right) { if (p == n) return n; }
        else { if (p == 0) return 0; }
        int i = right ? (p + sz) : (p + 1 + sz); node v = id();
        while(1){
            if(!right) --i;
            if(right) while ((i & 1) == 0) i >>= 1;
            if(!right) while (i > 1 && (i & 1)) i >>= 1;
            node tmp1 = join(v, seg[i], right);
            if (!f(tmp1)) {
                while (i < sz) {
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
    _seg(int n = 0){ clear(n); } // O(n)
    _seg(span<const node> arr){ build(arr); } // O(n)
    void clear(int n){ // O(n)
        this->n = n;
        sz = 1; while(sz < n + 1) sz <<= 1;
        seg.assign(2 * sz, id());
    }

    void build(span<const node> arr){ // O(n)
        if(arr.empty()){ clear(0); return; }
        clear((int)arr.size() - 1);
        for(int i = 0;i < (int)arr.size();i++) seg[i + sz] = arr[i];
        for(int i = sz - 1;i >= 1;i--) seg[i] = op(seg[i << 1], seg[i << 1 | 1]);
    }

    node query(int st, int en){ // O(log n)
        st = max(0, st); en = min(n, en);
        if(st > en) return id();
        node l = id(), r = id();
        st += sz; en += sz;
        while(st <= en){
            if(st & 1) l = op(l, seg[st++]);
            if(!(en & 1)) r = op(seg[en--], r);
            st >>= 1; en >>= 1; 
        }
        return op(l, r);
    }

    void set(int idx, const node& v){ // O(log n)
        if(idx < 0 || idx > n) return;
        int p = idx + sz; seg[p] = v;
        for(p >>= 1; p; p >>= 1) seg[p] = op(seg[p << 1], seg[p << 1 | 1]);
    }

    const node& root() const { return seg[1]; }
    template<class F>
    int max_right(int l, const F& f){ return bisect(l, 1, f); } // O(log n)

    template<class F>
    int min_left(int r, const F& f){  return bisect(r, 0, f); } // O(log n)
}; _seg seg;

void run(){
    cin >> n >> m; seg.clear(m);
    pw[0][1] = pw[1][1] = all[0] = all[1] = 1;
    for(int i = 2;i <= n;i++){
        pw[0][i] = (pw[0][i - 1] * 26) % MOD;
        pw[1][i] = (pw[1][i - 1] * 31) % MOD2;
        all[0] += pw[0][i]; all[0] %= MOD;
        all[1] += pw[1][i]; all[1] %= MOD2;
    }

    ll now[2] = {0, 0};
    for(int i = 1;i <= n;i++){
        int v; cin >> v;
        now[0] += pw[0][i] * v; now[0] %= MOD;
        now[1] += pw[1][i] * v; now[1] %= MOD2;
    }

    for(int i = 1;i <= m;i++){
        cin >> a[i];
        arr.push_back({a[i], i});
    }

    sort(all(arr));
    for(int i = 0;i < arr.size();i++) mp[arr[i].y] = i + 1;
    ll sub[2] = {0, 0};
    for(int i = 1;i <= m;i++){
        seg.set(mp[i], {{i, i}, 1});
        if(i > n) seg.set(mp[i - n], {{0, 0}, 0});
        if(i >= n){
            auto q = seg.root().v;
            q.x -= sub[0]; q.y -= sub[1];
            if(q.x < 0) q.x += MOD;
            if(q.y < 0) q.y += MOD2;

            sub[0] += all[0]; sub[1] += all[1];
            if(sub[0] >= MOD) sub[0] -= MOD;
            if(sub[1] >= MOD2) sub[1] -= MOD2;
            
            if(q.x != now[0] || q.y != now[1]) continue;
            result.push_back(i - n + 1);
        }
    }

    cout << result.size() << "\n";
    for(auto& i : result) cout << i << " ";
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}
