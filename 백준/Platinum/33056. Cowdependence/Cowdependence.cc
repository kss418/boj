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

int sq, result[MAX], sum[MAX], nxt[MAX], all;
vector <int> arr[MAX];

class _bs { // integer
public:
    template <class F>
    static ll max_right(ll l, ll r, const F& f) {
        ll lo = l, hi = r, mid = -1;
        while (hi > lo) {
            mid = (hi + lo + 1) >> 1ll;
            if (f(mid)) lo = mid;
            else hi = mid - 1;
        }
        return lo;
    }

    template <class F>
    static ll min_left(ll l, ll r, const F& f) {
        ll lo = l, hi = r, mid = -1;
        while (hi > lo) {
            mid = (hi + lo) >> 1ll;
            if (f(mid)) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }
};

void solve_mn(int i){
    int sz = arr[i].size(); all++;
    vector <int> tmp;
    for(int g = 1;g <= sz;g++){
        auto f = [&](int cur){
            int la = arr[i][0], cnt = 1;
            for(auto& j : arr[i]){
                if(j - la <= cur) continue;
                la = j; cnt++; 
            }

            return cnt <= g;
        };

        tmp.push_back(_bs::min_left(1, n, f));
    }

    for(auto& i : tmp) sum[i - 1]++;
}

void solve_mx(int i){
    int sz = arr[i].size(); memset(nxt, -1, sizeof(nxt));
    for(auto& j : arr[i]) nxt[j] = j;
    for(int i = n - 1;i >= 1;i--){
        if(nxt[i] != -1) continue;
        nxt[i] = nxt[i + 1];
    }
    
    for(int j = 1;j <= n;j++){
        int now = 1, cur = arr[i][0];
        while(true){
            if(cur + j + 1 > n || nxt[cur + j + 1] == -1) break;
            cur = nxt[cur + j + 1]; now++;
        }

        result[j] += now;
    }
}

void run(){
    cin >> n; sq = sqrt(n) + 1;
    for(int i = 1;i <= n;i++){
        int g; cin >> g;
        arr[g].push_back(i);
    }

    for(int i = 1;i <= n;i++){
        if(arr[i].empty()) continue;

        int sz = arr[i].size();
        if(sz <= sq) solve_mn(i);
        else solve_mx(i);
    }

    for(int i = n;i >= 1;i--){
        all += sum[i];
        result[i] += all;
    }

    for(int i = 1;i <= n;i++) cout << result[i] << "\n";
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}
