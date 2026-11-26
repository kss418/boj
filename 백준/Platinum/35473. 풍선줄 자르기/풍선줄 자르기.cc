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
constexpr ll MAX = 101010; // SET MAX SIZE
constexpr ll MOD = 998244353;

struct sp_policy{
    using dist = ll; using cost = ll;
    static dist add(const dist& d, const cost& w){ // dist + cost 
        return d + w;
    }
    static bool leq(const dist& a, const dist& b){ // dist a <= dist b 
        return a <= b;
    }
    static dist inf(){ // ll -> INF, pll -> {INF, INF}, tll -> {INF, INF, INF} 
        return INF;
    }
    static dist zero(){ // ll -> 0, pll -> {0, 0}, tll -> {0, 0, 0} 
        return 0;
    }
};

template<class policy = sp_policy>
class _dij{
public:
    using dist = typename policy::dist; using cost = typename policy::cost;
private:
    bool base;
    struct edge{ cost w; int nxt; }; struct node{ dist d; int v; };
    struct cmp{ bool operator()(const node& a, const node& b) const{ return _dij::less(b.d, a.d); } };
    vector<vector<edge>> adj; int n;
    vector <dist> d; vector<int> pre, origin;
    priority_queue<node, vector<node>, cmp> pq;

    static bool less(const dist& a, const dist& b){ return policy::leq(a, b) && !policy::leq(b, a); } // O(1)
    static bool eq(const dist& a, const dist& b){ return policy::leq(a, b) && policy::leq(b, a); } // O(1)
    void cal(){
        while(!pq.empty()){
            auto [cd, cur] = pq.top(); pq.pop();
            if(!eq(cd, d[cur])) continue;
            for(const auto& i : adj[cur]){
                auto& [w, nxt] = i;
                dist nd = policy::add(cd, w);
                if(policy::leq(d[nxt], nd)) continue;
                d[nxt] = nd; pre[nxt] = cur; origin[nxt] = origin[cur];
                pq.push({nd, nxt});
            }
        }
    }
    void reset(int n){ pre.assign(n + 1, -1); origin.assign(n + 1, -1); d.assign(n + 1, policy::inf()); }
    void chk(int x) const{ assert(x >= base && x <= n); }
public:
    _dij(int n = 0, bool base = 1){ clear(n, base); } // O(n)
    void clear(int n, bool base = 1){ // O(n + m)
        this->n = n; this->base = base; adj.assign(n + 1, {}); reset(n);
        while(!pq.empty()) pq.pop();
    }

    void addsol(int st, int en, cost c){ // O(1)
        assert(base <= st && st <= n && base <= en && en <= n);
        adj[st].push_back({c, en});
    }
    void add(int st, int en, cost c){ // O(1)
        addsol(st, en, c); addsol(en, st, c);
    }

    void build(int source){ build(span<const int>(&source, 1)); } // O((n + m) log n)
    void build(span<const int> source){ // O(k + (n + m) log n)
        while(!pq.empty()) pq.pop();
        reset(n);
        for(int i : source){
            assert(base <= i && i <= n);
            if(origin[i] != -1) continue;
            d[i] = policy::zero(); origin[i] = i;
            pq.push({d[i], i});
        }
        cal();
    }

    dist ret(int x) const{ // O(1)
        chk(x);
        return d[x];
    }
    int parent(int x) const{ chk(x); return pre[x]; } // O(1)
    int source(int x) const{ chk(x); return origin[x]; } // O(1)

    bool reachable(int x) const{ // O(1)
        chk(x);
        return !eq(d[x], policy::inf());
    }

    template<class F>
    void it_path(int x, const F& f) const{ // O(n)
        chk(x); assert(reachable(x));
        vector<int> ret;
        for(int cur = x; cur != -1; cur = pre[cur]) ret.push_back(cur);
        reverse(all(ret));
        for(const auto& v : ret) f(v);
    }
}; _dij dij;
map <ll, ll> mp[MAX];
ll result, cnt;

void run(){
    cin >> n >> m; dij = {n, 0}; cnt = m - n;
    while(m--){
        ll s, e, c; cin >> s >> e >> c;
        dij.add(s, e, c);

        if(!mp[s].count(e)) mp[s][e] = mp[e][s] = c;
        mp[s][e] = mp[e][s] = min(mp[s][e], c);
    }

    dij.build(0);
    for(int i = 1;i <= n;i++){
        ll p = dij.parent(i);
        result += mp[i][p];
    }

    cout << cnt << " " << result << "\n";
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}