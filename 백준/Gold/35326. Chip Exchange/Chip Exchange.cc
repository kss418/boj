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

void run(){
    ll a, b, need, cb, ca; cin >> a >> b >> ca >> cb >> need;

    ll cnt = b / cb;
    a += cnt * ca; b %= cb; 
    if(a >= need){
        cout << 0 << "\n";
        return;
    }
    
    if(ca >= cb){
        ll result = cb - b - 1, diff = max(need - a, 0ll);
        result += diff;
        cout << result << "\n";
    }
    else{
        ll diff = max(need - a, 0ll), result = 0;
        ll cnt = diff / ca + (diff % ca ? 1 : 0);
        ll req = need;
        req -= a; req -= cnt * ca;
        a += cnt * ca;

        result += max(req - 1, 0ll);
        result += max(cb * max(cnt, 0ll) - b, 0ll);
        result += max(ca - (a - need) % ca - 1, 0ll);
        cout << result << "\n";
    }
}

int main() {
    fastio; cin >> t;
    while(t--) run(); 

    return 0;
}