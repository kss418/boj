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
}; _uf uf;
map <ll, ll> mp, org;
ll x[MAX], y[MAX];

void cal(int i, ll v){
    ll mn = min(v, abs(x[i]));
    x[i] = (x[i] >= 0 ? x[i] - mn : x[i] + mn);
    v -= mn;
    
    mn = min(v, abs(y[i]));
    y[i] = (y[i] >= 0 ? y[i] - mn : y[i] + mn);
}

void run(){
    cin >> n; uf = {n, 0}; mp[0] = 0;
    for(int i = 1;i <= n;i++){
        cin >> x[i] >> y[i];
        ll sum = abs(x[i]) + abs(y[i]);
        if(mp.count(sum)) uf.merge(i, mp[sum]);
        mp[sum] = uf.find(i);
    }

    cin >> m;
    while(m--){
        ll v; cin >> v;
        auto [idx, num] = *--mp.upper_bound(v);
        if(!idx) continue;

        if(mp.count(idx - 1)) uf.merge(mp[idx - 1], num);
        mp[idx - 1] = uf.find(num);
        mp.erase(idx);
    }

    for(auto& [idx, num] : mp) org[uf.find(num)] = idx;
    for(int i = 1;i <= n;i++){
        ll c = abs(x[i]) + abs(y[i]) - org[uf.find(i)];
        cal(i, c);

        cout << x[i] << " " << y[i] << "\n";
    }
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}
