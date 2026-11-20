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
constexpr ll MAX = 5010; // SET MAX SIZE
constexpr ll MOD = 998244353;
vector <ll> arr[2];
ll result, tmp[MAX];
bool mx, f[MAX];
deque <ll> num[2];

ll cal(ll idx){
    ll l1 = 0, l2 = 0;
    for(int i = 1;i <= n;i++) tmp[i] = 0;
    tmp[idx] = n;    

    for(int i = 1;i <= idx - 1;i++){
        if(!f[i]) continue;
        tmp[i] = arr[1][l2++];
    }

    for(int i = n;i >= idx + 1;i--){
        if(f[i]) continue;
        tmp[i] = arr[0][l1++];
    }

    num[0].clear(); num[1].clear();
    for(int i = l1;i < arr[0].size();i++) num[0].push_back(arr[0][i]);
    for(int i = l2;i < arr[1].size();i++) num[1].push_back(arr[1][i]);

    ll mx = 0, ret = 1;
    for(int i = 1;i <= idx - 1;i++){
        mx = max(mx, tmp[i]);
        if(f[i]) continue;
        while(!num[0].empty() && num[0].front() <= mx) num[0].pop_front();
        if(num[0].empty()) continue;
        num[0].pop_front(); ret++;
    }

    for(int i = n;i >= idx + 1;i--){
        mx = max(mx, tmp[i]);
        if(!f[i]) continue;
        while(!num[1].empty() && num[1].front() <= mx) num[1].pop_front();
        if(num[1].empty()) continue;
        num[1].pop_front(); ret++;
    }

    return ret;
}

void run(){
    cin >> n;
    for(int i = 1;i <= n;i++){
        int v; char c;
        cin >> v >> c;
        f[i] = c == 'R';
        arr[c == 'R'].push_back(v);
        if(v == n) mx = (c == 'R');
    }

    sort(all(arr[0])); sort(all(arr[1]));
    arr[mx].pop_back();

    for(int i = 1;i <= n;i++){
        if(f[i] != mx) continue;
        result = max(result, cal(i));
    }

    cout << result;
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}
