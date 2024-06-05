const int M = 6e6+30;
ll INF = 1e8;
 
int nodes ;
int t[M][2], sz[M];
void init(){
    for (int i = 0 ; i <= nodes; ++i){
        sz[i] =0;
        memset (t[i] , 0 , sizeof t[i]);
    }
    nodes = 0;
}
 
int extend(){
    assert(++ nodes < M);
    return nodes;
}
 
void push(int v){
    int node = 0;
    for (int b = 29; b >= 0 ; --b){
        int on = (v >> b) & 1;
        if (!t[node][on]) t[node][on] = extend();
        node = t[node][on];
        sz[node]++;
    }
}
 
ll query(int v){
    ll ans ,ones , node; ans = node = ones = 0;
    for (int b = 29 ; b >= 0 ; --b){
        int on = (v >> b) & 1;
        if (on){ // i am greater
            ++ones;
            if (t[node][0]) ans = add(ans, mul(ones, sz[t[node][0]], mod2), mod2);
        }
        else{ // i am smaller + 1
            if (t[node][1]) ans = add(ans , mul(ones+2 , sz[t[node][1]] , mod2) , mod2);
        }
        node = t[node][on];
    }
    ans = add(ans , mul(ones+1 , sz[node] , mod2) , mod2);
    return ans;
}
