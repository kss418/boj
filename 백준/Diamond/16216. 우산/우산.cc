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
constexpr ll MAX = 5010; // SET MAX SIZE
constexpr ll MOD = 998244353;

class _vtree{
private:
    vector <vector <int>> lift; 
    vector <int> in, out, dep;
    vector <ll> dist;
    int n, seq, lg;
    bool is_ancestor(int a, int b){
        return in[a] <= in[b] && out[b] <= out[a];
    }

    void sort_node(vector <int>& node){
        sort(all(node), [&](int a, int b){
            return in[a] < in[b];
        });
    }

    int lca(int a, int b){
        if(is_ancestor(a, b)) return a;
        if(is_ancestor(b, a)) return b;
        for(int i = lg - 1;i >= 0;i--){
            if(!is_ancestor(lift[a][i], b)) a = lift[a][i];
        }
        return lift[a][0]; 
    }
public:
    vector <vector<pair<int, ll>>> adj, vt;
    _vtree(int n = 0){ clear(n); }
    void clear(int n){
        this->n = n; seq = 0; lg = __lg(n + 1) + 1;
        adj.assign(n + 1, vector <pair<int, ll>>());
        vt.assign(n + 1, vector <pair<int, ll>>());
        lift.assign(n + 1, vector <int>(lg + 1, 0));
        in.assign(n + 1, 0); out.assign(n + 1, 0);
        dist.assign(n + 1, 0); dep.assign(n + 1, 0);
    }

    void add(int s, int e, ll c){
        adj[s].push_back({e, c});
        adj[e].push_back({s, c});
    }

    vector <int> build(vector <int> node){
        if(node.empty()) return {};
        sort_node(node);

        int sz = node.size();
        for(int i = 0;i < sz - 1;i++) node.push_back(lca(node[i], node[i + 1]));

        sort_node(node);
        node.erase(unique(all(node)), node.end());
        
        vector<int> st;
        st.push_back(node[0]);
        for(int i = 1;i < node.size();i++){
            int v = node[i];
            while(!st.empty() && !is_ancestor(st.back(), v)){
                st.pop_back();
            }

            vt[st.back()].push_back({v, dist[v] - dist[st.back()]});
            st.push_back(v);
        }
        return node;
    }

    void dfs(int cur, int pre = -1){
        if(pre == -1) pre = cur;
        in[cur] = ++seq;
        lift[cur][0] = pre;
        for(int i = 1;i < lg;i++){
            lift[cur][i] = lift[lift[cur][i - 1]][i - 1];
        }

        for(auto& [nxt, co] : adj[cur]){
            if(nxt == pre) continue;
            dep[nxt] = dep[cur] + 1;
            dist[nxt] = dist[cur] + co;
            dfs(nxt, cur);
        }
        out[cur] = seq;
    }

    ll d(int a, int b){
        return dist[a] - dist[b];
    }
}; _vtree vt;

vector <int> arr;
ll dp1[2 * MAX][MAX], dp2[2 * MAX][MAX];
ll tmp1[MAX], tmp2[MAX];
int ind[301010], p[301010], sz[301010], num[301010];
deque <int> q;
bool flag[301010];

void mn(ll& a, ll b){
    a = min(a, b);
}

void run(){
    cin >> n >> m; vt.clear(n);
    for(int i = 1;i < n;i++){
        int s, e; cin >> s >> e;
        vt.add(s, e, 1);
    }

    memset(dp1, 0x3f, sizeof(dp1));
    memset(dp2, 0x3f, sizeof(dp2));
    for(int i = 1;i <= m;i++){
        int v; cin >> v;
        flag[v] = 1;
        arr.push_back(v);
    }

    vt.dfs(1); arr.push_back(1);
    auto node = vt.build(arr);
    for(int i = 0;i < node.size();i++) num[node[i]] = i + 1;
    for(auto& i : node){
        for(auto& j : vt.vt[i]) p[j.x] = i, ind[i]++;
    }

    for(auto& i : node){
        dp1[num[i]][0] = dp2[num[i]][0] = 0;
        sz[i] = flag[i];

        if(flag[i]) dp1[num[i]][1] = dp2[num[i]][1] = 0;
        if(ind[i]) continue;
        q.push_back(i);
    }

    while(!q.empty()){
        auto cur = q.front(); q.pop_front();
        if(!p[cur]) continue;
        int nxt = p[cur], nn = num[nxt], cn = num[cur];

        memset(tmp1, 0x3f, sizeof(tmp1)); memset(tmp2, 0x3f, sizeof(tmp2));
        for(int i = 0;i <= sz[nxt];i++){
            for(int j = 0;j <= sz[cur];j++){
                mn(tmp1[i + j] , dp1[nn][i] + dp1[cn][j] + (j == 0 ? 0 : 2 * vt.d(cur, nxt)));
            }

            for(int j = 0;j <= sz[cur];j++){
                mn(tmp2[i + j], dp1[nn][i] + dp2[cn][j] + (j == 0 ? 0 : vt.d(cur, nxt)));
                mn(tmp2[i + j], dp2[nn][i] + dp1[cn][j] + (j == 0 ? 0 : 2 * vt.d(cur, nxt)));
            }
        }

        for(int i = 0;i <= sz[nxt] + sz[cur];i++) dp1[nn][i] = tmp1[i], dp2[nn][i] = tmp2[i];

        sz[nxt] += sz[cur];
        if(!--ind[nxt]) q.push_back(nxt);
    }

    for(int i = 1;i <= m;i++) cout << dp2[num[1]][i] << "\n";
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}
