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

ll a[MAX], sum;
void run(){
    cin >> n; 
    for(int i = 1;i <= n;i++){
        cin >> a[i];
        sum += a[i];
    }

    sort(a + 1, a + n + 1);
    if(n == 1){ cout << a[1]; return; }
    if(a[n] >= sum - a[n]){ cout << a[n] - (sum - a[n]); return; }
    cout << sum % 2;
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}