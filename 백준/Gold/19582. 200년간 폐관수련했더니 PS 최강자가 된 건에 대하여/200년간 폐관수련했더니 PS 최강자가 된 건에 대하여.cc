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

int dp[MAX][2];
void run(){
    cin >> n; memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    for(int i = 1;i <= n;i++){
        int x, p; cin >> x >> p;
        if(dp[i - 1][0] <= x){
            dp[i][0] = min(dp[i - 1][0] + p, 0x3f3f3f3f);
        }

        if(dp[i - 1][1] <= x){
            dp[i][1] = min(dp[i - 1][1] + p, 0x3f3f3f3f);
        }

        dp[i][1] = min({dp[i][1], dp[i - 1][0], 0x3f3f3f3f});
    }

    cout << (dp[n][1] == 0x3f3f3f3f ? "Zzz" : "Kkeo-eok");
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}