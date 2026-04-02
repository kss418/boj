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

struct node{
    int x, y, z;
};
vector <pair<int, int>> adj[MAX];
node co[MAX], result = {-0x3f3f3f3f, -0x3f3f3f3f, -0x3f3f3f3f};

void push(node& p, int v){
    if(v > p.x) p.z = p.y, p.y = p.x, p.x = v;
    else if(v > p.y) p.z = p.y, p.y = v;
    else if(v > p.z) p.z = v;
}

void init(){
    for(int i = 1;i <= n;i++){
        co[i] = {0, -0x3f3f3f3f, -0x3f3f3f3f};
    }
}

void f(const node& a, const node& b){
    for(auto& i : {a.x, a.y, a.z}){
        for(auto& j : {b.x, b.y, b.z}) push(result, i + j);
    }
}

void dfs(int cur, int pre = -1){
    bool flag = 1;
    node tmp = {0, -0x3f3f3f3f, -0x3f3f3f3f};
    for(auto& [nxt, c] : adj[cur]){
        if(nxt == pre) continue;
        dfs(nxt, cur);
        f(tmp, {co[nxt].x + c, co[nxt].y + c, co[nxt].z + c});

        push(tmp, co[nxt].x + c);
        push(tmp, co[nxt].y + c);
        push(tmp, co[nxt].z + c);
    }

    co[cur] = tmp;
}

void run(){
    cin >> n; init();
    for(int i = 1;i < n;i++){
        int s, e, c; cin >> s >> e >> c;
        adj[s].push_back({e, c});
        adj[e].push_back({s, c});
    }

    dfs(1); 
    cout << result.y;
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}