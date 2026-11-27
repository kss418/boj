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
constexpr ll MAX = 1010101; // SET MAX SIZE
constexpr ll MOD = 987654321;

class _ls{
private:
    vector <int> lp, prime, vphi, vmu; int n = 0, flag = 0;
public:
    static constexpr int with_phi = 1, with_mobius = 2;

    _ls() = default;
    _ls(int n, int flag = 0) : n(n), flag(flag){ build(); }

    void make(int n, int flag = 0){ this->n = n; this->flag = flag; } // O(1)

    void build(){ // O(n)
        bool do_phi = flag & with_phi, do_mu = flag & with_mobius;
        prime.clear(); vphi.clear(); vmu.clear();
        lp.assign(n + 1, 0);
        if(n >= 3) prime.reserve((int)(n / log((ld)n)) + 10);
        if(do_phi){ vphi.assign(n + 1, 0); if(n >= 1) vphi[1] = 1; }
        if(do_mu){ vmu.assign(n + 1, 0); if(n >= 1) vmu[1] = 1; }

        for(int i = 2;i <= n;i++){
            if(!lp[i]){
                lp[i] = i;
                prime.push_back(i);
                if(do_phi) vphi[i] = i - 1;
                if(do_mu) vmu[i] = -1;
            }

            int least = lp[i];
            for(int p : prime){
                ll x = 1ll * p * i;
                if(x > n) break;
                lp[x] = p;

                if(p == least){
                    if(do_phi) vphi[x] = vphi[i] * p;
                    if(do_mu) vmu[x] = 0;
                    break;
                }
                if(do_phi) vphi[x] = vphi[i] * (p - 1);
                if(do_mu) vmu[x] = -vmu[i];
            }
        }
    }

    const vector<int>& ret() const{ return prime; } // O(1)
    int count() const{ return prime.size(); } // O(1)
    int count(int l, int r) const{ // O(log pi(n))
        if(l > r) return 0;
        return upper_bound(all(prime), r) - lower_bound(all(prime), l);
    }
    template <class F>
    void it_prime(const F& f) const{ for(int p : prime) f(p); } // O(pi(n))
    bool is_prime(int x) const{ return x >= 2 && lp[x] == x; }

    template <class F>
    void it_factor(int x, const F& f) const{ // O(log x)
        while(x != 1){
            int p = lp[x], c = 0;
            do{ x /= p; c++; }while(lp[x] == p);
            f(p, c);
        }
    }

    vector <ll> factorize(int x) const{ // 소인수분해 (1 <= x <= n)
        vector <ll> ret;
        while(x != 1){
            ret.push_back(lp[x]);
            x /= lp[x];
        }
        return ret;
    }

    vector <pll> factorize_cnt(int x) const{ // p^c 꼴로 소인수분해 (1 <= x <= n)
        vector <pll> ret;
        it_factor(x, [&](int p, int c){ ret.emplace_back(p, c); });
        return ret;
    }

    ll divisor_num(int x) const{ // 약수의 개수
        if(!x) return 0;
        ll ret = 1;
        it_factor(x, [&](int, int c){ ret *= c + 1; });
        return ret;
    }

    ll divisor_sum(int x) const{ // 약수의 합
        if(!x) return 0;
        ll ret = 1;
        it_factor(x, [&](int p, int c){
            ll sum = 1, cur = 1;
            for(int i = 0;i < c;i++){
                cur *= p;
                sum += cur;
            }
            ret *= sum;
        });
        return ret;
    }

    vector <ll> divisor(int x) const{ // 약수 벡터 반환
        if(!x) return {};
        vector <ll> ret = {1};
        it_factor(x, [&](int p, int c){
            ll mul = 1;
            int sz = ret.size();
            for(int k = 0;k < c;k++){
                mul *= p;
                for(int i = 0;i < sz;i++) ret.push_back(ret[i] * mul);
            }
        });

        sort(all(ret));
        return ret;
    }

    ll phi(int x) const { return vphi[x]; } // 오일러 피
    ll mobius(int x) const { return vmu[x]; } // 뫼비우스
}; _ls ls(MAX);
int mx[MAX];

ll pow(ll a, ll b){
    ll ret = 1;
    for(int i = 1;i <= b;i++){
        ret *= a;
        ret %= MOD;
    }
    return ret;
}

void run(){
    cin >> n; 
    for(int i = 2;i <= n;i++){
        auto fc = ls.factorize_cnt(i);
        for(auto& [v, c] : fc) mx[v] = max<int>(mx[v], c);
    }

    ll result = 1;
    for(int i = 2;i <= n;i++){
        result *= pow(i, mx[i]);
        result %= MOD;
    }

    cout << result;
}

int main() {
    fastio; // cin >> t;
    while(t--) run(); 

    return 0;
}