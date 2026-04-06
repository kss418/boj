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
        if(!pat[nxt]) return !pat[cur] || pat[cur] >= nxt;
        return pat[cur] == pat[nxt];
    }

    bool match_chk(span<const T> v, int idx, int state) const{
        if(!pat[state]) return !v[idx] || v[idx] >= state;
        return pat[state] == v[idx];
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

vector <int> v[2];
int la[2][26];

int findP(char T[], char P[], int N, int M){
    memset(la, -1, sizeof(la));
    v[0].resize(N); v[1].resize(M);
    for(int i = 0;i < N;i++){
        int l = la[0][T[i] - 'a'];
        v[0][i] = (l == -1 ? 0 : i - l);
        la[0][T[i] - 'a'] = i;
    }

    for(int i = 0;i < M;i++){
        int l = la[1][P[i] - 'a'];
        v[1][i] = (l == -1 ? 0 : i - l);
        la[1][P[i] - 'a'] = i;
    }

    int ret = 0; kmp.set(v[1]);
    kmp.it_match(v[0], [&](int cur){
        ret++;
    });

    return ret;
}
