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
constexpr ll MAX = 101010; // SET MAX SIZE
constexpr ll MOD = 998244353;

vector <ll> pos, neg;
void run(){
    cin >> n; ll result = 0;
    for(int i = 1;i <= n;i++){
        int v; cin >> v;
        if(v == 1){ result++; continue; }
        (v > 0 ? pos : neg).push_back(v);
    }

    sort(all(pos)); reverse(all(pos)); sort(all(neg));
    for(int i = 0;i + 1 < pos.size();i += 2) result += pos[i] * pos[i + 1];
    if(pos.size() % 2) result += pos.back();

    for(int i = 0;i + 1 < neg.size();i += 2) result += neg[i] * neg[i + 1];
    if(neg.size() % 2) result += neg.back();
    cout << result;
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}