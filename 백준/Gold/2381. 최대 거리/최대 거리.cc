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

using pi = pair<int, int>;
vector <pi> arr1, arr2;
int dist(const pi& a, const pi& b){
    return abs(a.x - b.x) + abs(a.y - b.y);
}

void run(){
    cin >> n;
    for(int i = 1;i <= n;i++){
        int x, y; cin >> x >> y;
        arr1.push_back({x, y});
        arr2.push_back({x, y});
    }

    sort(all(arr1), [&](pi& a, pi& b){
        return a.x + a.y < b.x + b.y;
    });

    sort(all(arr2), [&](pi& a, pi& b){
        return a.x - a.y < b.x - b.y;
    });

    vector <pi> vec;
    vec.push_back(arr1[0]);
    vec.push_back(arr1.back());
    vec.push_back(arr2[0]);
    vec.push_back(arr2.back());

    int result = 0;
    for(auto& i : vec){
        for(auto& j : vec) result = max(result, dist(i, j));
    }

    cout << result;
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}
