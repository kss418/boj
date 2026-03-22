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
constexpr ll MAX = 505; // SET MAX SIZE
constexpr ll MOD = 998244353;

struct node{
    string st;
    ll p, q;
}; node arr[MAX];

unordered_map <string, vector<string>> adj;
unordered_map <string, ll> co, dp;
unordered_map <string, bool> flag;

ll dfs(const string& cur){
    if(dp.count(cur)) return dp[cur];
    ll mx = 0;
    for(auto& nxt : adj[cur]){
        mx = max(mx, dfs(nxt) + co[nxt]);
    }
    
    return dp[cur] = mx;
}

void run(){
    cin >> n;
    for(int i = 1;i <= n;i++){
        cin >> arr[i].st >> m;
        adj.clear(); co.clear(); 
        flag.clear(); dp.clear();

        for(int j = 1;j <= m;j++){
            int sz; cin >> s >> co[s] >> sz;
            flag[s] |= 0;
            for(int k = 1;k <= sz;k++){
                string sub; cin >> sub;
                adj[s].push_back(sub);
                flag[sub] = 1;
            }
        }

        ll a = 0, b = 0;
        for(auto& [str, f] : flag){
            a += co[str];
            if(f) continue;
            b = max(b, co[str] + dfs(str));
        }

        arr[i].p = a; arr[i].q = b;
    }

    sort(arr + 1, arr + n + 1, [&](node& a, node& b){
        return a.p * b.q < b.p * a.q;
    });

    for(int i = 1;i <= n;i++) cout << arr[i].st << "\n";
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}
