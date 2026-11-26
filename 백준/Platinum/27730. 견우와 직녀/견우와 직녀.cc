#include <bits/stdc++.h>
#define fastio cin.tie(0), cout.tie(0), ios::sync_with_stdio(0);
#define all(x) (x).begin(), (x).end()
#define x first 
#define y second
using namespace std; using ll = long long; using u64 = uint64_t;
using ld = long double; using pld = pair<ld, ld>;
using i128 = __int128_t; using f128 = __float128; 
using pll = pair<ll, ll>; using tll = tuple<ll, ll, ll>;
ll n, m, k, t = 1; 

constexpr ll INF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MINF = 0xc0c0c0c0c0c0c0c0;
constexpr ll MAX = 101010; // SET MAX SIZE
constexpr ll MOD = 998244353;
vector <pair<int, int>> adj[MAX];
ll dp[MAX], c[MAX], s[MAX], mn, result;
ll ai, bi;

ll cnt(ll cur, ll pre = -1){
    ll& ret = c[cur];
    if(ret != -1) return ret; ret = 1;
    for(auto& [nxt, co] : adj[cur]){
        if(nxt == pre) continue;
        ret += cnt(nxt, cur);
    }
    return ret;
}

ll solve(ll cur, ll pre = -1){
    ll& ret = dp[cur];
    if(ret != -1) return ret; ret = 0;
    for(auto& [nxt, co] : adj[cur]){
        if(nxt == pre) continue;
        ret += solve(nxt, cur) + c[nxt] * co;
    }
    return ret;
}

void reroot(ll cur, ll& idx, ll pre = -1, ll rev = 0){
    if(dp[cur] + rev < mn){
        mn = dp[cur] + rev;
        idx = cur;
    }

    for(auto& [nxt, co] : adj[cur]){
        if(nxt == pre) continue;
        ll nr = rev + dp[cur] - dp[nxt] - c[nxt] * co;
        nr += co * (c[1] - c[nxt]);
        reroot(nxt, idx, cur, nr);
    }
}

void clear(){
    for(int i = 1;i <= m;i++) adj[i].clear();
    memset(dp, -1, sizeof(dp));
    memset(c, -1, sizeof(c));
    mn = INF;
}

void run(){
    cin >> n; clear();
    for(int i = 1;i < n;i++){
        ll s, e, c; cin >> s >> e >> c;
        adj[s].push_back({e, c});
        adj[e].push_back({s, c});
    }
    cnt(1); solve(1); reroot(1, ai);

    cin >> m; result += mn * m; clear();
    for(int i = 1;i < m;i++){
        ll s, e, c; cin >> s >> e >> c;
        adj[s].push_back({e, c});
        adj[e].push_back({s, c});
    }
    cnt(1); solve(1); reroot(1, bi);
    
    result += mn * n;
    cout << ai << " " << bi << "\n";
    cout << result + n * m;
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}