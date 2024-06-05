#include<iostream>
#include <bits/stdc++.h>
#include <ext/numeric>
using namespace std;
//using L = __int128;
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
#define print2(x , y) cout <<x<<' '<<y<<nd;
#define print3(x , y , z) cout <<x<<' '<<y<<' '<<z<<nd;
#define watch(x) cout << (#x) << " = " << x << nd;
template<class container>
void print(container v) { for (auto& it : v) cout << it << ' ' ;cout <<endl;}
//template <class Type1 , class Type2>
ll fp(ll a , ll p){ if(!p) return 1; ll v = fp(a , p/2); v*=v;return p & 1 ? v*a : v;  }
ll inf = 1e9+5 , mod= 1e9+7;//998244353;//1e9+7
template <typename T> using ordered_set =  tree<T, null_type,less<T>, rb_tree_tag,tree_order_statistics_node_update>;
const int N = 8e6+500,LOG = 22;

ll mul (ll a, ll b){
    return ( ( a % mod ) * ( b % mod ) ) % mod;
}
ll add (ll a , ll b){
    return (a + b + mod) % mod;
}

template< typename  T > using min_heap = priority_queue <T , vector <T >  , greater < T > > ;
// m n

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()) ;
long long gen(long long l , long long r)
{
    return uniform_int_distribution<long long>(l , r)(rng) ;
}
struct node{
    ll data ;
    node *l , *r;
};
node buf[N];
int index;
node * extend(node *l , node *r ,ll v){
    buf[index].l = l;
    buf[index].r = r;
    buf[index].data = v;
    assert(index+1 < N);
    return &buf[index++];
}
node *leaf(ll c){
    return extend(nullptr , nullptr , c);
}
node * merge (node *l , node *r){
    return extend(l , r , l->data ^ r->data);
}
node * build(int node_low , int node_high){
    if (node_high- node_low == 1)
        return leaf(0);
    int mid = node_low + node_high >> 1;
    node * left = build(node_low , mid);
    node * right = build(mid , node_high);
    return merge(left , right);
}
node * upd (node * tree , int i , ll data ,int node_low , int node_high){
   /// cout <<"a7a" <<endl;
    if (node_high - node_low == 1)
        return leaf(data ^ tree->data);
    int mid = node_low + node_high >> 1;
    node * left = tree->l ; node * right = tree->r;
    if (i < mid)left =  upd(left , i , data , node_low , mid);
    else right = upd(right , i , data ,mid ,node_high);
    return merge(left , right);
}

ll calc (node * tree , ll node_low , ll node_high , ll query_low , ll query_high){
    if (node_low >= query_high || query_low>= node_high) return 0;
    if (node_low >= query_low && query_high >= node_high)
        return tree->data;
    int mid = node_low  + node_high >> 1;
    ll op1 = calc(tree->l , node_low , mid , query_low , query_high);
    ll op2= calc(tree->r , mid , node_high , query_low , query_high);
    return  op1 ^ op2;
}
void print (node * tree , int node_low , int node_high) {
    cout << node_low << " " << node_high << " uuu   " << tree->data << nd;
    if (node_high - node_low == 1)
        return;
    int mid = node_low + node_high >> 1;
    print(tree->l, node_low, mid);
    print(tree->r, mid, node_high);
}
ll n , q;
const int M = 3e5+100;
vector<int > depth(M);
vector < vector <int > > ad(M);
vector < vector <int > > anc;
vector <ll > h , a ;
vector<node * > versions;
void dfs(int nn , int par , node* tree){
    anc[nn][0] = par; depth[nn] = 1 + depth[par];
    for (int i = 1; i < LOG; ++i) anc[nn][i] = anc[anc[nn][i-1]][i-1];
    assert(a[nn] < (int)h.size());
   tree = upd(tree , a[nn] ,h[a[nn]], 0 , n);
    versions[nn] = tree;
    for (auto &ch : ad[nn]) {
        if (par != ch) dfs(ch, nn, tree);
    }
}
int kth (int node , int k){
    for (int i = LOG-1; ~i ; --i)
        if (k & (1 << i)) node =anc[node][i];
    return node;
}
ll lca (int u , int v){
    if (depth[u] < depth[v]) swap(u , v);
    u = kth(u , depth[u]- depth[v]);
    if (u == v) return u;
    for (int i = LOG-1; ~i; -- i)
        if (anc[u][i] != anc[v][i]) u = anc[u][i] , v= anc[v][i];

    assert(anc[u][0] == anc[v][0] && u ^ v);
    return anc[u][0];
}

ll ask (node * u , node *v  , node * lc , node * father , ll node_low , ll node_high , ll query_low , ll query_high){
    ll tt = u-> data ^ v->data ^ lc->data ^ father->data;
    if (!tt) return -1;
    if (node_low >= query_high || query_low>= node_high) return -1;
    if (node_high - node_low == 1)
        return node_low;
    int mid = node_low + node_high >> 1;
    ll ac = ask(u->l, v->l, lc->l, father->l, node_low, mid, query_low, query_high);
    if (ac != -1) return ac;

    return ask(u->r , v->r , lc->r , father->r , mid , node_high , query_low , query_high);
}

void hat_wrong_answer_test2(int tc){
    cin >> n >> q;
    int l , r , u , v;
    a = vector <ll>(n+5);
    h= vector<ll>(n+30);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i < n; ++i) {
        cin >> u >> v;
        ad[u].emplace_back(v);
        ad[v].emplace_back(u);
    }

    for (int i = 0; i <= n+20; ++i) h[i] = rng() % (1ll << 62);

    anc = vector < vector <int > > (n+10 , vector <int > (LOG+1));
    versions = vector < node* > (n+5);
    n+=3;
    versions[0] = build(0 , n);
   dfs(1 , 0 , versions.front());

    while (q--){
        cin >> u >> v >> l >> r; // add one
        ll lc = lca(u , v);
        ll ans = ask(versions[u] , versions[v] , versions[lc] , versions[anc[lc][0]] , 0 , n , l , r+1);
        cout << ans <<nd;
    }

}


int main(){
   // mobi();
     ios_base::sync_with_stdio(0); cin.tie(0);cout.tie(0); //init();

    //the_best_is_still_yet_to_come();
    //freopen("red2.in ","r",stdin);//  freopen("output.txt","w",stdout);
    int tt = 1 , tc = 0;
 //   cin>>tt;
    while(tt--) hat_wrong_answer_test2(++tc);
#ifndef ONLINE_JUDGE
    cout << "Running Time: " << 1.0 * clock() / CLOCKS_PER_SEC << " s .\n";
#endif
    return 0;
}
/*
x3 - w3 >= x2 + w2
x3 - w3 >= x1 + w1
x2 - w2 >= x1 + w1
*/
 
