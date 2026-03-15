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
constexpr ll MAX = 201010; // SET MAX SIZE
constexpr ll MOD = 998244353;

ll a[MAX], result, sum[MAX];
bool cy[MAX];
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

void run(){
    cin >> n >> m >> s; uf.clear(n);
    for(int i = 1;i <= n;i++) cin >> a[i], result += a[i]; 
    
    int lc = 0, rc = 0;
    for(auto& i : s){
        lc += (i == 'L');
        rc += (i == 'R');
    }

    if(!lc || !rc){ cout << result; return; } 
    for(int i = 0;i < n;i++){
        int j = (i + 1) % n;
        if(s[i] != 'R' || s[j] != 'L') continue;
        cy[i + 1] = cy[j + 1] = 1;
    }

    for(int i = 1;i <= n;i++){
        if(cy[i]) continue;
        if(s[i - 1] == 'L'){
            int pre = (i == 1 ? n : i - 1);
            if(!cy[pre]) uf.merge(pre, i);
        }
        else{
            int nxt = (i == n ? 1 : i + 1);
            if(!cy[nxt]) uf.merge(nxt, i);
        }
    }

    for(int i = 1;i <= n;i++){
        if(cy[i]) continue;
        sum[uf.find(i)] += a[i];
    }

    for(int i = 1;i <= n;i++){
        if(cy[i] || !uf.root(i)) continue;
        result -= min(sum[i], m);
    }

    cout << result;
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}