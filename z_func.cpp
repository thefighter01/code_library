#include<iostream>
#include <bits/stdc++.h>
#include <ext/numeric>
using namespace std;
#include<ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
//using LL = __int128;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define clz(n) __builtin_clz(n)//31 -x
#define nd "\n"
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rand(ll l , ll r) { return uniform_int_distribution<ll>(l, r)(rng); }
const  double PI = acos(-1.0);  double EPS = 1e-9; ll INF = 2e18+5;   ll B1 = 200117 , B2 = 200201; const ll N = 2e5+10, LOG = 20 , inf = 1e9, SQ= 200 , mod=1e9+7, mod2 = 998244353 , P1 = 31 , P2 = 29;
template<class container> void print(container v) { for (auto& it : v) cout << it << ' ' ;cout <<endl;}
template <typename T> using ordered_set =  tree<T, null_type,less<T>, rb_tree_tag,tree_order_statistics_node_update>;
ll fp(ll a , ll p){ if(!p) return 1; ll v = fp(a , p/2); v*=v;return p & 1 ? v*a : v;  }
template< typename  T > using min_heap = priority_queue <T , vector <T >  , greater < T > >;
//# define int long long
#define all(x) x.begin() , x.end()
#define makeUnique(v)  sort(all(v)) , v.resize(unique(all(v))-v.begin());
#define popcount(x)  __builtin_popcount(x)
 
ll mul (ll a, ll b , ll m){
    return ((a % m) *  (b % m)) % m;
}
ll add (ll a , ll b , ll m){
    return ((a+b) % m + m) % m;
}
ll Fp (ll b , ll p , ll m){
    if (!p) return 1;
    ll v = Fp(b , p >> 1 , m);
    v = mul(v , v , m);
    if (p & 1) v = mul(v , b , m);
    return v;
}
ll modInv(ll n , ll m){
    return Fp(n , m-2 , m);
}
int dx[] {0 , 0 , -1 , 1 ,-1 , 1 , 1 , -1};
int dy[] {-1 , 1 , 0 , 0 , -1 , 1 , -1 , 1};
 
const int M = 6e6+30;
 
 
vector <int > z_function(string & s){
    int n = (int)s.length();
    vector <int > z(n);
    int l , r; l = r = 0;
    for (int i = 1; i < n; ++i){
        if (i < r) z[i] = min(r - i , z[i - l]);
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] > r){
            l = i;
            r = i + z[i];
        }
    }
    return z;
}
 
void main_(int tc){
    int n , l , r; cin >> n >> l >> r;
    string s; cin >> s;
    auto z = z_function(s);
    vector < vector < int > > g(n+5);
    for (int i = 0; i < n; ++i) g[z[i]].push_back(i);
    set<int > st = {n};
    vector <int > ans(n+5) , f(n+5);
    for (int i = n; i ; --i){
        for (auto &cur : g[i]) st.emplace(cur);
        auto cur = 0;
        while(cur < n){
            f[i]++;
            cur = *st.lower_bound(cur + i);
        }
        ans[f[i]] = max(ans[f[i]] , i);
    }
    for (int i = n; i; --i) ans[i] = max(ans[i] , ans[i+1]);
    for (int i = l; i <= r; ++i) cout << ans[i] << " \n"[i == r];
 
}
 
 
 
 
signed main() {
    ios_base::sync_with_stdio(0);cin.tie(0); cout.tie(0);
    int tt = 0, tc = 0;cin >> tt;
    while (tt--) main_(++tc);
    return 0;
}
// look at my code
// my code is amazing
