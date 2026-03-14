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
constexpr ll MOD = 1e9 + 7;

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

ll org[MAX], v[MAX]; int a, b;
bool f(ll cur){
    ll use = 0;
    for(int i = 1;i <= a;i++){
        use += min(m, max(0ll, cur - org[i]));
    }

    return use <= (a - b) * m;
}

void run(){
    cin >> n >> m >> a >> b; 
    for(int i = 1;i <= n;i++) cin >> org[i];
    sort(org + 1, org + n + 1); reverse(org + 1, org + n + 1);

    ll mx = _bs::max_right(0, 1e15, f), use = (a - b) * m;
    for(int i = 1;i <= n;i++) v[i] = org[i];
    for(int i = 1;i <= a;i++){
        ll u = min(m, max(0ll, mx - org[i]));
        v[i] = org[i] + u; use -= u;
    }

    for(int i = a;i >= 1;i--){
        if(v[i] - org[i] == m || use <= 0) continue;
        v[i]++; use--;
    }

    ll result = 0;
    for(int i = 1;i <= n;i++){
        ll c = v[i] % MOD, sq = (c * c) % MOD;
        result += sq; result %= MOD;
    }

    cout << result;
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}