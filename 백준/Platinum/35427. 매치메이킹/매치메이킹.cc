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
priority_queue <tll, vector<tll>, greater<tll>> pq;
map <ll, vector<ll>> mp;

bool chk(ll a, ll b){
    if(!mp.count(a)) return 0;
    auto lb = --mp.lower_bound(a);
    auto ub = mp.upper_bound(a);
    return lb->x == b || ub->x == b;
}

void push(ll x){
    if(x == MINF || x == INF) return;
    if(mp.count(x) && mp[x].size() >= 2) pq.push({0, x, x});
    else{
        auto lb = --mp.lower_bound(x);
        auto ub = mp.upper_bound(x);
        pq.push({x - lb->x, lb->x, x});
        pq.push({ub->x - x, x, ub->x});
    }
}

void prop(ll x){
    auto lb = --mp.lower_bound(x);
    auto ub = mp.upper_bound(x);
    push(lb->x); push(ub->x);
}

void print(ll l, ll r){
    cout << mp[l].back() << " ";
    mp[l].pop_back();
    cout << mp[r].back() << "\n";
    mp[r].pop_back();

    if(mp[l].empty()) mp.erase(l);
    if(mp[r].empty()) mp.erase(r);
    prop(l); prop(r);
}

void pop(){
    while(1){
        auto [d, l, r] = pq.top(); pq.pop();
        if(!d && mp.count(l) && mp[l].size() >= 2){
            print(l, r); break;
        }
        else if(d && chk(l, r)){
            print(l, r); break;
        }
    }
}

void run(){
    cin >> m; 
    mp[MINF].push_back(0);
    mp[INF].push_back(0);
    while(m--){
        ll op; cin >> op;
        if(op == 1){
            ll x, v; cin >> x >> v;
            mp[v].push_back(x);
            push(v);
        }
        else pop();
    }
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}
