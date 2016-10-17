//http://www.practice.geeksforgeeks.org/problem-page.php?pid=700203
//Depth First Traversal for a Graph

/* You have to complete this function
which prints out the depth first level traversal of the 
graph starting from node s
the vector<int> g[i] represent the adjacency 
list of the ith node of the graph
 */
void dfs(int s, vector<int> g[], bool vis[]){
    if(g[s].size() == 0 && !vis[s]){
        
        cout << s << " ";
        vis[s] = true;
    }
    else{
        cout << s << " ";
        vis[s] = true;
        vector<int>::iterator it = g[s].begin();
        for(; it != g[s].end(); it++){
            if(!vis[*it]){
                dfs(*it,g,vis);
            }
        }
    }
}

