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

template <u64 mod> requires (mod > 0)
class _mint{
private:
    using mint = _mint;
    using u128 = __uint128_t;
public:
    u64 v;
    template <integral T = int>
    constexpr _mint(T v = 0) : v(norm((i128)v)){}
    static constexpr u64 get_mod(){ return mod; }
    static constexpr u64 norm(i128 x){ x %= mod; return (u64)(x < 0 ? x + mod : x); }
    static constexpr tuple <u64, i128, i128> gcd(u64 a, u64 b){
        if(!b) return {a, 1, 0};
        auto [g, x, y] = gcd(b, a % b);
        return {g, y, x - (a / b) * y};
    }

    constexpr mint inv() const{
        assert(v);
        auto [g, x, y] = gcd(v, mod);
        assert(g == 1);
        return mint(x);
    }

    constexpr mint pow(u64 e) const{
        mint a = *this, ret(1);
        while(e){
            if(e & 1) ret *= a;
            a *= a; e >>= 1;
        }
        return ret;
    }

    constexpr mint& operator+=(const mint& a){
        u64 b = a.v;
        if(v >= mod - b) v -= mod - b;
        else v += b;
        return *this;
    }

    constexpr mint& operator-=(const mint& a){
        u64 b = a.v;
        if(v < b) v += mod - b;
        else v -= b;
        return *this;
    }

    constexpr mint& operator*=(const mint& a){ v = (u64)((u128)v * a.v % mod); return *this; }
    constexpr mint& operator/=(const mint& a){ return *this *= a.inv(); }
    friend constexpr mint operator+(mint a, const mint& b){ return a += b; }
    friend constexpr mint operator-(mint a, const mint& b){ return a -= b; }
    friend constexpr mint operator*(mint a, const mint& b){ return a *= b; }
    friend constexpr mint operator/(mint a, const mint& b){ return a /= b; }
    friend constexpr bool operator==(const mint& a, const mint& b){ return a.v == b.v; }
    constexpr mint operator+() const{ return *this; }
    constexpr mint operator-() const{ auto ret = *this; ret.v = v ? mod - v : 0; return ret; }
    friend ostream& operator<<(ostream& out, const mint& a){ return out << a.v; }
    friend istream& operator>>(istream& in, mint& a){ ll v; if(in >> v) a = v; return in; }
};

template <u64 mod = 998244353>
class _comb{ // mod == prime
public:
    using mint = _mint<mod>;
private:
    vector <mint> fac, ifac; int n;
public:
    _comb(int n = 0){ build(n); } // O(n + log mod)

    void build(int n){ // O(n + log mod)
        assert(n >= 0 && (u64)n < mod);
        this->n = n; fac.resize(n + 1); ifac.resize(n + 1);
        fac[0] = 1;
        for(int i = 1;i <= n;i++) fac[i] = fac[i - 1] * i;
        ifac[n] = fac[n].pow(mod - 2);
        for(int i = n - 1;i >= 0;i--) ifac[i] = ifac[i + 1] * (i + 1);
    }

    u64 comb(int n, int r) const{ // O(1)
        if(n < 0 || r < 0 || n < r) return 0;
        return (fac[n] * ifac[r] * ifac[n - r]).v;
    }

    u64 perm(int n, int r) const{ // O(1)
        if(n < 0 || r < 0 || n < r) return 0;
        return (fac[n] * ifac[n - r]).v;
    }

    u64 multicomb(int n, int r) const{ // O(1)
        if(n < 0 || r < 0) return 0;
        if(!n) return !r;
        ll total = (ll)n + r - 1;
        assert(total <= this->n);
        return comb((int)total, r);
    }

    u64 factorial(int n) const{ return fac[n].v; } // O(1)
    u64 inv_factorial(int n) const{ return ifac[n].v; } // O(1)
}; _comb <MOD> comb;

void run(){
    cin >> n >> m; comb = {n};
    _mint <MOD> result = 1;
    
    ll div = n / m, mod = n % m;
    for(int i = 1;i <= mod;i++){
        result *= comb.comb(n, div + 1);
        n -= div + 1;
    }
   
    for(int i = mod + 1;i <= m;i++){
        result *= comb.comb(n, div);
        n -= div;
    }

    cout << result;
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}