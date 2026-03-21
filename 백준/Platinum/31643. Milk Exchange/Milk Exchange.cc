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
constexpr ll MAX = 501010; // SET MAX SIZE
constexpr ll MOD = 998244353;

int tmp[MAX], a[MAX];
ll pre[MAX], result;
vector <int> stk;
void run(){
    cin >> n; int mn = 0x3f3f3f3f, idx = -1;
    for(int i = 0;i < n;i++){
        cin >> tmp[i]; result += tmp[i];
        if(mn < tmp[i]) continue;
        idx = i; mn = tmp[i];
    }
    
    for(int i = 0;i < n;i++) a[i] = tmp[(i + idx + n + 1) % n];

    for(int i = n - 1;i >= 0;i--){
        while(!stk.empty() && a[stk.back()] >= a[i]){
            if(stk.size() > 1){
                int t1 = stk.back(), t2 = stk[stk.size() - 2];
                int d = a[t1] - a[t2];
                pre[t2 - t1] += d;
                pre[t2 - i] -= d;
            }
    
            stk.pop_back();
        }

        stk.push_back(i);
    }

    while(stk.size() > 1){
        int t1 = stk.back(), t2 = stk[stk.size() - 2];
        int d = a[t1] - a[t2];
        pre[t2 - t1] += d;
        pre[t2 + 1] -= d;
        stk.pop_back();
    }

    for(int i = 1;i <= n;i++){
        pre[i] += pre[i - 1];
        result -= pre[i];
        cout << result << "\n";
    }
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}