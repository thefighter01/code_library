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
const  double PI = acos(-1.0);  double EPS = 1e-9; const int M = 5000 + 5; ll INF = 1e15+5;  const ll B1 = 200117 , B2 = 200201; const ll N = 2e5+10, LOG = 20 , inf = 1e9, SQ= 200 , mod=1e9+7, mod2 = 998244353 , P1 = 31 , P2 = 29;
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
    return (a + b + m ) % m;
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
ll sum(ll n){
    return n * (n+1) / 2;
}
ll ss(ll n){
    return n * (n+1) * (2 * n+1) / 6;
}
ll solve(ll n){
    return (n+1) * sum(n)  - ss(n) ;
}



struct matrix{
    vector <vector<ll > > a , nu;

    matrix(){
        a = nu= vector < vector <ll > > (3 ,  vector <ll > (3));
        for (int i = 0; i < 3; ++i) nu[i][i] = 1;
    }

    vector < vector <ll > >  mu(vector < vector <ll > > & m1 , vector < vector<ll > > & m2){
        vector < vector <ll > > ans = vector < vector <ll > > (3 , vector <ll > (3));
        for (int i = 0; i < 3; ++i){
            for (int j = 0; j < 3; ++j){
                for (int k = 0; k < 3; ++k){
                    ans[i][k] = add(ans[i][k] , mul(m1[i][j] , m2[j][k] , mod), mod);
                }
            }
        }
        return ans;
    }

    vector < vector <ll >>  solve(vector <vector <ll > > b , ll p){
        if (!p) return nu;
        vector < vector<ll > > ret = solve(b , p >> 1);
        ret = mu(ret , ret);
        if (p & 1) ret = mu(ret , b);
        return ret;
    }
};


void main_(int tc){
    ll n , k; cin >> k >> n;
    /*
     * a , b , c
     * k , k , k
     * int new_a = a * 0 + b * 1 + c * 0
     * int new_b = a * 0 + b * 0 + c * 1
     * int new_c = a * 1 + b * 0 + c * 1
     */
    if (n < 4){
        cout << k << nd;
        return;
    }
    matrix dp;
    vector < vector <ll > > state = {
            {0 , 1 , 0} ,
            {0 , 0 , 1} ,
            {1, 0 , 1}
    };
    vector < vector <ll > > cur_state = dp.solve(state , n-3);
    ll ans = 0;
    for (int i = 0; i < 3; ++i) ans = add(ans , cur_state[2][i] , mod);
    cout << ans << nd;







}


signed main() {
    ios_base::sync_with_stdio(0);cin.tie(0); cout.tie(0);
    int tt = 1, tc = 0;//cin >> tt;
    while (tt--) main_(++tc);
    return 0;
}
// look at my code
// my code is amazing

