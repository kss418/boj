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

int seq, adj[MAX][2], result;
int cnt[MAX], p[MAX], ind[MAX], dep[MAX];
deque <int> q;

void insert(const string& s){
    int now = 0;
    for(auto& i : s){
        int nxt = adj[now][i - '0'];
        if(nxt == -1){
            adj[now][i - '0'] = nxt = ++seq;
            p[nxt] = now;
            ind[now]++;
            dep[nxt] = dep[now] + 1;
        }
        now = nxt;
    }
    cnt[now]++;
}

struct uf_policy{
    struct node{
        map <int, int> free, use;
        node(){} // identity
    };
    static void merge(node& a, node& b){
        for(auto& [v, c] : b.free) a.free[v] += c;
        for(auto& [v, c] : b.use) a.use[v] += c;
        b.free.clear(); b.use.clear();
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
        if(size(a) < size(b)) swap(a, b);
        p[b] = a; sz[a] += sz[b]; cc--;
        policy::merge(arr[a], arr[b]); arr[b] = id();
        return true;
    }

    int count() const{ return cc; } // O(1)
    node& get(int x){ return arr[find(x)]; } // O(1)
    void set(int x, const node& v){ arr[find(x)] = v; } // O(1)
    int size(int x){ return get(x).free.size() + get(x).use.size(); } // O(1)
    bool root(int x){ return find(x) == x; } // O(1)
    bool same(int a, int b){ return find(a) == find(b); } // O(1)
}; _uf uf;

pair<int, int> get(const map <int, int>& mp){
    if(mp.empty()) return {INF, 1};
    return *mp.begin();
}

void use_begin(int cur){
    auto free = get(uf.get(cur).free);
    auto use = get(uf.get(cur).use);

    if(free.x <= use.x + 2){
        uf.get(cur).free[free.x]--;
        if(free.y == 1) uf.get(cur).free.erase(free.x);
        uf.get(cur).use[free.x]++;
        result += free.x - dep[cur];
    }
    else{
        uf.get(cur).use[use.x]--;
        if(use.y == 1) uf.get(cur).use.erase(use.x);
        uf.get(cur).use[use.x + 1] += 2;
        result += use.x - dep[cur] + 2;
    }
}
 
void run(){
    cin >> n;
    memset(p, -1, sizeof(p));
    memset(adj, -1, sizeof(adj));
    for(int i = 1;i <= n;i++){
        cin >> s;
        insert(s);
    }
    uf.clear(seq);

    for(int i = 1;i <= seq;i++){
        if(ind[i]) continue;
        q.push_back(i);   
    }

    while(!q.empty()){
        auto cur = q.front(); q.pop_front();
        if(adj[cur][0] == -1 && adj[cur][1] == -1){
            uf.get(cur).use[dep[cur]]++;
            cnt[cur]--;
        }
        else for(int i = 0;i <= 1;i++){
            if(adj[cur][i] != -1) continue;
            uf.get(cur).free[dep[cur] + 1]++;
        }

        for(int i = 1;i <= cnt[cur];i++) use_begin(cur);
        if(p[cur] == -1) continue;
        uf.merge(cur, p[cur]);
        if(!--ind[p[cur]]) q.push_back(p[cur]);
    }

    cout << result;
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}
