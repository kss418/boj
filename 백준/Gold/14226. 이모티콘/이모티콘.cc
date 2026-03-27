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

int result = 0x3f3f3f3f;
deque <pair<int, int>> q;
int d[MAX][MAX];
void run(){
    cin >> n; memset(d, 0x3f, sizeof(d));

    q.push_back({1, 0}); d[1][0] = 0;
    while(!q.empty()){
        auto [ca, cb] = q.front(); q.pop_front();
        if(ca + cb <= n && d[ca + cb][cb] > d[ca][cb] + 1){
            d[ca + cb][cb] = d[ca][cb] + 1;
            q.push_back({ca + cb, cb});
        }

        if(d[ca][ca] > d[ca][cb] + 1){
            d[ca][ca] = d[ca][cb] + 1;
            q.push_back({ca, ca});
        }

        if(ca > 1 && d[ca - 1][cb] > d[ca][cb] + 1){
            d[ca - 1][cb] = d[ca][cb] + 1;
            q.push_back({ca - 1, cb});
        }
    }

    for(int i = 0;i <= n;i++) result = min(result, d[n][i]);
    cout << result;
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}