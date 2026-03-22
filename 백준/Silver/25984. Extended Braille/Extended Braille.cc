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

set <vector<pair<int, int>>> arr;
void run(){
    cin >> n;
    for(int i = 1;i <= n;i++){
        cin >> m;
        vector <pair<int, int>> tmp;
        for(int i = 1;i <= m;i++){
            int x, y; cin >> x >> y;
            tmp.push_back({x, y});
        }
        sort(all(tmp));

        for(int i = 0;i < tmp.size();i++){
            tmp[i].x -= tmp.back().x;
            tmp[i].y -= tmp.back().y;
        }

        arr.insert(tmp);
    }

    cout << arr.size();
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}
