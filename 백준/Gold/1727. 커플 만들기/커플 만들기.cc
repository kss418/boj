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
constexpr ll MAX = 1010; // SET MAX SIZE
constexpr ll MOD = 998244353;

using pi = pair<int, int>;
pi dp[MAX][MAX];
int a[MAX], b[MAX];

pi f(const pi& a, const pi& b){
    return {a.x + b.x, a.y + b.y};
}

pi c(const pi& a, const pi& b){
    if(a.x == b.x){
        return a.y < b.y ? a : b;
    }
    return a.x < b.x ? b : a;
}

pi solve(int l, int r){
    pi& ret = dp[l][r];
    if(ret != pi(-1, -1)) return ret; ret = {0, 0x3f3f3f3f};
    if(!l && !r) return ret = {0, 0};

    if(l) ret = c(ret, f(solve(l - 1, r), {0, 0}));
    if(r) ret = c(ret, f(solve(l, r - 1), {0, 0}));
    if(l && r) ret = c(ret, f(solve(l - 1, r - 1), {1, abs(a[l] - b[r])}));

    return ret;
}

void init(){
    for(int i = 0;i <= n;i++){
        for(int j = 0;j <= m;j++) dp[i][j] = {-1, -1};
    }
}

void run(){
    cin >> n >> m; init();
    for(int i = 1;i <= n;i++) cin >> a[i];
    for(int i = 1;i <= m;i++) cin >> b[i];
    sort(a + 1, a + n + 1); sort(b + 1, b + m + 1);

    cout << solve(n, m).y;
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}
