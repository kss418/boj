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

int a[MAX];
void run(){
    cin >> n >> m >> k;
    if(m + k > n + 1){
        cout << -1; return;
    }

    for(int i = 1;i <= n;i++) a[i] = 1;
    for(int i = n;i > n - k + 1;i--) a[i] = n - i + 1;
    if(m == 1) a[1] = k;
    else{
        a[n - k + 1] = max(m, k);
        int now = m - 1;
        for(int i = n - k;i >= 1;i--){
            if(!now) break;
            a[i] = now--;
        }
    }

    for(int i = 1;i <= n;i++) cout << a[i] << " ";
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}
