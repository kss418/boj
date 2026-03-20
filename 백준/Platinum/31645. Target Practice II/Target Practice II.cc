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
constexpr ll MAX = 40101; // SET MAX SIZE
constexpr ll MOD = 998244353;

ll x1;
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

ll cal(ll x, ll y, ll s){
    return y - s * x;
}

struct rat{
    ll p, q;
    bool operator < (const rat& ot) const{
        return (i128)p * ot.q < (i128)ot.p * q;
    }

    bool operator > (const rat& ot) const{
        return (i128)p * ot.q > (i128)ot.p * q;
    }
};

bool le(rat a, ll ot){
    return a.p < (i128)a.q * ot;
}

bool ge(rat a, ll ot){
    return a.p > (i128)a.q * ot;
}

vector <ll> neg, pos, slope;
vector <pll> l, u, d;

bool f1(ll mid){
    vector <rat> tmp;
    for(auto& [x, y] : u){
        tmp.push_back({y - mid, x});
    }

    sort(all(tmp)); sort(all(neg));
    for(int i = 0;i < n;i++){
        if(ge(tmp[i], neg[i])) return 0;
    }

    return 1;
}

bool f2(ll mid){
    vector <rat> tmp;
    for(auto& [x, y] : d){
        tmp.push_back({y - mid, x});
    }

    sort(all(tmp)); sort(all(pos));
    for(int i = 0;i < n;i++){
        if(le(tmp[i], pos[i])) return 0;
    }

    return 1;
}

void run(){
    cin >> n >> x1;
    l.clear(); u.clear(); d.clear();
    for(int i = 1;i <= n;i++){
        ll y1, y2, x2; cin >> y1 >> y2 >> x2;
        l.push_back({x1, y1});
        l.push_back({x1, y2});
        u.push_back({x2, y2});
        d.push_back({x2, y1});
    }

    neg.clear(); pos.clear(); slope.clear();
    for(int i = 1;i <= 4 * n;i++){
        int v; cin >> v;
        if(v >= 0) pos.push_back(v);
        if(v <= 0) neg.push_back(v);
    }

    if(pos.size() < n || neg.size() < n){
        cout << -1 << "\n"; return;
    }

    sort(all(pos)); sort(all(neg));
    reverse(all(neg));
    while(pos.size() > n){
        slope.push_back(pos.back());
        pos.pop_back();
    }

    while(neg.size() > n){
        slope.push_back(neg.back());
        neg.pop_back();
    }

    sort(all(slope));
    sort(all(l), [&](pll& a, pll& b){
        return a.y < b.y;
    });

    ll mn = INF, mx = MINF;
    for(int i = 0;i < 2 * n;i++){
        ll v = cal(l[i].x, l[i].y, slope[i]);
        mn = min(v, mn); mx = max(v, mx);
    }

    ll a = _bs::min_left(mx, 2e18, f1), b = _bs::max_right(-2e18, mn, f2);
    cout << a - b << "\n";
}

int main() {
    fastio; cin >> t;
    while(t--) run(); 

    return 0;
}
