unordered_map<int,int> dp1,dp2 ;
vector<vector<ll>> c ;
void dfs(ll node,ll par){
    ll fm=0,sm=0 ;
 
    for(int it : c[node]){
       if(it==par) continue ;
       dfs(it,node) ;
       if(dp1[it]+1>fm){
          sm=fm;
          fm=dp1[it]+1;
       }else if(dp1[it]+1>sm){
          sm=dp1[it]+1;
       }
    }
 
    dp1[node]=fm ;
    dp2[node]=fm+sm ;
    mx=max<ll>(mx,dp2[node]) ;
}
void solve() {
    ll n;cin>>n;
    c.resize(n) ;
    for(int i=0;i<n-1;i++) {
       ll u,v;cin>>u>>v;
       u--,v--;
     //   if(u>v) swap(u,v) ;
       c[u].pb(v) ;
       c[v].pb(u) ;
    }
    dfs(0,-1) ;
    cout<<mx<<endl ;
}
