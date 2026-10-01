#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<limits.h>
struct node{
    int vertex;
    int weight;
    struct node *next;
};
void addedge(struct node *adj[],int u,int v,int w){
    struct node* newnode=malloc(sizeof(struct node));
    newnode->vertex=v;
    newnode->weight=w;
    newnode->next=adj[u];
    adj[u]=newnode;
}
void printGraph(struct node* adj[], int V)
{
    for (int i = 0; i < V; i++)
    {
        printf("%d: ", i);

        struct node* temp = adj[i];

        while (temp != NULL)
        {
            printf("%d %d-> ", temp->vertex,temp->weight);
            temp = temp->next;

        }

        printf("NULL\n");
    }
}
void bfs(struct node* adj[],int v,int st){
    int vis[v];
    for (int i = 0; i < v; i++)
    {
        vis[i]=0;
    }
    int front=0,rear=0;
    int queue[v];
    queue[rear++]=st;
    vis[st]=1;
    printf("BFS== ");
    
    while(front<rear){
        int u=queue[front++];
        printf("%d ",u);
        struct node*temp=adj[u];
        while(temp!=NULL){
            int z=temp->vertex;
            if(!vis[z]){
                queue[rear++]=z;
                vis[z]=1;
            }
            temp=temp->next;
        }
    }
}
int mindist(int dist[],int vis[],int v){
    int minvertex=-1;
    int min=INT_MAX;
    for (int i = 0; i < v; i++)
    {
        if (!vis[i]&&dist[i]<min)
        {
            min=dist[i];
            minvertex=i;
        }    
    }
    return minvertex;   
}
void dfs(struct node* adj[],int vis[],int v,int st){
    vis[st]=1;
    printf("%d ",st);
    struct node*temp=adj[st];
    while(temp!=NULL){
        int z=temp->vertex;
        if(!vis[z]){
            vis[z]=1;
            dfs(adj,vis,v,z);
        }
        temp=temp->next;
    }
}
void dijkstra(struct node* adj[],int v,int st){
    int dist[v];
    int vis[v];
    for (int i = 0; i < v; i++)
    {
        vis[i]=0;
        dist[i]=INT_MAX;
    }
    dist[st]=0;
    for (int count = 0; count < v;count++)
    {
        int u=mindist(dist,vis,v);
        if(u==-1)break;
        vis[u]=1;
        struct node* temp=adj[u];
        while(temp!=NULL){
            int v=temp->vertex;
            int wei=temp->weight;
            if (!vis[v]&&dist[u]!=INT_MAX&&dist[u]+wei<dist[v])
            {
               dist[v]=dist[u]+wei;
            }
            temp=temp->next;
        }
    }
    printf("shortest distance from %d to vertices:-> ",st);
    for (int i = 0; i < v; i++)
    {
         if (dist[i] == INT_MAX)
            printf("%d -> INF\n", i);
        else
            printf("%d -> %d\n", i, dist[i]);
    }  
}
void bellmanford(struct node* adj[],int v,int st){
    int dist[v];
    for (int i = 0; i < v; i++)
    {
        dist[i]=INT_MAX;
    }
    dist[st]=0;
    for (int i = 0; i < v-1; i++)
    {
        for (int u = 0; u < v; u++)
        {
            struct node *temp=adj[u];
            while (temp!=NULL)
            {
                int vv=temp->vertex;
                int weightt=temp->weight;
                if (dist[u]!=INT_MAX&&dist[u]+weightt<dist[vv])
                {
                   dist[vv]=dist[u]+weightt; 
                }
                temp=temp->next;
            }
        }
        
    }
    for (int u = 0; u < v; u++){
            struct node *temp=adj[u];
            while (temp!=NULL)
            {
                int vv=temp->vertex;
                int weightt=temp->weight;
                if (dist[u]!=INT_MAX&&dist[u]+weightt<dist[vv])
                {
                 printf("negative weight cycle \n");
                 return;  
                }
                temp=temp->next;
            }
        }
        printf("Shortest distances:\n");
        for(int i = 0; i < v; i++){
        if(dist[i] == INT_MAX)
        printf("%d -> INT_MAX\n", i);
        else
        printf("%d -> %d\n", i, dist[i]);
    }

}

int main(){
    int v,e;
    printf("enter the no of vertices\n");
    printf("enter no of edges\n");
    scanf("%d %d",&v,&e);
    struct node* adj[v];
    for (int i = 0; i < v; i++)
    {
        adj[i] = NULL;
    }
    printf("enter the connections with weight\n");
    for(int i=0;i<e;i++){
        int uu,vv,w;
        scanf(" %d %d %d",&uu,&vv,&w);
        addedge(adj,uu,vv,w);
    }
    printGraph(adj,v);
    bfs(adj,v,0);
    printf("dfs== ");
    int vis[v];
    for (int i = 0; i < v; i++)
    {
        vis[i]=0;
    }
    
    dfs(adj,vis,v,0);
    dijkstra(adj,v,0);
    bellmanford(adj,v,0);
        return 0;
}