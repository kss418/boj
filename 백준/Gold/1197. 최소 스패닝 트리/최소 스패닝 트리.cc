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

struct uf_policy{
    struct node{
        node(){} // identity
    };
    static void merge(node& a, node& b){}
};

template <class policy = uf_policy>
class _uf{ // 1-based index
private:
    using node = typename policy::node;
    vector<node> arr;
    vector<int> p, sz; int n, cc;
    node id() const{ return node(); }
public:
    _uf(int n = 0){ clear(n); } // O(n)
    void clear(int n){ // O(n)
        this->n = n; cc = n;
        p.assign(n + 1, -1); sz.assign(n + 1, 1);
        arr.assign(n + 1, id());
    }

    int find(int x){ // O(1)
        if(p[x] == -1) return x;
        return p[x] = find(p[x]);
    }

    bool merge(int a, int b){ // O(1) + policy::merge
        a = find(a); b = find(b);
        if(a == b) return false;
        if(sz[a] < sz[b]) swap(a, b);
        p[b] = a; sz[a] += sz[b]; cc--;
        policy::merge(arr[a], arr[b]); arr[b] = id();
        return true;
    }

    int count() const{ return cc; } // O(1)
    node& get(int x){ return arr[find(x)]; } // O(1)
    void set(int x, const node& v){ arr[find(x)] = v; } // O(1)
    int size(int x){ return sz[find(x)]; } // O(1)
    bool root(int x){ return find(x) == x; } // O(1)
    bool same(int a, int b){ return find(a) == find(b); } // O(1)
}; _uf uf;

struct edge{
    int s, e, c;
    bool operator < (const edge& ot) const{
        return c < ot.c;
    }
}; vector <edge> adj;
int cost[MAX];

int mst(){
    int ret = 0;
    sort(all(adj));
    for(auto& [s, e, c] : adj){
        if(uf.same(s, e)) continue;
        uf.merge(s, e);
        ret += c;
    }

    return ret;
};

void run(){
    cin >> n >> m; uf.clear(n);
    while(m--){
        int s, e, c; cin >> s >> e >> c;
        adj.push_back({s, e, c});
    }

    cout << mst();
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}