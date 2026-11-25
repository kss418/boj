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

class _uf{
private:
    bool base;
    vector<int> p; int n, cc;
protected:
    bool merge_internal(int& a, int& b){ // O(alpha(n)) amortized
        a = find(a); b = find(b);
        if(a == b) return false;
        if(p[a] > p[b]) swap(a, b);
        p[a] += p[b]; p[b] = a; cc--;
        return true;
    }
public:
    _uf(int n = 0, bool base = 1){ clear(n, base); } // O(n)
    void clear(int n, bool base = 1){ // O(n)
        this->n = n; this->base = base; cc = n - base + 1;
        p.assign(n + 1, -1);
    }

    int find(int x){ // O(alpha(n)) amortized
        if(p[x] < 0) return x;
        return p[x] = find(p[x]);
    }

    bool merge(int a, int b){ return merge_internal(a, b); } // O(alpha(n)) amortized
    int count() const{ return cc; } // O(1)
    int size(int x){ return -p[find(x)]; } // O(alpha(n)) amortized
    bool root(int x) const{ return p[x] < 0; } // O(1)
    bool same(int a, int b){ return find(a) == find(b); } // O(alpha(n)) amortized

    template<class F>
    void it_root(const F& f) const{ // O(n)
        for(int i = base;i <= n;i++) if(root(i)) f(i);
    }

    vector<vector<int>> groups(){ // O(n * alpha(n))
        vector<int> id(n + 1, -1);
        vector<vector<int>> ret; ret.reserve(cc);
        it_root([&](int r){
            id[r] = (int)ret.size(); ret.emplace_back();
            ret.back().reserve(-p[r]);
        });
        for(int i = base;i <= n;i++) ret[id[find(i)]].push_back(i);
        return ret;
    }
};

class uf_policy{
public:
    class node{
    public:
        bool cy;
        node(bool cy) : cy(cy){};
    };
    static node leaf(){ return {0}; }
    static void merge(node& a, node& b){
        a.cy |= b.cy;
    }
};

template <class policy = uf_policy>
class _uf_value : public _uf{
public:
    using node = typename policy::node;
private:
    bool base; vector<node> arr;
    node leaf() const{ return policy::leaf(); }
public:
    _uf_value(int n = 0, bool base = 1) : _uf(n, base), base(base), arr(n + 1, leaf()){} // O(n)
    void clear(int n, bool base = 1){ // O(n)
        _uf::clear(n, base); this->base = base;
        arr.assign(n + 1, leaf());
    }

    void make(span<const node> v){ // O(n)
        vector<node> tmp(v.size(), leaf());
        for(int i = base;i < (int)v.size();i++) tmp[i] = v[i];
        _uf::clear(v.empty() ? base - 1 : (int)v.size() - 1, base);
        arr.swap(tmp);
    }

    bool merge(int a, int b){ // O(alpha(n)) amortized + policy::merge
        if(!merge_internal(a, b)) return false;
        policy::merge(arr[a], arr[b]);
        return true;
    }

    node& get(int x){ return arr[find(x)]; } // O(alpha(n)) amortized
    void set(int x, const node& v){ arr[find(x)] = v; } // O(alpha(n)) amortized

    template<class F>
    void it_component(const F& f){ // O(n)
        it_root([&](int root){ f(root, arr[root]); });
    }
}; _uf_value uf;

ll result;
vector <tll> adj;
void run(){
    cin >> n >> m; uf = {n};
    while(m--){
        int s, e, c; cin >> s >> e >> c;
        adj.push_back({c, s, e});
    }

    sort(all(adj)); reverse(all(adj));
    for(auto& [c, s, e] : adj){
        if(uf.same(s, e)){
            if(uf.get(s).cy) continue;
            uf.set(s, 1);
            result += c;
        }
        else{
            if(uf.get(s).cy && uf.get(e).cy) continue;
            uf.merge(s, e);
            result += c;
        }
    }
    
    cout << result;
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}
