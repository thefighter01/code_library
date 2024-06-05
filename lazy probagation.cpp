const int M = 1e6 * 10;
ll INF = 1e8;
int q ,dfn;
vector < ll > value_of;
vector < vector < int > > g;
vector  <int > st , sz , par;
void dfs (int node){
    st[node] = ++dfn; sz[node ] = 1;
    for (auto &ch : g[node]){
        par[ch] = node;
        dfs(ch);
        sz[node]+= sz[ch];
    }
}
int en (int u){
    return st[u] + sz[u] -1;
}

void init(){
    value_of = vector <ll > (N);
    par = sz = st = vector < int > (N);
    g = vector < vector < int > > (N);
}

struct sss{
    int n;
    vector < ll > lazy , t;
    void init(int _n){
        n = _n + 5;
        while (popcount(n) != 1) ++ n;
        lazy = vector < ll > (2 * n , 1);
        t = vector < ll > (2 * n);
    }
    void drop(int node , int nl , int nr){
        t[node] = mul(t[node] , lazy[node] , mod);
        if (nr - nl -1){
            lazy[2 * node + 1] = mul(lazy[2 * node + 1] , lazy[node] , mod);
            lazy[2 * node + 2] = mul(lazy[2 * node + 2] , lazy[node] , mod);
        }
        lazy[node] = 1;
    }
    void m (int node , int nl , int nr , int ql , int qr, ll v){
        drop(node , nl , nr);
        if (nl >= qr || ql >= nr) return;
        if (nl >= ql && qr >= nr){
            lazy[node] = mul(lazy[node] , v , mod);
            return drop (node , nl ,nr);
        }
        int md = (nl + nr) >> 1;
        m (2 * node + 1 , nl , md , ql ,qr , v);
        m (2 * node + 2 , md , nr ,ql , qr, v);
        t[node] = add (t[2 * node + 1] , t[ 2 * node + 2] , mod);
    }
    void m (int L , int R , ll v){
        return m (0 , 0 , n , L ,  R + 1 , v);
    }
    void upd (int node , int nl , int nr, int idx, ll v){ // take of lazy propagation
        drop(node , nl , nr);
        if (nl + 1 == nr) {
            t[node] = v;
            return ;
        }
        int md = (nl + nr ) >> 1;
        drop(2 * node + 1 , nl , md);  // drop my children to take the correct values while i am jumping up to the parents in the backtracking part
        drop(2 * node + 2 , md , nr);
        if (idx < md) upd (2 * node + 1 , nl , md , idx, v);
        else upd (2 * node + 2 , md , nr , idx, v);
        t[node] = add  (t[2 * node + 1], t[2 * node + 2] , mod);

    }
    void upd (int idx , ll v){
        return upd (0 , 0 , n , idx, v);
    }
    ll query(int node , int nl , int nr , int ql , int qr){
        drop(node , nl , nr);
        if (nl >= qr || ql >= nr) return 0;
        if (nl >= ql && qr >= nr) return t[node];
        int md = (nl + nr ) >> 1;
        ll ans = query(2 * node + 1 , nl , md , ql ,qr);
        ans = add(ans , query(2 * node + 2 , md , nr , ql , qr) , mod);
        return ans;
    }
    ll query(int L , int R ){
        return query (0 , 0 , n , L , R +  1);
    }

};
int nodes = 1;
void main_(int tc) { init();
    cin >> value_of[1] >> q;
    vector < array <int , 3 > > queries(q+5);
    for (int i = 1; i <= q; ++i){
        cin>> queries[i][0] >> queries[i][1];
        if (queries[i][0] == 1){
            cin >> queries[i][2];
            int nu = ++nodes;
            g[queries[i][1]].push_back(nu);
            value_of[nu] = queries[i][2];
            queries[i][2] = nu;
        }
    }
    dfs(1);
    sss t; t.init(nodes);
    t.upd(st[1] , value_of[1]);
    vector < int > children(nodes + 5 , 1);
    for (int i = 1 ; i <= q ;i ++){
        if (queries[i][0] == 1){
            int u = queries[i][1];
            ll con = mul((children[u]+1) , modInv(children[u] ,mod) , mod); children[u]++;
            int ch = queries[i][2];
            ll m = t.query(st[u] , st[u]); m = mul(m , modInv(value_of[u] , mod) , mod);
            t.upd(st[ch] , mul(value_of[ch] , m , mod));
            t.m(st[u] , en(u) , con);
        }
        else {
            int u = queries[i][1];
            ll ans = t.query(st[u] , en(u));
            u = par[u];
            if (u) {
                ll cur = modInv(value_of[u] , mod);
                cur = mul (cur , t.query(st[u] , st[u]) , mod);
                ans = mul(ans , modInv(cur , mod) , mod);
            }
            cout << ans << nd;
        }
    }



}
