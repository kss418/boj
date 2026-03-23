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
constexpr ll MAX = 1010; // SET MAX SIZE
constexpr ll MOD = 998244353;
int p[MAX], sz[MAX];
vector <int> arr[MAX];


int find(int x){
    if(p[x] == -1) return x;
    return p[x] = find(p[x]);
}

void merge(int a, int b){
    a = find(a); b = find(b);
    if(a == b) return;
    if(sz[a] < sz[b]) swap(a, b);
    p[b] = a; sz[a] += sz[b];
}

void run(){
    cin >> n >> m; memset(p, -1, sizeof(p));
    for(int i = 1;i <= n;i++) sz[i] = 1;

    while(m--){
        char op; int a, b; cin >> op >> a >> b;
        if(op == 'F'){
            merge(a, b);
        }
        else{
            arr[a].push_back(b);
            arr[b].push_back(a);
        }
    }

    for(int i = 1;i <= n;i++){
        if(arr[i].empty()) continue;
        for(int j = 1;j < arr[i].size();j++){
            merge(arr[i][0], arr[i][j]);
        }
    }

    int result = 0;
    for(int i = 1;i <= n;i++){
        if(find(i) != i) continue;
        result++;
    }

    cout << result;
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}