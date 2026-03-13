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
constexpr ll MAX = 201010; // SET MAX SIZE
constexpr ll MOD = 998244353;

ll result, sum[MAX], dp[MAX][2], tmp[MAX][2][2];
int p[MAX], c[MAX], ind[MAX], mi[MAX];
vector <int> adj[MAX], arr[MAX];

ll solve(ll cur, bool root){
    ll& ret = dp[cur][root];
    if(ret != -1) return ret; ret = INF;
    if(adj[cur].empty()) return ret = 0;

    ll sum = 0;
    if(!root){
        for(auto& nxt : adj[cur]){
            if(ind[nxt]) continue;
            sum += solve(nxt, 1) + c[nxt];
        }
        ret = min(ret, sum);
    }
    else{
        for(auto& nxt : adj[cur]){
            if(ind[nxt]) continue;
            sum += min(solve(nxt, 0), solve(nxt, 1) + c[nxt]);
        }
        ret = min(ret, sum);
    }
    
    return ret;
}

bool v[MAX];
void dfs(int cur, int root){
    if(v[cur]) return; v[cur] = 1;
    arr[root].push_back(cur);
    dfs(p[cur], root);
}

void run(){
    cin >> n; memset(dp, -1, sizeof(dp));
    for(int i = 1;i <= n;i++){
        cin >> p[i]; ind[p[i]]++;
        adj[p[i]].push_back(i);
    }
    for(int i = 1;i <= n;i++) cin >> c[i];

    deque <int> q;
    for(int i = 1;i <= n;i++) if(!ind[i]) q.push_back(i);
    while(!q.empty()){
        auto cur = q.front(); q.pop_front();
        if(!--ind[p[cur]]) q.push_back(p[cur]);
    }

    for(int i = 1;i <= n;i++){
        if(!ind[i]) continue;
        dfs(i, i);
    }

    for(int i = 1;i <= n;i++){
        if(arr[i].empty()) continue;
        if(arr[i].size() == 1){
            result += solve(arr[i][0], 1);
            continue;
        }

        for(int j = 0;j < arr[i].size();j++){
            tmp[j][0][0] = tmp[j][1][0] = INF;
            tmp[j][0][1] = tmp[j][1][1] = INF;
        }
        tmp[0][0][0] = solve(arr[i][0], 0);
        tmp[0][1][1] = solve(arr[i][0], 1) + c[arr[i][0]];

        for(int j = 1;j < arr[i].size();j++){
            auto cur = arr[i][j];
            for(int k = 0;k <= 1;k++){
                tmp[j][0][k] = tmp[j - 1][1][k] + solve(cur, 0);
                tmp[j][1][k] = min(tmp[j - 1][1][k], tmp[j - 1][0][k]) + c[cur] + solve(cur, 1);
            }
        }
        
        int sz = arr[i].size() - 1;
        result += min({tmp[sz][1][0], tmp[sz][0][1], tmp[sz][1][1]});
    }
    
    cout << result;
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}
