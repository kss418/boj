#include <bits/stdc++.h>
#define fastio 	cin.tie(0), cout.tie(0),ios::sync_with_stdio(0);
using namespace std; typedef long long ll;
typedef pair<int, int> pi; typedef pair<ll, ll> pll;
typedef unsigned long long ull;
ll n, m, k, t; string s;


const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MAX = 201010;

struct query{
  ll num, a, b;
};

ll p[MAX]; stack <query> st;
stack <int> result;
ll uf[MAX];

ll find(ll a){
    if(uf[a] < 0) return a;
    return uf[a] = find(uf[a]);
}

void merge(ll a, ll b){
    a = find(a); b = find(b);
    if(a == b) return;
    uf[b] = a;
}


int main() {
	fastio;
	
	memset(uf,-1,sizeof(uf));
	cin >> n >> m;
	for(int i = 2; i <= n;i++){
	    cin >> p[i];
	}
	
	ll ag = m + n - 1;
	while(ag--){
	    ll num,a,b;
	    b = 0;
	    cin >> num;
	    
	    if(!num){
	        cin >> a;
	    }
	    else{
	        cin >> a >> b;
	    }
	    
	    query cur = {num,a,b};
	    st.push(cur);
	}
	
	while(!st.empty()){
	    query cur = st.top();
	    st.pop();
	    if(cur.num){
	        result.push(find(cur.a) == find(cur.b));
	    }
	    else{
	        merge(cur.a,p[cur.a]);
	    }
	}
	
	while(!result.empty()){
	    if(result.top() == 1) cout << "YES\n";
	    else cout << "NO\n";
	    result.pop();
	}

   
    
	return 0;
}