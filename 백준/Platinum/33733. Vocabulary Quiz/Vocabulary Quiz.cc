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

int p[MAX];
vector <int> adj[MAX];

class _st { // 0-base index
private:
    vector <vector<ll>> sum;
    ll m; int n, lg; 
public:
    vector <vector<int>> lift;
    _st(int n = 0, ll max_step = 0){ clear(n, max_step); }; // O(n log m)
    void clear(int n, ll m = 60){ // O(n log m)
        lg = 1; this->n = n; this->m = m;
        while((1ll << lg) <= m) lg++;
        lift.assign(lg + 1, vector<int>(n + 2, n + 1));
        sum.assign(lg + 1, vector<ll>(n + 2, 1));
    }

    void add(int st, int en, ll co = 1) { lift[0][st] = en; sum[0][st] = co; } // O(1)
    void build(){ // O(n log m)
        for(int i = 1;i <= lg;i++){
            for(int j = 0;j <= n;j++){
                int mid = lift[i - 1][j];
                lift[i][j] = lift[i - 1][mid];
                sum[i][j] = min<int>(sum[i - 1][j] + sum[i - 1][mid], 0x3f3f3f3f);
            }
        }
    }

    int next(int v) const{ return lift[0][v]; } // O(1)
    pair<int, ll> ret(int cur, ll k) const{ // O(log m)
        ll co = 0;
        for(int i = lg; i >= 0; i--){
            if(k < sum[i][cur]) continue;
            co += sum[i][cur]; k -= sum[i][cur]; cur = lift[i][cur];
        }
        return {cur, co}; // 도착 정점, 사용한 비용
    }
}; _st st;

struct monoid{
    struct node {
        int v;
        node(int v = 0) : v(v){}
    };
    static node op(const node& l, const node& r){
        return {
            l.v + r.v
        };
    }
};

template <class policy>
concept has_inv = requires(const typename policy::node& a){
    { policy::inv(a) } -> std::same_as<typename policy::node>;
};

struct group{
    struct node{
        ll v;
        node(ll v = 0) : v(v){}
    };
    static node op(const node& l, const node& r){
        return {l.v + r.v};
    }
    static node inv(const node& a){
        return {-a.v};
    }
};

template <class policy = group>
class _fw{ // 0-based index
private:
    using node = typename policy::node;
    vector <node> bit; int n;
    node op(const node& l, const node& r) const{ return policy::op(l, r); }
    node id() const{ return node(); }
    node inv(const node& a) const{ return policy::inv(a); }
public:
    _fw(int n = 0){ clear(n); } // O(n)
    _fw(span<const node> arr){ build(arr); } // O(n)
    void clear(int n){ // O(n)
        this->n = n;
        bit.assign(n + 2, id());
    }

    void build(span<const node> arr){ // O(n)
        if(arr.empty()){ clear(0); return; }
        clear((int)arr.size() - 1);
        for(int i = 0;i <= n;i++) bit[i + 1] = arr[i];
        for(int i = 1;i <= n + 1;i++){
            int j = i + (i & -i);
            if(j <= n + 1) bit[j] = op(bit[j], bit[i]);
        }
    }

    // range query -> need inv
    node query(int idx) requires has_inv<policy> { return query(idx, idx); } // O(log n)
    node query(int l, int r) requires has_inv<policy> { // O(log n)
        l = max(l, 0); r = min(r, n);
        if(l > r) return id();
        return op(pre(r), inv(pre(l - 1))); 
    }

    // return 0 ~ idx
    node pre(int idx){ // O(log n)
        node ret = id(); idx = min(idx, n);
        for(int i = idx + 1;i > 0;i -= i & -i) ret = op(ret, bit[i]);
        return ret;
    }

    void set(int idx, const node& v) requires has_inv<policy> { // O(log n)
        if(idx < 0 || idx > n) return;
        node cur = query(idx, idx), d = op(v, inv(cur));         
        update(idx, d);                
    }

    void update(int idx, const node& v){ // O(log n)
        if(idx < 0 || idx > n) return;
        for(int i = idx + 1;i <= n + 1;i += i & -i) bit[i] = op(bit[i], v);
    }
}; _fw fw;

int in[MAX], out[MAX], seq = - 1, dep[MAX];
void dfs(int cur, int d = 0){
    in[cur] = ++seq; dep[cur] = d;
    for(auto& nxt : adj[cur]) dfs(nxt, d + 1);
    out[cur] = seq;

    if(adj[cur].empty()) fw.set(in[cur], 1), m++;
}

void run(){
    cin >> n; st.clear(n, 1010101); fw.clear(n);
    for(int i = 1;i <= n;i++){
        cin >> p[i], adj[p[i]].push_back(i);
        st.add(i, p[i]);
    }
    st.build(); dfs(0);

    while(m--){
        int v, tmp; cin >> v; tmp = v;
        for(int i = 20;i >= 0;i--){
            int nxt = st.lift[i][tmp];
            if(nxt == n + 1) continue;
            int q = fw.query(in[nxt], out[nxt]).v;
            if(q > 1) continue; tmp = nxt;
        }
        fw.set(in[v], 0);

        cout << dep[tmp] << "\n";
    }
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}