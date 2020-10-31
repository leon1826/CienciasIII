#include <vector>
#include<iostream>
#include<map>
#define endl '\n'
#define size( x )   int( ( x ).size( ) )
#define endl '\n'

using namespace std;

/*
 * @author
 * Daniel Santos
 * the example data was taken from this video
 * https://www.youtube.com/watch?v=4oDLMs11Exs
 *
 * the columns are as follows
 * 
 * 1st column (n): the number of edges in the graph
 * then n rows with the edges in the graph
 * Activity, Predecesor, Duration(days)
 *
 * to use the example: the name of the nodes should be a single letters from [A-Z]
 *
 *        t1   t2
 *           A
 *        t4   t3
 */


struct node{
  char name;
  vector<node*> childs;
  int duration;
  int t1, t2 , t3, t4;
  node(){};
  node( char _name, int _d): name(_name), duration(_d){
    t1 = t2  = t4;
    t3 = 1e5; 
  }
};


vector< node* >  graph[100];
vector<char> critic_path;
map<int, int> vis;
node*  desc[100];

int dfs( int src, int acum){
  for( node* son: graph[src]){
    int id = son->name - 'A';
    if( id != src){
      desc[id]->t1 = max(acum, desc[id]->t1);
      desc[id]->t2 = max(desc[id]->t2, acum+desc[id]->duration);
      desc[src]->t3 = min( desc[src]->t3, dfs(id,desc[id]->t2 ));
    }
  }
  if( size(graph[src])  == 0) desc[src]->t3 =  desc[src]->t2;
  desc[src]->t4 = desc[src]->t3 - desc[src]->duration;
  return desc[src]->t4;
}

void dfs2( int src){
  if( desc[src]->t2 == desc[src]->t3){
    critic_path.push_back(desc[src]->name);
  }
  for( node* son: graph[src]){
    int id = son->name - 'A';
    if( id != src && vis[id]==0){
       vis[id] = 1;
       dfs2(id);
    }
  }
}


int main(){

  int n;
  cin >>n ;
  char from, to;
  int duration;
  cout << "times\n";
  while(n--){
    cin >> to >> from >> duration;
    int id1 = from - 'A';
    int id2 = to - 'A';
    if( from == '-') id1 = 0;
    node *aux = new node(to, duration);
    graph[id1].push_back(aux);
    desc[id2] = aux;
  }

  // compute the times t1, t2, t3, t4

  // we know that the root is 'A', then
  int root = 'A' - 'A';
  desc[root]->t2 = desc[root]->duration;
  dfs(root, desc[root]->duration);

  cout << "Node t1 t2 t3 t4 holgura(t4-t1)"<<endl;

  for( int i = 0; i< 100; i++){
    if( desc[i]){
      int holgura = desc[i]->t4 - desc[i]->t1;
      cout << desc[i]->name << " " << desc[i]->t1 <<  " " << desc[i]->t2 << " " ;
      cout << desc[i]->t3 << " " << desc[i]->t4 << " " <<holgura<<endl;
    }
  }

  // now find the critical path
  dfs2(root);

  cout <<"Critic path\nbegin->";
  for(char c: critic_path){
    cout << c << "->";
  }
  cout<<"end";
  cout <<endl;

  return 0;
}
