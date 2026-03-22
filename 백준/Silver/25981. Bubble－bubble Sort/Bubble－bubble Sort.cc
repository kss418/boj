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
constexpr ll MAX = 2525; // SET MAX SIZE
constexpr ll MOD = 998244353;

int a[MAX], result;
bool chk(){
    for(int i = 1;i < n;i++){
        if(a[i + 1] < a[i]) return 0;
    }
    return 1;
}

void run(){
    cin >> n >> m;
    for(int i = 1;i <= n;i++) cin >> a[i];


    for(int i = 1;i <= n;i++){
        if(chk()) break;
        for(int j = 1;j <= n - m + 1;j++){
            sort(a + j, a + j + m);
        }
        
        result++;
    }

    cout << result;
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}
