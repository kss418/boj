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
    array<u64, N> basis{};
    _xor_basis(){ clear(); }
    void clear(){ basis.fill(0); }

    bool insert(u64 x){
        for(int i = N - 1; i >= 0; i--){
            if(((x >> i) & 1ull) == 0) continue;
            if(!basis[i]){
                basis[i] = x;
                return true;
            }
            x ^= basis[i];
        }
        return false;
    }

    bool can_make(u64 x) const {
        for(int i = N - 1; i >= 0; i--) {
            if(((x >> i) & 1ull) == 0) continue;
            if(!basis[i]) return false;
            x ^= basis[i];
        }
        return true;
    }

    u64 max_xor(u64 x = 0) const {
        u64 ret = x;
        for(int i = N - 1; i >= 0; i--) ret = max(ret, ret ^ basis[i]);
        return ret;
    }

    u64 min_xor(u64 x = 0) const {
        u64 ret = x;
        for(int i = N - 1; i >= 0; i--) ret = min(ret, ret ^ basis[i]);
        return ret;
    }

    int rank() const {
        int ret = 0;
        for(int i = 0; i < N; i++) if(basis[i]) ret++;
        return ret;
    }
}; _xor_basis xb;

void run(){
    cin >> n; 
    for(int i = 0; i < n; i++){
        u64 x;
        cin >> x;
        xb.insert(x);
    }

    cout << xb.max_xor();
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}
