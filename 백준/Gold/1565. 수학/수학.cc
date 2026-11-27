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
int a[MAX], b[MAX];
map <ll, ll> mx, mn;

namespace _gcd{
    constexpr tll build(ll a, ll b){ // O(log max(|a|, |b|))
        i128 g = a, r = b, x = 1, y = 0, nx = 0, ny = 1;
        while(r){
            i128 q = g / r, tmp = g % r;
            g = r; r = tmp;
            tmp = x - q * nx; x = nx; nx = tmp;
            tmp = y - q * ny; y = ny; ny = tmp;
        }
        if(g < 0){ g = -g; x = -x; y = -y; }
        return {(ll)g, (ll)x, (ll)y};
    }

    constexpr ll ret(ll a, ll b){ // O(log max(|a|, |b|))
        i128 x = a, y = b;
        while(y){ i128 tmp = x % y; x = y; y = tmp; }
        return (ll)(x < 0 ? -x : x);
    }

    constexpr ll inv(ll a, ll mod){ // O(log mod)
        auto [g, x, y] = build(a, mod);
        if(g != 1) return -1;
        x %= mod;
        return x < 0 ? x + mod : x;
    }

    constexpr optional<pll> solve(ll a, ll b, ll mod){ // O(log mod)
        auto [g, x, y] = build(a, mod);
        if(b % g) return nullopt;
        ll period = mod / g;
        i128 value = (i128)x * (b / g) % period;
        if(value < 0) value += period;
        return pll{(ll)value, period};
    }
}

void op1(ll cur){
    for(ll i = 2;i * i <= cur;i++){
        ll now = 0;
        while(cur % i == 0){
            cur /= i;
            now++;
        }

        if(!now) continue;
        if(!mx.count(i)) mx[i] = now;
        mx[i] = max(mx[i], now); 
    }

    if(cur <= 1) return;
    if(!mx.count(cur)) mx[cur] = 1;
    mx[cur] = max(mx[cur], 1ll);
}

void op2(ll cur){
    for(ll i = 2;i * i <= cur;i++){
        ll now = 0;
        while(cur % i == 0){
            cur /= i;
            now++;
        }

        if(!mn.count(i)) mn[i] = now;
        mn[i] = min(mn[i], now); 
    }

    if(cur <= 1) return;
    if(!mn.count(cur)) mn[cur] = 1;
    mn[cur] = min(mn[cur], 1ll);
}

void run(){
    cin >> n >> m; ll g = 0;
    for(int i = 1;i <= n;i++) cin >> a[i], op1(a[i]);
    for(int i = 1;i <= m;i++){
        cin >> b[i];
        g = _gcd::ret(g, b[i]);
    }

    op2(g);
    bool flag = 1;
    ll result = 1;

    for(auto& [v, c] : mn){
        result *= mn[v] - mx[v] + 1;
        if(mx[v] > mn[v]) flag = 0;
    }

    for(auto& [v, c] : mx){
        if(mx[v] > mn[v]) flag = 0;
    }

    cout << (flag ? result : 0) << "\n";
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}