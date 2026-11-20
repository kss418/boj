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
constexpr ll MAX = 501; // SET MAX SIZE
constexpr ll MOD = 998244353;
int a[MAX][MAX], num[MAX][MAX], result[MAX][MAX];
int pre[MAX], sum[MAX], tmp[MAX];

void run(){
    cin >> n >> m;
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++) cin >> a[i][j], result[i][j] = 0xc0c0c0c0;
    }

    for(int i = 1;i <= n;i++){
        for(int j = i;j <= n;j++){
            int mn = 0;
            for(int k = 1;k <= m;k++){
                sum[k] += a[j][k];
                pre[k] = pre[k - 1] + sum[k];

                num[j][k] = -mn;
                mn = min(mn, pre[k]);
            }

            int mx = 0xc0c0c0c0;
            for(int k = m;k >= 1;k--){
                mx = max(mx, pre[k]);
                num[j][k] += mx;
            }
        }

        for(int k = 1;k <= m;k++) tmp[k] = 0xc0c0c0c0;
        for(int j = n;j >= i;j--){
            for(int k = 1;k <= m;k++){
                tmp[k] = max(tmp[k], num[j][k]);
                result[j][k] = max(result[j][k], tmp[k]);
            }
        }

        for(int k = 1;k <= m;k++) sum[k] = 0;
    }

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++) cout << result[i][j] << " ";
        cout << "\n";
    }
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}
