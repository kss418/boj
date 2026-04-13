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

vector <pair <int, int>> adj[MAX];
int dp[MAX][MAX][2], sz[MAX], ind[MAX], tmp[MAX][2];
int arr[MAX][MAX];
pair <int, int> p[MAX];
deque <int> q;
vector <int> result;

void mn(int& a, int b){
    a = min(a, b);
}

void dfs(int cur, int pre = -1){
    for(auto& [nxt, co] : adj[cur]){
        if(nxt == pre) continue;
        p[nxt] = {cur, co}; 
        ind[cur]++;
        dfs(nxt, cur);
    }
}

void track(int cur, int cnt, bool use, int pre = -1){
    if(use) result.push_back(cur);

    int need = cnt - use;
    vector <pair<int, int>> c;
    for(auto& [nxt, co] : adj[cur]){
        if(nxt == pre) continue;
        c.push_back({nxt, co});
    }

    vector<vector<int>> arr(c.size() + 1);
    for(int i = 0;i <= c.size();i++){
        arr[i].assign(cnt + 1, 0x3f3f3f3f);
    }
    arr[0][0] = 0;

    for(int i = 0;i < c.size();i++){
        auto& [nxt, co] = c[i];
        for(int j = 0;j <= need;j++){
            if(arr[i][j] == 0x3f3f3f3f) continue;
            for(int k = 0;k <= min(sz[nxt], need - j);k++){
                mn(arr[i + 1][j + k], arr[i][j] + dp[nxt][k][0] + (use ? 0 : co));
                mn(arr[i + 1][j + k], arr[i][j] + dp[nxt][k][1] + (use ? co : 0));
            }
        }
    }

    int now = need;
    for(int i = c.size() - 1;i >= 0;i--){
        auto& [nxt, co] = c[i];
        for(int j = 0;j <= min(sz[nxt], now);j++){
            if(arr[i][now - j] == 0x3f3f3f3f) continue;
            int v0 = arr[i][now - j] + dp[nxt][j][0] + (use ? 0 : co);
            if(v0 == arr[i + 1][now]){
                track(nxt, j, 0, cur);
                now -= j;
                break;
            }

            int v1 = arr[i][now - j] + dp[nxt][j][1] + (use ? co : 0);
            if(v1 == arr[i + 1][now]){
                track(nxt, j, 1, cur);
                now -= j;
                break;
            }
        }
    }
}

void run(){
    cin >> n >> m;
    for(int i = 1;i < n;i++){
        int s, e, c; cin >> s >> e >> c;
        adj[s].push_back({e, c});
        adj[e].push_back({s, c});
    }

    dfs(1); memset(dp, 0x3f, sizeof(dp));
    for(int i = 1;i <= n;i++){
        sz[i] = 1;
        dp[i][0][0] = 0;
        dp[i][1][1] = 0;
        if(!ind[i]) q.push_back(i);
    }

    while(!q.empty()){
        int cur = q.front(); q.pop_front();
        auto& [nxt, co] = p[cur];
        if(!nxt) continue;

        for(int i = 0;i <= sz[cur] + sz[nxt];i++){
            tmp[i][0] = tmp[i][1] = 0x3f3f3f3f;
        }

        for(int i = 0;i <= sz[nxt];i++){
            for(int j = 0;j <= sz[cur];j++){
                mn(tmp[i + j][0], dp[nxt][i][0] + dp[cur][j][0] + co);
                mn(tmp[i + j][0], dp[nxt][i][0] + dp[cur][j][1]);

                mn(tmp[i + j][1], dp[nxt][i][1] + dp[cur][j][0]);
                mn(tmp[i + j][1], dp[nxt][i][1] + dp[cur][j][1] + co);
            }
        }

        for(int i = 0; i <= sz[cur] + sz[nxt]; i++){
            dp[nxt][i][0] = tmp[i][0];
            dp[nxt][i][1] = tmp[i][1];
        }
  
        sz[nxt] += sz[cur];
        if(!--ind[nxt]) q.push_back(nxt);
    }

    cout << min(dp[1][m][0], dp[1][m][1]) << "\n";
    track(1, m, dp[1][m][1] <= dp[1][m][0]);

    sort(all(result));
    for(auto& i : result) cout << i << " ";
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}
