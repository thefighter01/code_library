

const int M = 6e5+5;

ll INF = 1e16;
// take care of multi edges using set think
vector <int > a , lo , dfn, compo, sz, in_stack , st;
vector < ll > value_of ;
vector < vector < int > > g;
int n , m , T , id;
void init (){
    in_stack = lo = dfn = compo = sz = a = vector < int > (n+5);
    g = vector < vector< int > > (n+5);
    value_of = vector<ll > (n+5);
    T = id = 0; st.clear();
}

void tarjan(int node){
    lo[node] = dfn[node] = ++T; in_stack[node] = 1; st.emplace_back(node);
    for (auto &ch : g[node]){
        if (!dfn[ch]){
            tarjan(ch);
            lo[node] = min(lo[node] , lo[ch]);
        }
        else if (in_stack[ch]) lo[node] = min(lo[node], dfn[ch]);
    }
    if (lo[node] == dfn[node]){
        int u = -1; ++id;
        while (node != u){
            u = st.back(); st.pop_back(); in_stack[u] = 0;
            sz[id]++; compo[u] = id;
            value_of[id]+=a[u];
        }

    }

}

void main_(int tc) {
    cin >> n >> m; init();
    for (int i = 1 ;i <= n; ++i) cin >> a[i];
    for (int u, v , i = 1; i <= m; ++i){
        cin >> u  >> v;
        g[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i) if (!dfn[i]) tarjan(i);
    set< array< int, 2 > > s;
    for (int node = 1; node <= n ; ++ node)
        for (auto &ch : g[node])
            if (compo[ch] ^ compo[node])
                s.insert({compo[node] , compo[ch]});
    for (int i = 1; i <= n; ++i) g[i].clear();
    vector <int > deg(id+5);
    for (auto &[u , v] : s) g[u].push_back(v), deg[v]++;
    deque <int > q;
    for (int i = 1; i<= id ; ++i) if (!deg[i]) q.emplace_back(i);
    vector <int > order;
    while (!q.empty()){
        int node = q.front(); q.pop_front();
        order.push_back(node);
        for (auto &ch : g[node])
            if (!--deg[ch])
                q.emplace_back(ch);
    }
    assert(id == (int)order.size());
    reverse(all(order));
    array< ll , 2 > longest {0 , INF};
    vector < array < ll , 2 > > dp(id+5);
    for (auto &node : order){
        auto &ret = dp[node];
        for (auto &ch : g[node]) ret = max(ret , dp[ch]);
        ret[0]+=sz[node];
        ret[1]-=value_of[node];
        longest = max(longest , ret);
    }
    cout << longest[0] << " " << -longest[1] << nd;


}

