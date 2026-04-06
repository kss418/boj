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
int lift[22][MAX];

void build(){
    for(int i = 1;i < 22;i++){
        for(int x = 1;x <= n;x++){
            int mid = lift[i - 1][x];
            lift[i][x] = lift[i - 1][mid];
        }
    }
}

int query(int x, int v){
    for(int i = 0;i < 22;i++){
        if((v & (1 << i)) == 0) continue;
        x = lift[i][x];
    }

    return x;
}

void run(){
    cin >> n;
    for(int i = 1;i <= n;i++) cin >> lift[0][i];
    build();

    cin >> m;
    while(m--){
        int v, x; cin >> v >> x;
        cout << query(x, v) << "\n";
    }
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}
