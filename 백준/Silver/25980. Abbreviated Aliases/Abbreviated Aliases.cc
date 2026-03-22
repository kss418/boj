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
constexpr ll MAX = 10101010; // SET MAX SIZE
constexpr ll MOD = 998244353;

vector <string> arr;
int result;
void run(){
    cin >> n >> m; 
    for(int i = 1;i <= n;i++){
        cin >> s;
        arr.push_back(s);
    }
    sort(all(arr));

    for(int i = 0;i < arr.size();i++){
        int now = 0, cnt = 0;
        if(i) for(int j = 0;j < min(arr[i].size(), arr[i - 1].size());j++){
            if(arr[i][j] != arr[i - 1][j]) break;
            cnt++;
        }
 
        now = cnt; cnt = 0;
        if(i + 1 != arr.size()) for(int j = 0;j < min(arr[i].size(), arr[i + 1].size());j++){
            if(arr[i][j] != arr[i + 1][j]) break;
            cnt++;
        }
        now = max(now, cnt);

        result += now + 1;
    }

    cout << result;
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}
