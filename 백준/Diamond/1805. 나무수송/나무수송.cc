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
constexpr ll MAX = 101; // SET MAX SIZE
constexpr ll MOD = 998244353;

int w[MAX], p[MAX], c[MAX], d[MAX];
int dp[MAX][MAX][55], sz[MAX];
vector <int> adj[MAX];

void dfs(int cur){
    sz[cur] = 1;
    for(auto& nxt : adj[cur]){
        d[nxt] = d[cur] + c[nxt];
        dfs(nxt);
        sz[cur] += sz[nxt];
    }
}

void mn(int& a, int b){
    a = min(a, b);
}

int solve(int cur, int la, int cnt){
    int& ret = dp[cur][la][cnt];
    if(ret != -1) return ret; ret = 0x3f3f3f3f;
    if(adj[cur].empty()) ret = 0;

    vector<vector<int>> arr(adj[cur].size() + 1);
    for(int i = 0;i <= adj[cur].size();i++) arr[i].assign(cnt + 1, 0x3f3f3f3f);
    arr[0][0] = 0;
    
    int now = 1;
    for(int i = 0;i < adj[cur].size();i++){
        int nxt = adj[cur][i];
        for(int j = 0;j <= now;j++){
            for(int k = 0;k <= sz[nxt];k++){
                if(j + k > cnt) break;
                mn(arr[i + 1][j + k], arr[i][j] + solve(nxt, la, k));
                if(k) mn(arr[i + 1][j + k], arr[i][j] + solve(nxt, nxt, k - 1));
            }
        }

        now += sz[nxt];
    }

    ret = arr[adj[cur].size()][cnt];
    return ret += w[cur] * (d[cur] - d[la]);
}

void run(){
    cin >> n >> m; memset(dp, -1, sizeof(dp));
    for(int i = 1;i <= n;i++){
        cin >> w[i] >> p[i] >> c[i];
        adj[p[i]].push_back(i);
    }

    dfs(0);
    cout << solve(0, 0, m);
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}
