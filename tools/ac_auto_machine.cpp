// It`s not executable. Just 4 saving code. It`s not written by me.

int num_node, trie[N][M], val[N], num[N];
const int M = 26;
int idx(char c){
    return c - 'a';
}
void init_trie(){
    memset(trie[0], 0, sizeof(trie[0]));
    num_node = 1;
}
void insert_trie(char *s, int lens){
    int now = 0, c;
    for(int i = 0; i < lens; i++){
        c = idx(s[i]);
        if(trie[now][c] == 0){
            now = trie[now][c] = num_node;
            memset(trie[now], 0, sizeof(trie[now]));
            num_node += 1;
        }
        else now = trie[now][c];
    }
    val[now] += 1;
}

int fail[N], last[N];
queue<int>q;
void build(){
    while(!q.empty()) q.pop();
    fail[0] = last[0] = 0;
    int now;
    for(int i = 0; i < M; i++){
        int now = trie[0][i];
        if(now){
            fail[now] = last[now] = 0;
            q.push(now);
        }
    }
    while(!q.empty()){
        now = q.front();
        q.pop();
        for(int i = 0; i < M; i++){
            int f = fail[now];
            if(trie[now][i] == 0)
                continue;
            while(f && trie[f][i] == 0)
                f = fail[f];
            int son = trie[now][i];
            fail[son] = trie[f][i];
            last[son] = val[fail[son]]? fail[son] : last[fail[son]];
            q.push(son);
        }
    }
}
void mark(int now){
    //...write what you need
}
void dfs(char *s){
    int lens = (int)strlen(s), now=0, c;
    for(int i = 0; i < lens; i++){
        c = idx(s[i]);
        while(now && trie[now][c] == 0)  now = fail[now];
        now = trie[now][c];
        if(val[now]) mark(now);
        else if(last[now]) mark(last[now]);
    }
}
