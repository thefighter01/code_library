
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
const  double PI = acos(-1.0);  double EPS = 1e-9; const int M = 5000 + 5; ll INF = 1e17+5;  const ll B1 = 200117 , B2 = 200201; const ll N = 1e6+10, LOG = 20 , inf = 1e9, SQ= 200 , mod=1e9+7, mod2 = 998244353 , P1 = 31 , P2 = 29;
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
 
 
 
int nodes;
const int mm = 70 * 2e5;
ll val[mm] ;
int ls[mm] ,rs[mm];
int extend(){
    int cur = ++ nodes;
    assert(cur < mm);
    val[cur] = ls[cur] = rs[cur] = 0;
    return cur;
}
 
void modify(int l, int r, int p, int &x, ll v) {
    if(!x) x = extend();
    val[x] = max(val[x] , v);
    if(l == r) return;
    int m = l + r >> 1;
    if(p <= m) modify(l, m, p, ls[x], v);
    else modify(m + 1, r, p, rs[x], v);
}
ll query(int l, int r, int ql, int qr, int x) {
    if(ql <= l && r <= qr || !x) return val[x];
    int m = (l + r) >> 1;
    ll ans = 0;
    if(ql <= m) ans = max(ans , query(l, m, ql, qr, ls[x]) ) ;
    if(m < qr) ans = max( ans , query(m + 1, r, ql, qr, rs[x]) ) ;
    return ans;
}
int mx;
ll solve(int root , int L , int R){
    return query(0 , mx , L , R , root);
}
 
struct fen{
    int n;
    vector < int > t;
    void init(int _n){
        n= _n +5;
        t = vector < int > (n+5);
    }
    void upd (int _h , ll x , int c){
        int h = _h;
        while(h){
            modify(0 , mx , c , t[h] , x);
            h-= h & -h;
        }
    }
    ll fnd(int x , int R){
        ll  ans = 0;
 
        while(x <= n) {
            ans = max(ans , solve(t[x] , 0 , R));
            x+= x & -x;
        }
        return ans;
    }
};
 
struct prefix{
    int n;
    vector <int > t;
    void init(int _n){
        n = _n + 5;
        t = vector <int > (n+5);
    }
    ll query(int x , int R){
        ll ans = 0;
        while(x){
            ans = max(ans , solve(t[x] , 0 , R));
            x-= x & -x;
        }
        return ans;
    }
    void upd(int _h , ll v , int c){
        int h = _h;
        while(h <= n){
            modify(0 , mx , c , t[h] , v);
            h+= h & -h;
        }
    }
};
void main_(int tc){
    int n; cin >> n;  mx = n+5; nodes = 0;
    vector < array<int , 3 > > a(n);
    for (auto &i : a) for (int j = 0; j < 3; ++j) cin >> i[j];
    int r = 0;
    for (auto &i : a) r = max(r , i[1]);
    vector <ll > dp(n+5);
    vector <int > root(r+5);
    prefix pre; fen suf; pre.init(r+5);
    suf.init(r+5);
    for (int i = 0; i < n; ++i){
        ll &ret = dp[i];
        auto [h ,c , b] = a[i];
        ret = pre.query(c-1 , h-1);
        ret = max(ret , suf.fnd(c+1 , h-1));
        ret+=b;
        pre.upd(c , ret , h);
        suf.upd(c , ret , h);
 
    }
    cout << *max_element(all(dp)) << nd;
 
 
 
 
 
}
 
 
 
 
signed main() {
    ios_base::sync_with_stdio(0);cin.tie(0); cout.tie(0);
    int tt = 1, tc = 0;cin >> tt;
    while (tt--) main_(++tc);
    return 0;
}
// look at my code
// my code is amazing
 
