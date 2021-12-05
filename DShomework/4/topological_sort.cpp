#include<iostream>
#include<vector>
#include<queue>
#include<map>
#include<string>
using namespace std;

struct node{
    int u, level;
    node(int v=0, int n=0): u(v), level(n){}
};                  //level 是层次
const int N = 105;  //最多就学100门课
int st[N];          //标记
vector<int> edge[N];//邻接表
int ind[N];         //入度表
int n;              //n个结点
int m;              //m个关系
queue<node> q;       //队列
vector<node> ans;   //ans 为拓扑序列
map<string, int> ma; //将节点内容和序号做一个映射
map<int, string> ma2; //反向映射

//输出所有拓扑排序
int vis[N];
int o[N];
int num=0;
void dfs(int len, int level){
    if(len==n){
        for(int i=0; i<n; i++){
            cout<<ma2[o[i]]<<" ";
        }
        cout<<num++<<endl;
    }
    for(int j=0; j<n; j++){
        if(ans[j].level==level){
            if(vis[ans[j].u]==0){
                o[len]=ans[j].u;
                vis[ans[j].u]=1;
                dfs(len+1, level);
                vis[ans[j].u]=0;
            }
        }
        else if(ans[j].level>level){
            dfs(len,level+1);
            break;
        }
    }
}

int main() {
    //读入，建图
    cout<<"请输入各个节点"<<endl;
    //进行映射
    n=0;
    string s, ss;
    cin>>s;
    for(auto& c:s){
        if(c==','){
            ma[ss]=n;
            ma2[n]=ss;
            n++;
            ss.clear();
        }
        else{
            ss.push_back(c);
        }
    }
    ma[ss]=n;
    ma2[n]=ss;
    n++;
    ss.clear();
    //读入边
    cout<<"请输入边的数量"<<endl;
    cin>>m;
    for (int i = 1; i <= m; i++) {
        cin>>s;
        string s1;
        for(auto& c:s){
            if(c==','){
                s1=ss;
                ss.clear();
            }
            else{
                ss.push_back(c);
            }
        }
        edge[ma[s1]].push_back(ma[ss]);
        ind[ma[ss]]++;
        ss.clear();
    }
    for (int i = 0; i < n; i++) if (ind[i] == 0) q.push(node(i,0));  //将入度为0的点入队列

    while (!q.empty()) {
        node p = q.front();
        q.pop(); // 选一个入度为0的点，出队列
        ans.push_back(p);
        for (int i = 0; i < edge[p.u].size(); i++) {
            int y = edge[p.u][i];
            ind[y]--;
            if (ind[y] == 0) q.push(node(y,p.level+1));
        }
    }
    if (ans.size() == n) {
        cout<<"此有向图存在拓扑排序"<<"\n"<<"所有拓扑排序结果为:"<<endl;
        dfs(0,0);
        printf("\n");
    } else printf("图中存在环\n");   //  ans 中的长度与n不相等，就说明无拓扑序列

    return 0;
}