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

int a[MAX], sum[MAX], result = 0x3f3f3f3f;
short dp[MAX];

short solve(int cur, int l, int r){
    short& ret = dp[cur];
    if(ret != 0x3f3f) return ret; ret = 0xc0c0;
    if(!cur) return ret = 0;

    for(int i = 0;i < cur;i++){
        int diff = sum[cur] - sum[i];
        if(diff < l || diff > r) continue;
        ret = max<char>(ret, solve(i, l, r) + 1);
    }

    return ret;
}

void run(){
    cin >> n;
    for(int i = 1;i <= n;i++) cin >> a[i], sum[i] = sum[i - 1] + a[i];

    for(int i = 1;i <= 50101;i++){
        auto f = [&](int mid)-> bool {
            memset(dp, 0x3f, sizeof(dp));
            short ret = solve(n, i, i + mid);
            return ret >= 2;
        };

        int now = _bs::min_left(0, 50102, f);
        if(now >= 50102) continue;
        result = min(result, now);
    }

    cout << result;
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}