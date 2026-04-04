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

template <size_t N = 63>
class _xor_basis{
public:
    array<u64, N> basis{}; int rk = 0;
    _xor_basis(){ clear(); } // O(max_bit)
    void clear(){ basis.fill(0); rk = 0; } // O(max_bit)

    bool insert(u64 x){ // O(max_bit)
        for(int i = (int)N - 1; i >= 0; i--){
            if(((x >> i) & 1ull) == 0) continue;
            if(!basis[i]){
                basis[i] = x; rk++;
                return 1;
            }
            x ^= basis[i];
        }
        return 0;
    }

    bool can_make(u64 x) const{ // O(max_bit)
        for(int i = (int)N - 1; i >= 0; i--){
            if(((x >> i) & 1ull) == 0) continue;
            if(!basis[i]) return 0;
            x ^= basis[i];
        }
        return 1;
    }

    u64 max_xor(u64 x = 0) const{ // O(max_bit)
        u64 ret = x;
        for(int i = (int)N - 1; i >= 0; i--) ret = max(ret, ret ^ basis[i]);
        return ret;
    }

    u64 min_xor(u64 x = 0) const{ // O(max_bit)
        u64 ret = x;
        for(int i = (int)N - 1; i >= 0; i--) ret = min(ret, ret ^ basis[i]);
        return ret;
    }

    int rank() const{ return rk; } // O(1)
}; _xor_basis xb;

bool flag = 1;
ll a[MAX];
void run(){
    cin >> n >> m; 
    for(int i = 1;i <= n;i++){
        cin >> a[i];
        a[i] ^= (1ll << m) - 1;
        flag &= xb.insert(a[i]);
    }

    if(!flag) cout << (1ll << m) - 1;
    else{
        u64 ret = ULLONG_MAX;
        for(auto& i : xb.basis){
            if(i) ret = min(ret, i);
        }
        cout << (ret ^ ((1ll << m) - 1));
    }
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}