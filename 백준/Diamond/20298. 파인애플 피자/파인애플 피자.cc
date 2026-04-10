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

int lo[MAX], hi[MAX], eq[MAX];
map <int, int> mp;

template <class T = ll>
class _kmp{ // 0-based index
private:
    int m;
    vector <T> pat; vector <int> arr;
    void build(){
        m = (int)pat.size(); int nxt = 0; arr.assign(m, 0);
        for(int cur = 1;cur < m;cur++){
            while(nxt && !build_chk(cur, nxt)) nxt = arr[nxt - 1];
            if(build_chk(cur, nxt)) arr[cur] = ++nxt;
        }
    }

    bool build_chk(int cur, int nxt) const{
        int base = cur - nxt;
        if(eq[nxt + 1]) return pat[cur] == pat[base + eq[nxt + 1] - 1];
        if(lo[nxt + 1] && pat[cur] <= pat[base + lo[nxt + 1] - 1]) return 0;
        if(hi[nxt + 1] && pat[cur] >= pat[base + hi[nxt + 1] - 1]) return 0;
        return 1;
    }

    bool match_chk(span<const T> v, int idx, int state) const{
        int base = idx - state;
        if(eq[state + 1]) return v[idx] == v[base + eq[state + 1] - 1];
        if(lo[state + 1] && v[idx] <= v[base + lo[state + 1] - 1]) return 0;
        if(hi[state + 1] && v[idx] >= v[base + hi[state + 1] - 1]) return 0;
        return 1;
    }

    static vector <T> tf(const string& s){
        vector <T> ret; ret.reserve(s.size());
        for(unsigned char c : s) ret.push_back(T(c));
        return ret;
    }
public:
    _kmp() : m(0){}
    _kmp(const string& s){ set(s); } // O(|s|)
    _kmp(span<const T> v){ set(v); } // O(|v|)
    void clear(){ pat.clear(); arr.clear(); m = 0; } // O(1)
    void set(const string& s){ pat = tf(s); build(); } // O(|s|)
    void set(span<const T> v){ pat.assign(all(v)); build(); } // O(|v|)

    const vector<int>& fail() const{ return arr; } // O(1)
    template <class F>
    void it_match(const string& s, const F& f) const{ it_match(tf(s), f);} // O(|s| + m)
    template <class F>
    void it_match(span<const T> v, const F& f) const{ // O(|v| + m)
        int n = (int)v.size();
        if(!m) return; int state = 0;
        for(int i = 0;i < n;i++){
            state = go(state, v, i);
            if(state == m) f(i - m + 1);
        }
    }

    int go(int state, span<const T> v, int idx) const{ // amortized O(1)
        if(!m) return 0;
        if(state == m) state = arr[m - 1];
        while(state && !match_chk(v, idx, state)) state = arr[state - 1];
        if(match_chk(v, idx, state)) state++;
        return state;
    }

    template <class F>
    void it_border(const F& f) const{ // O(m)
        if(!m) return;
        for(int x = arr[m - 1];x > 0;x = arr[x - 1]) f(x);
    }
}; _kmp <int> kmp;

int a[2 * MAX], b[MAX];
void run(){
    cin >> n >> m;
    for(int i = 1;i <= n;i++) cin >> a[i];
    for(int i = n + 1;i <= n + m - 1;i++) a[i] = a[i - n];

    for(int i = 1;i <= m;i++){
        cin >> b[i];
        if(mp.count(b[i])) eq[i] = mp[b[i]];
        auto ub = mp.upper_bound(b[i]);
        if(ub != mp.end()) hi[i] = ub->y;

        auto lb = mp.lower_bound(b[i]);
        if(lb != mp.begin()) lo[i] = (--lb)->y;

        mp[b[i]] = i;
    }

    kmp.set(span{b + 1, b + m + 1});

    int result = 0;
    kmp.it_match(span{a + 1, a + n + m}, [&](int cur){
        result++;
    });

    cout << result;
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}
