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

int cnt[22][22][22], ret[MAX];  
int cal(int bit){
    int now = 0;
    for(int i = 0;i < n;i++){
        if(bit & (1 << i)) continue;
        for(int j = 0;j < n;j++){
            if(!(bit & (1 << j))) continue;
            for(int k = j + 1;k < n;k++){
                if(!(bit & (1 << k))) continue;
                now += cnt[i][j][k];
            }
        }
    }
    
    return now;
}

void run(){
    cin >> n >> m; 
    for(int i = 1;i <= m;i++){
        int x, y, z; cin >> x >> y >> z;
        if(y > z) swap(y, z);
        cnt[x - 1][y - 1][z - 1]++;
    }

    for(int i = 0;i < (1ll << n);i++) ret[cal(i)]++;

    for(int i = MAX - 1;i >= 1;i--){
        if(!ret[i]) continue;
        cout << i << " " << ret[i]; return;
    }
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}