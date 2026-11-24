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
constexpr ll MAX = 2010; // SET MAX SIZE
constexpr ll MOD = 998244353;
ll a[MAX][MAX], dp[MAX][MAX], result = MINF;
pll pre[MAX][MAX], suf[MAX][MAX];

pll merge(pll a, ll b){
    a.x = min(a.x, b);
    a.y = max(a.y, b);
    return a;
}

pll merge(pll a, pll b){
    a.x = min(a.x, b.x);
    a.y = max(a.y, b.y);
    return a;
}

void run(){
    cin >> n >> m; 
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            cin >> a[i][j];
            pre[i][j] = suf[i][j] = {INF, MINF};
        }
        pre[i][0] = suf[i][m + 1] = {INF, MINF};
    }
    
    for(int i = 1;i <= m;i++) dp[n][i] = (n % 2 ? a[n][i] : -a[n][i]);
    for(int i = n - 1;i >= 1;i--){
        for(int j = 1;j <= m;j++) pre[i + 1][j] = merge(pre[i + 1][j - 1], dp[i + 1][j]);
        for(int j = m;j >= 1;j--) suf[i + 1][j] = merge(suf[i + 1][j + 1], dp[i + 1][j]);

        for(int j = 1;j <= m;j++){
            pll now = merge(suf[i + 1][j + 1], pre[i + 1][j - 1]);
            dp[i][j] = (i % 2 ? now.x + a[i][j] : now.y - a[i][j]);
            dp[i][j] = (i % 2 ? min(dp[i][j], dp[i + 1][j] + a[i + 1][j] + a[i][j]) 
                : max(dp[i][j], dp[i + 1][j] - a[i + 1][j] - a[i][j]));
        }
    }

    for(int i = 1;i <= m;i++) result = max(result, dp[1][i]);
    cout << (result <= 0 ? "ibasic" : "djangg7") << " ";
    cout << abs(result);
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}