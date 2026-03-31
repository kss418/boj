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
constexpr ll MAX = 22; // SET MAX SIZE
constexpr ll MOD = 998244353;

int a[MAX][MAX], dp[MAX][1ll << MAX];
int solve(int cur, int cnt){
    if(cur == -1) return 0;
    int& ret = dp[cur][cnt];
    if(ret != -1) return ret; ret = 0x3f3f3f3f;

    for(int i = 0;i < n;i++){
        if(cnt & (1ll << i)) continue;
        ret = min(ret, solve(cur - 1, cnt ^ (1ll << i)) + a[cur][i]);
    }

    return ret;
}

void run(){
    cin >> n; memset(dp, -1, sizeof(dp));
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++) cin >> a[i][j];
    }

    cout << solve(n - 1, 0);
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}