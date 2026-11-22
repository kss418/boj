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
constexpr ll MAX = 55; // SET MAX SIZE
constexpr ll MOD = 998244353;
ll result[MAX];
string st[MAX];

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
}; _uf uf;

void run(){
    cin >> n >> m; uf = {n - 1, 0};
    for(int i = 0;i < n;i++) cin >> st[i];

    for(int i = 0;i < n;i++){
        for(int j = i + 1;j < n;j++){
            if(st[i][j] == 'N' || m <= 0) continue;
            if(uf.same(i, j)) continue;
            uf.merge(i, j); m--;
            result[i]++; result[j]++;
            st[i][j] = 'N'; 
        }
    }

    if(uf.count() != 1){
        cout << -1;
        return;
    }

    for(int i = 0;i < n;i++){
        for(int j = i + 1;j < n;j++){
            if(st[i][j] == 'N' || m <= 0) continue;
            result[i]++; result[j]++;
            m--;
        }
    }

    if(m){
        cout << -1;
        return; 
    }
    
    for(int i = 0;i < n;i++) cout << result[i] << " ";
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}