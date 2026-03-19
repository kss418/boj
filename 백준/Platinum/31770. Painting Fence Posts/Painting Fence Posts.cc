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
pi a[MAX];
vector <pair <pi, pi>> arr;
int result[MAX];
unordered_map <int, vector<pi>> mx, my;
unordered_map <int, set<int>> vx, vy;
map <pi, ll> d;
map <ll, int> sum, org;
set <ll> c;
vector <int> adj[MAX];
vector <ll> cs;
bool v[MAX];
ll all;

void mkg(unordered_map <int, vector<pi>>& mp){
    for(auto& [i, v] : mp){
        sort(all(v));
        for(int i = 0;i < v.size();i += 2){
            int a = v[i].y, b = v[i + 1].y;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
    }
}

void dfs(int cur, ll dist = 0, int pre = -1){
    if(cur == 1 && v[cur]){
        all = dist; return;
    }

    org[dist] = cur;
    v[cur] = 1; cs.push_back(dist);
    auto& [cx, cy] = a[cur];
    for(auto& nxt : adj[cur]){
        if(pre == nxt) continue;
        if(nxt != 1 && v[nxt]) continue;
        auto& [nx, ny] = a[nxt];
        if(cy == ny){
            if(cx < nx){
                auto it = vy[cy].lower_bound(cx);
                while(it != vy[cy].end() && *it <= nx){
                    d[{*it, cy}] = dist + *it - cx;
                    ++it;
                }
            }
            else{
                auto it = vy[cy].upper_bound(cx);
                while(it != vy[cy].begin()){
                    --it;
                    if(*it < nx) break;
                    d[{*it, cy}] = dist + cx - *it;
                }
            }
        }
        else{
            if(cy < ny){
                auto it = vx[cx].lower_bound(cy);
                while(it != vx[cx].end() && *it <= ny){
                    d[{cx, *it}] = dist + *it - cy;
                    ++it;
                }
            }
            else{
                auto it = vx[cx].upper_bound(cy);
                while(it != vx[cx].begin()){
                    --it;
                    if(*it < ny) break;
                    d[{cx, *it}] = dist + cy - *it;
                }
            }
        }

        dfs(nxt, dist + abs(ny - cy) + abs(nx - cx), cur);
    }
}

void run(){
    cin >> n >> m;
    for(int i = 1;i <= m;i++){
        cin >> a[i].x >> a[i].y;
        mx[a[i].x].push_back({a[i].y, i});
        my[a[i].y].push_back({a[i].x, i});
    }

    mkg(mx); mkg(my); 
    while(n--){
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        arr.push_back({{x1, y1}, {x2, y2}});
        vx[x1].insert(y1); vy[y1].insert(x1);
        vx[x2].insert(y2); vy[y2].insert(x2);
    }
    
    dfs(1);
    for(auto& i : cs) c.insert(i), c.insert(i + all);

    for(auto& [s, e] : arr){
        ll mn = d[s], mx = d[e];
        if(mn > mx) swap(mn, mx);
        if(mx - mn < mn + all - mx){
            auto lb = c.lower_bound(mn);
            auto ub = c.upper_bound(mx);
            sum[*lb]++; 
            if(ub != c.end()) sum[*ub]--;
        }
        else{
            auto lb = c.lower_bound(mx);
            auto ub = c.upper_bound(mn + all);
            sum[*lb]++;
            if(ub != c.end()) sum[*ub]--;
        }
    }

    int now = 0;
    for(auto& i : c){
        now += sum[i];
        int idx = (i >= all ? org[i - all] : org[i]);
        result[idx] += now;
    }

    for(int i = 1;i <= m;i++) cout << result[i] << "\n";
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}
