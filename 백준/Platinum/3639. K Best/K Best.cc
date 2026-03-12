#include <bits/stdc++.h>
#define fastio cin.tie(0), cout.tie(0), ios::sync_with_stdio(0);
#define all(x) (x).begin(), (x).end()
#define x first 
#define y second
using namespace std; using ll = long long;
using ld = long double; using pld = pair<ld, ld>;
using i128 = __int128_t; using f128 = __float128; 
using pll = pair<ll, ll>; using tll = tuple<ll, ll, ll>;
ll n, m, k, t = 1; string s;

constexpr ll INF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MINF = 0xc0c0c0c0c0c0c0c0;
constexpr ll MAX = 101010; // SET MAX SIZE
constexpr ll MOD = 998244353;

vector <ll> result;
class node{
public:
    ll x, y, idx;
}; vector <node> arr;

ld ebs = 1e-9;
template <typename T = ll>
class _bs { // 0-based index
public:
    T l, r;
    _bs(T l, T r) {
        this->l = l; this->r = r;
    }

    bool f(T cur) {
        sort(all(arr), [cur](node l, node r){
            return (ld)l.x - cur * (ld)l.y > (ld)r.x - cur * (ld)r.y;
        });

        ld sum = 0;
        for(int i = 0;i < m;i++) sum += arr[i].x - cur * arr[i].y;
        if(sum < -ebs) return 0;

        result.clear();
        for(int i = 0;i < m;i++) result.push_back(arr[i].idx);
        return 1;
    }

    T ret() {
        T lo = l, hi = r, mid = -1;
        while (hi - lo > ebs) {
            mid = (hi + lo) / (T)2;
            if (f(mid)) lo = mid;
            else hi = mid;
        }

        return lo;
    }
};

void run(){
    cin >> n >> m;
    for(int i = 1;i <= n;i++){
        ll v, w; cin >> v >> w;
        arr.push_back({v, w, i});
    }

    _bs <ld> bs(0, 2e7); bs.ret();
    for(auto& i : result) cout << i << " ";
}

int main() {
    fastio; // cin >> t;
    while(t--) run();
    
    return 0;
}