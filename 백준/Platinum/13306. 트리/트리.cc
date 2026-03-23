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
int p[MAX], sz[MAX], pa[MAX];

int find(int x){
    if(p[x] == -1) return x;
    return p[x] = find(p[x]);
}

void merge(int a, int b){
    a = find(a); b = find(b);
    if(a == b) return;
    if(sz[a] < sz[b]) swap(a, b);
    p[b] = a; sz[a] += sz[b];
}

vector <tuple<int, int, int>> query;
vector <string> result;
void run(){
    cin >> n >> m; memset(p, -1, sizeof(p));
    for(int i = 2;i <= n;i++) cin >> pa[i];
    for(int i = 1;i <= n;i++) sz[i] = 1;

    int q = n + m - 1;
    while(q--){
        int op; cin >> op;
        if(!op){
            int x; cin >> x;
            query.push_back({op, x, pa[x]});
        }
        else{
            int a, b; cin >> a >> b;
            query.push_back({op, a, b});
        }
    }

    reverse(all(query));
    for(auto& [op, a, b] : query){
        if(!op) merge(a, b);
        else{
            result.push_back(find(a) == find(b) ? "YES" : "NO");
        }
    }

    reverse(all(result));
    for(auto& i : result) cout << i << "\n";
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}