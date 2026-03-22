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

string tmp;
int result[26];
vector <int> arr[26];
void run(){
    cin >> n >> m >> k >> tmp >> s;
    for(int i = 0;i < s.size();i++){
        arr[s[i] - 'a'].push_back(i);
    }

    for(auto& i : tmp){
        if(arr[i - 'a'].empty()) continue;
        int la = arr[i - 'a'][0]; result[i - 'a'] = 2 * k + m;
        for(int idx = 1;idx < arr[i - 'a'].size();idx++){
            auto& now = arr[i - 'a'][idx];
            if(now == la + 1) result[i - 'a'] += m;
            else{
                result[i - 'a'] += min(2 * k, (now - la - 1) * n) + m;
            }

            la = now;
        }
    }

    for(auto& i : tmp) cout << result[i - 'a'] << "\n";
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}
