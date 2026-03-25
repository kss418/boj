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
constexpr ll MAX = 201; // SET MAX SIZE
constexpr ll MOD = 998244353;

string st[MAX], tmp[MAX];
int dx[4] = {0, 0, 1, -1}, dy[4] = {-1, 1, 0, 0}, cnt = 0;
bool out(int cy, int cx){
    return cy < 0 || cx < 0 || cy >= n || cx >= m;
}

void exp(){
    for(int i = 0;i < n;i++){
        tmp[i] = st[i];
        for(int j = 0;j < m;j++){
            bool flag = st[i][j] == 'O';
            for(int k = 0;k < 4;k++){
                int ny = i + dy[k], nx = j + dx[k];
                if(out(ny, nx)) continue;
                if(st[ny][nx] == 'O') flag = 1;
            }

            tmp[i][j] = flag ? '.' : 'O';
        }
    }

    for(int i = 0;i < n;i++) st[i] = tmp[i];
}

void run(){
    cin >> n >> m >> k;
    for(int i = 0;i < n;i++) cin >> st[i];
    if(k == 1){
        for(int i = 0;i < n;i++) cout << st[i] << "\n";
        return;
    }

    k %= 4;
    if(k == 1){
        exp(); exp();
        for(int i = 0;i < n;i++) cout << st[i] << "\n";
    }
    else if(k % 2 == 0){
        for(int i = 0;i < n;i++){
            for(int j = 0;j < m;j++) cout << 'O';
            cout << "\n";
        }
    }
    else{
        exp();
        for(int i = 0;i < n;i++) cout << st[i] << "\n";
    }
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}
