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
constexpr ll MAX = 5010; // SET MAX SIZE
constexpr ll MOD = 998244353;

class _bs { // integer
public:
    template <class F>
    static ll max_right(ll l, ll r, const F& f) {
        ll lo = l, hi = r, mid = -1;
        while (hi > lo) {
            mid = (hi + lo + 1) >> 1ll;
            if (f(mid)) lo = mid;
            else hi = mid - 1;
        }
        return lo;
    }

    template <class F>
    static ll min_left(ll l, ll r, const F& f) {
        ll lo = l, hi = r, mid = -1;
        while (hi > lo) {
            mid = (hi + lo) >> 1ll;
            if (f(mid)) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }
};

struct uf_policy{
    struct node{
        int mn;
        node(int mn = 0) : mn(mn){} // identity
    };
    static void merge(node& a, node& b){
        a.mn = min(a.mn, b.mn);
    }
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

bool chk(int a, int b, int cur){
    int diff = uf.get(b).mn - uf.get(a).mn;
    return diff >= 0 && diff <= cur;
}

vector <pair<int, int>> arr;
bool f(int cur){
    uf.clear(n);
    for(auto& [v, idx] : arr) uf.set(idx, v);
    for(auto& [v, idx] : arr){
        if(uf.size(idx) != 1) continue;
        int tmp = idx;
        while(tmp > 1 && chk(tmp, tmp - 1, cur)) uf.merge(tmp, tmp - 1), tmp--;

        tmp = idx;
        while(tmp < n && chk(tmp, tmp + 1, cur)) uf.merge(tmp, tmp + 1), tmp++;
    }

    return uf.count() <= m;
}

void run(){
    cin >> n >> m;
    for(int i = 1;i <= n;i++) cin >> k, arr.push_back({k, i});
    sort(all(arr));

    cout << _bs::min_left(0, 10101, f);
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}