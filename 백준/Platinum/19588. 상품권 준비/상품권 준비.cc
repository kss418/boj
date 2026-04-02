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

vector <pair<int, int>> arr;
class _st { // 0-base index
private:
    vector <vector<ll>> sum;
    vector <vector<int>> lift; ll m; int n, lg; 
public:
    _st(int n = 0, ll max_step = 0){ clear(n, max_step); }; // O(n log m)
    void clear(int n, ll m = 60){ // O(n log m)
        lg = 1; this->n = n; this->m = m;
        while((1ll << lg) <= m) lg++;
        lift.assign(lg + 1, vector<int>(n + 2, n + 1));
        sum.assign(lg + 1, vector<ll>(n + 2, 0));
    }

    void add(int st, int en, ll co = 1) { lift[0][st] = en; sum[0][st] = co; } // O(1)
    void build(){ // O(n log m)
        for(int i = 1;i <= lg;i++){
            for(int j = 0;j <= n;j++){
                int mid = lift[i - 1][j];
                lift[i][j] = lift[i - 1][mid];
                sum[i][j] = min(sum[i - 1][j] + sum[i - 1][mid], INF);
            }
        }
    }

    int next(int v) const{ return lift[0][v]; } // O(1)
    pair<int, ll> ret(int cur, ll k) const{ // O(log m)
        ll co = 0;
        for(int i = lg; i >= 0; i--){
            if(k < (1ll << i)) continue;
            co += sum[i][cur]; k -= (1ll << i); cur = lift[i][cur];
        }
        return {cur, co}; // 도착 정점, 사용한 비용
    }
}; _st st;

int pre[MAX];
void run(){
    cin >> n >> m; st.clear(n, n);
    for(int i = 1;i <= n;i++){
        int x, y; cin >> x >> y;
        arr.push_back({x, y});
    }
    sort(all(arr));

    for(int i = 1;i <= n;i++){
        pre[i] = pre[i - 1] ^ arr[i - 1].y;
        if(i < m) st.add(i, n + 1, 0);
        else st.add(i, i == m ? n + 1 : i - m, pre[i] ^ pre[i - m]);
    }

    st.build();
    cin >> k;
    while(k--){
        int a, b; cin >> a >> b;
        cout << st.ret(n - b, a).y << "\n";
    }
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}