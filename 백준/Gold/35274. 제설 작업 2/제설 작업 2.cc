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

ll a[MAX], tmp[MAX];
bool f(ll cur){
    ll cnt = 0, idx = 1;
    for(int i = 1;i <= n;i++) tmp[i] = a[i];

    while(idx <= n){
        ll div = tmp[idx] / cur;
        cnt += div; tmp[idx] -= div * cur;

        if(!tmp[idx]){
            idx++; continue;
        }

        ll use = cur; cnt++; 
        ll mn = min(tmp[idx], use);
        tmp[idx] -= mn; use -= mn; idx++;
        if(idx > n) break;

        for(int i = 1;i < k;i++){
            ll mn = min(tmp[idx], use);
            tmp[idx] -= mn; use -= mn;
            if(!tmp[idx]) idx++;
            if(!use || idx > n) break;
        }
    }

    return cnt <= m;
}

void run(){
    cin >> n >> m >> k;
    for(int i = 1;i <= n;i++) cin >> a[i];

    ll ret = _bs::min_left(1, 1e16 + 1, f);
    cout << (ret == 1e16 + 1 ? -1 : ret);
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}
