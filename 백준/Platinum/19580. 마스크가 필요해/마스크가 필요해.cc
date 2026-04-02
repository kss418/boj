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

vector <pll> arr, mask;
priority_queue <ll, vector<ll>, greater<ll>> pq;
void run(){
    cin >> n >> m; 
    for(int i = 1;i <= n;i++){
        ll s, e; cin >> s >> e;
        arr.push_back({s, e});
    }

    while(m--){
        ll x, v; cin >> x >> v;
        mask.push_back({x, v});
    }
    sort(all(mask)); sort(all(arr));

    int idx = 0, result = 0;
    for(auto& [cur, v] : mask){
        while(idx < arr.size() && arr[idx].x <= cur){
            pq.push(arr[idx].y);
            idx++;
        }

        while(!pq.empty() && pq.top() < cur) pq.pop();
        while(!pq.empty() && v > 0){
            pq.pop();
            result++; v--;
        }
    }

    cout << result;
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}