// BFS traversal of graph
// http://www.practice.geeksforgeeks.org/problem-page.php?pid=700217

/* You have to complete this function
which prints out the breadth first level traversal of the 
graph starting from node s
the vector<int> g[i] represent the adjacency 
list of the ith node of the graph
 */
#include<queue>
void bfs(int s, vector<int> g[], bool vis[])
{

    if(g[s].size() == 0){
        cout << s;
    }
    else{
        queue<int> q;
        q.push(s);
        vis[s] = true;
        while(q.size() > 0){
            int curr = q.front(); q.pop();
            cout << curr << " ";
            vector<int>::iterator it = g[curr].begin();
            for(;it!=g[curr].end(); it++){
                
                if(!vis[*it]){
                    q.push(*it);                    
                    vis[*it] = true;
                }
            }
        }
    }
    
}