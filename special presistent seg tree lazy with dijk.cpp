const int N = 1e5 + 50;
const int M = N << 8 ; // take of the number of nodes
ll INF = 1e8;
int pw[N] , lc[M] ,rc[M] ,val[M] , num[M], root[N] , par[N] , nodes;
int extend (){
    assert(++ nodes < M);
    return nodes;
}
vector < array < int , 2 >  > g[N];
void init(){
    pw[0] = 1;
    for (int i = 1; i < N; ++i) pw[i] = mul(pw[i-1] , 2 , mod);
}
void push(int x){
    val[x] = add(val[lc[x]] , val[rc[x]] , mod) ; num[x] = num[lc[x]] + num[rc[x]];
}

void ins(int pre , int & x, int nl , int nr , int idx){
    x = extend(); lc[x] = lc[pre] , rc[x] = rc[pre];
    if (nl + 1 == nr){
        assert(nl == idx);
        val[x] = pw[nl] , num[x] = 1;
        return;
    }
    int md = (nl + nr ) >> 1;
    if (idx < md) ins(lc[pre] , lc[x] , nl , md , idx);
    else ins (rc[pre] , rc[x] , md , nr , idx);
    push(x);
}
void modify(int pre , int & x , int nl , int nr , int ql , int qr){
    if (nl >=ql && qr >= nr){x = 0; return;}
    int md = (nl + nr) >> 1;
    x = extend(); lc[x] = lc[pre] , rc[x] = rc[pre];
    if (qr <= md) modify (lc[pre] , lc[x] , nl , md , ql ,qr);
    else if (ql >=  md) modify(rc[pre] , rc[x] , md , nr ,ql ,qr);
    else {
        modify (lc[pre] , lc[x] , nl , md , ql ,qr);
        modify(rc[pre] , rc[x] , md , nr ,ql ,qr);
    }
    push(x);
}
int query (int x , int nl , int nr , int v){
    if (num[x] == nr - nl) return -1;
    if (nl + 1 == nr) return nl;
    int md = (nl + nr) >> 1;
    if (v < md) {
        int ans = query(lc[x] , nl , md , v);
        if (~ans) return ans;
    }
    return query(rc[x] , md , nr , v);
}
bool com(int lt , int rt , int nl , int nr){
    if(val[lt] == val[rt]) return 0;
    if (nl + 1 == nr) return num[lt] < num[rt];
    int md = (nl + nr) >> 1;
    if (val[rc[lt]] == val[rc[rt]])
        return com(lc[lt] , lc[rt] , nl , md);
    return com(rc[lt] , rc[rt] , md , nr);
}

struct atom{
    int node , rt;
    bool operator < (const  atom & rhs) const{// u should really look at these stuf
        // priority queue  sorting  to make it like set return node > rhs.node; // sorting increasing order
        return com( rhs.rt , rt , 0 , N); // take care rhs.rt , rt
    }
};

void main_(int tc) {
    int n , m ; cin >> n >> m; init();
    for (int u , v , w , i =1 ;i <= m; ++i){
        cin >> u >> v >> w;
        g[u].push_back({v , w});
        g[v].push_back({u , w});
    }
    int s , e; cin >> s >> e;
    if (s == e ){cout <<0 << nd << 1 << s << nd;return;}
    priority_queue< atom > q;  // node , root
    q.push({s , 0});
    vector < int > vis(n + 5);
    while(!q.empty()){
        auto [node , t] = q.top(); q.pop();
        if (vis[node]) continue;

        vis[node] = 1;
        for (auto &[ch, w] : g[node]){
            if (ch == s) continue; // really it was an important condition
            int p = query(root[node] , 0 , N , w) , temp = root[node];
            if (p > w ) modify(root[node] , temp , 0 , N  , w, p);
            ins(temp , temp , 0 , N , p);
            if (!root[ch] || com(temp , root[ch] , 0 , N)) q.push({ch , root[ch] = temp}), par[ch] = node;
        }

    }
    if (!root[e]) {cout << -1 << nd; return ; }
    cout << val[root[e]] << nd;
    vector < int > path = {e};
    while (par[e]) path.emplace_back(par[e]) , e = par[e];
    reverse(all(path));
    cout << (int) path.size() << nd;
    print(path);




}
