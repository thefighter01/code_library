
ll INF = 2e18;

int n, m, q, dfn;
vector < vector < int > > g ;
vector < vector < array <ll , 2 > > > nodes;
array < ll , 3 > nu =  {INF , INF, INF};
vector < int > st , sz  , heavy , root , par , dep ,inv;
int en (int u){
    return st[u] + sz[u] - 1;
}
void init(){
    g = vector < vector < int > > (n+5);
    inv = dep = st = sz = par = root = heavy = vector < int > (n+5);
    nodes = vector < vector < array< ll , 2 > > > (n+5);
}
struct sss{
    int n;
    vector < array < ll , 3 > > t;
    vector < ll > lazy;
    void init(int _n){
        n = _n + 5;
        while (popcount(n) != 1 ) ++n;
        t = vector < array < ll , 3 > > (2 * n , nu);
        lazy = vector < ll > (2* n);
    }

    array < ll , 3 > merge (array < ll , 3 > & u , array < ll , 3 > & v){
        return min (u , v);
    }
    void drop (int node , int nl , int nr){
        t[node][0]+=lazy[node];
        if (nr - nl -1){
            lazy[2 * node +1]+= lazy[node];
            lazy[2 * node +2]+= lazy[node];
        }
        lazy[node] = 0;
    }

    void upd (int node , int nl , int nr , int idx , array <ll , 2 > d){
        drop (node , nl , nr);
        if (nl+ 1 == nr){
            t[node] = {d[0], d[1] , nl};
            return;
        }
        int md = (nl + nr) >> 1;
        drop(2 * node + 1 , nl , md);
        drop (2 * node + 2 , md , nr);
        if (idx < md) upd (2* node + 1 , nl , md ,idx, d);
        else upd(2* node + 2 , md , nr , idx , d);
        t[node] = merge(t[2* node + 1 ] , t[2 * node + 2]);
    }

    void add (int node , int nl , int nr , int ql , int qr , ll k){
        drop (node , nl , nr);
        if (nl >= qr || ql >= nr) return;
        if (nl >= ql && qr >= nr){
            lazy[node]+= k;
            return drop (node , nl , nr);
        }
        int md = (nl + nr) >> 1;
        add(2 * node + 1 , nl , md , ql ,qr , k);
        add(2* node + 2 , md , nr ,ql ,qr ,k);
        t[node] = merge(t[2 * node+1] , t[2 * node + 2]);
    }
    // can u delete function del
    void del (int node , int nl , int nr , int idx){
        drop (node , nl , nr);
        if (nl + 1 == nr){
            assert (!nodes[nl].empty());
            array < ll , 2> temp = nodes[nl].back();
            nodes[nl].pop_back();
            ll must = t[node][0] - temp[0];
            if (nodes[nl].empty()) t[node] = nu;
            else t[node] = {nodes[nl].back()[0]+ must , nodes[nl].back()[1], nl};
            return;
        }
        int md = (nl + nr) >> 1;
        drop(2 * node + 1 , nl , md);
        drop (2 * node + 2 , md , nr);
        if (idx < md) del(2* node + 1 , nl , md , idx);
        else del(2* node + 2 , md , nr , idx);
        t[node] = merge(t[2 * node + 1] , t[ 2 * node + 2]);
    }
    void upd (int idx , array<ll , 2 > d){
        upd (0, 0 , n , idx , d);
    }
    void del (int idx){
        del (0,0 , n , idx);
    }
    void add (int L , int R , int v){
        add (0, 0 , n , L , R+1, v);
    }
    array < ll , 3 >  query (int node , int nl , int nr , int ql , int qr){
        drop (node, nl , nr);
        if (nl >= qr || ql >= nr) return nu;
        if (nl >= ql && qr >= nr) return t[node];
        int md = (nl + nr) >> 1;
        array <ll , 3 >  L = query(2 * node + 1 , nl , md , ql , qr);
        array < ll , 3 >  R = query(2 * node + 2 , md , nr ,ql ,qr);
        return merge (L , R);
    }
    array < ll , 3 > query (int L , int R){
        assert (L <= R);
        return query (0 , 0 , n , L , R + 1);
    }
};
sss t ;
void dfs_sz(int node , int p){
    par[node] = p; sz[node] = 1; root[node] = node;
    for (auto &ch : g[node]){
        if (ch == p) continue;
        dep[ch] = 1 + dep[node];
        dfs_sz(ch , node);
        sz[node] += sz[ch];
        if (sz[ch] > sz[heavy[node]]) heavy[node] = ch;
    }
}

void hld (int node){
    inv [st[node] = ++ dfn ] = node ;
    if (heavy[node]) { root[heavy[node]] = root[node]; hld(heavy[node]);}
    for (auto &ch : g[node]){
        if (ch ^ par[node] && ch ^ heavy[node]) hld(ch);
    }
}

array < ll , 3 > solve (int u , int v){
    array < ll , 3 >  ans = nu;
    while (root[u] != root[v]){
        if (dep[root[u]] < dep[root[v]]) swap(u, v);
        ans = min (ans , t.query (st[root[u]], st[u]));
        u = par[root[u]];
    }
    if (st[u] < st[v]) swap(u, v);
    ans = min (ans, t.query(st[v] , st[u]));
    return ans;
}
void main_(int tc) {
    cin >> n >> m >> q; init();
    for (int i = 1; i < n; ++i){
        int u, v ; cin >> u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs_sz(1, 0); hld(1);   t.init(n+5);
    for (int i = 1; i <= m ; ++i){
        int u; cin >> u;
        nodes[st[u]].push_back({i, u});
    }
    for (int cur = 1 ; cur <= n; ++ cur) {
        if (!nodes[cur].empty()) {
            reverse(all(nodes[cur]));
            t.upd(cur, nodes[cur].back());
        }
    }

    for (int _ = 1; _ <= q; ++_){
        int op , u, v, k;
        cin >> op;
        if (op == 1){
            cin >> u >> v >> k;
            vector < int > ans;
            while (k--){
                array < ll , 3 > opt = solve (u, v);
                if (opt[0] >= INF) break;
                ans.push_back(nodes[opt[2]].back()[0]);
                t.del(opt[2]);
            }
            int sz_ans = (int ) ans.size ();
            cout << sz_ans;
            for (int i = 0 ;i < sz_ans ; ++i) cout << " " << ans[i];
            cout << nd;
        }
        else {
            cin >> u >> k;
            t.add(st[u] , en(u) , k);
        }
    }




}

