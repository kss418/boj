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
int a[MAX][MAX];
ll sum[MAX][MAX];

struct node{
    int y, x; ll v;
    bool operator<(const node& ot) const{
        return v < ot.v;
    }
};
priority_queue <node> pq;

void run(){
    cin >> n >> m >> k;
    for(int i = m;i <= n;i++){
        for(int j = m;j <= n;j++) pq.push({i, j, 0});
    }

    while(k--){
        int x, y, v; cin >> x >> y >> v;
        for(int i = max<int>(y, m);i < min(y + m, n + 1);i++){
            for(int j = max<int>(x, m);j < min(x + m, n + 1);j++){
                sum[i][j] += v - a[y][x];
                pq.push({i, j, sum[i][j]});
            }
        }

        a[y][x] = v;
        while(1){
            auto [cy, cx, now] = pq.top();
            if(sum[cy][cx] != now) pq.pop();
            else{
                cout << now << "\n";
                break;
            }
        }
    }
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}