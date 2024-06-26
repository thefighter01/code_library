//#pragma GCC optimize ("O3")
//#pragma GCC optimize ("unroll-loops") // remember usage
#include<iostream>
#include <bits/stdc++.h>
#include <ext/numeric>
using namespace std;
using LL = __int128;
#include<ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define nd "\n"
#define all(x) (x).begin(), (x).end()
#define lol cout <<"i am here"<<nd;
#define py cout <<"YES"<<nd;
#define pp  cout <<"ppppppppppppppppp"<<nd;
#define pn cout <<"NO"<<nd;
#define popcount(x)  __builtin_popcount(x)
#define clz(n) __builtin_clz(n)//31 -x
const  double PI = acos(-1.0);
double EPS = 1e-9;
const ll N = 3e5+10, LOG = 20 , inf = 1e16, SQ= 200 , mod=1e9+7, mod2 = 998244353 , P1 = 31 , P2 = 29;
template<class container> void print(container v) { for (auto& it : v) cout << it << ' ' ;cout <<endl;}
//template <class Type1 , class Type2>
ll fp(ll a , ll p){ if(!p) return 1; ll v = fp(a , p/2); v*=v;return p & 1 ? v*a : v;  }
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rand(ll l , ll r) { return uniform_int_distribution<ll>(l, r)(rng); }
template <typename T> using ordered_set =  tree<T, null_type,less<T>, rb_tree_tag,tree_order_statistics_node_update>;
template< typename  T > using min_heap = priority_queue <T , vector <T >  , greater < T > >;
const ll B1 = 200117 , B2 = 200201;
//# define int long long // hay brother


ll mul (ll a, ll b , ll m){
    return ((a % m) *  (b % m)) % m;
}
ll add (ll a , ll b , ll m){
    return (a + b + m ) % m;
} // x ^ phi(m) is congruent to 1 mod m
// x ^ (phi -1) is congruent to  x^ -1 mod m
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


// E gym  , div1E tor , problem j //  div1 E , div1 D
int dx[] {0 , 0 , -1 , 1 ,-1 , 1 , 1 , -1};
int dy[] {-1 , 1 , 0 , 0 , -1 , 1 , -1 , 1};


const int M = 1e6+30;
ll INF = 1e8;
int t[M][26], cnt [M] , ed[M];
ll sum[M];

int nodes;
void init(){
    for (int i = 0 ;i <= nodes ; ++i) {
        cnt[i] = sum[i] = ed[i] = 0;
        for (int j = 0 ; j < 26 ; ++j) t[i][j] = 0;
    }
    nodes = 0;
}
int extend(){
    assert(++nodes < M);
    return nodes;
}
void push(string & s){
    int sz = (int) s.size();
    int node = 0;
    for (int i = 0 ; i < sz; ++i){
        int ch = s[i] - 'a';
        if (!t[node][ch]) t[node][ch] = extend();
        node = t[node][ch];
        sum[node] += sz-i;
        cnt[node]++;
    }
    ed[node]++;
}
ll solve(string & s){
    int sz = (int) s.size(); int node = 0;
    ll ans = 0;
    for (int i = 0 ; i < sz; ++i){
        int ch = s[i]-'a';
        for (int j = 0 ; j < 26 ; ++j){
            if (ch ^ j && t[node][j]){
                ans += (sz - i) * 1ll * cnt[t[node][j]] + sum[t[node][j]];
            }
        }

        node = t[node][ch];
        if (!node) return ans;
        ans += ed[node] * 1ll * (sz -i -1);
    }
    for (int j = 0 ; j < 26 ; ++j) if (t[node][j]) ans += sum[t[node][j]];
    return ans;
}

void main_(int tc) {
    int n; cin >> n; init();
    vector < string > a(n);
    for (auto &i : a) cin >> i , push(i);
    ll ans = 0;
    for (auto &i : a){
        reverse(all(i));
        ans+= solve(i);
    }
    cout << ans << nd;



}

signed main() {
    ios_base::sync_with_stdio(0);cin.tie(0); cout.tie(0);
    //freopen("trains.in", "r", stdin);
    //freopen("output.txt", "w", stdout);
    int tt = 1, tc = 0 ;//cin >> tt;
    while (tt--) main_(++tc);
#ifndef ONLINE_JUDGE
    cout << "Running Time: " << 1.0 * clock() / CLOCKS_PER_SEC << " s .\n";
#endif
    return 0;
}
