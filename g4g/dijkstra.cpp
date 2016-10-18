// Implementing Dijkstra | Set 1 (Adjacency Matrix)
// http://www.practice.geeksforgeeks.org/problem-page.php?pid=700334
class Node{
public:    
    int id;
    int dist;
    Node* next;
    Node(int id, int dist){
        this->id = id;
        this->dist = dist;
        this->next = NULL;
    }
};

class List{
public:
    List(){
        beg = new Node*;
        *beg = NULL;
    }
    ~List(){
    	delete beg;
    }
    void add(int id, int dist){
        	
        Node* n = new Node(id, dist); 
            
        if((*beg) == NULL){
        	(*beg) = n;    
        }
        else if(dist < (*beg)->dist){
            n->next = *beg;
            *beg = n;
        }
        else{
            Node* c = *beg;
            Node* p = NULL;
            
            while(c!= NULL && c->dist < dist){
                p = c;
                c = c->next;
            }
		              
            if(c == NULL){
                p->next = n;    
            }
            else if(c != NULL and p==NULL){
            	c->next = n;
            }
            else{
            
                p->next = n;
                n->next = c;
                
            }    
        }
    }
    
    int get_next(){
        int r = (*beg)->id;
        Node *old_beg = *beg;
        (*beg) = (*beg)->next;
        delete old_beg;
        return r;
    }
    
    bool has_nodes(){
        return *beg != NULL;
    }
    
    Node** beg;
    
};


void dijkstra(int g[MAX][MAX], int s,int V)
{
	
    vector<int> dist(V, MAX);
	List to_visit;
    vector<int> prev(V, -1);
    vector<bool> visited(V, false);
    

    dist[s] = 0;
    to_visit.add(s, 0);
    
    while(to_visit.has_nodes() > 0){
        
        int c = to_visit.get_next();
        
        for(int i=0; i<V; i++){
            if (!visited[i] && g[c][i] != 0){
                if(dist[c] + g[c][i] < dist[i]){
                    dist[i] = dist[c] + g[c][i];
                    prev[i]=c;
                }
                to_visit.add(i, dist[i]);
                
            }    
            visited[c] = true;
        }
    }        
        
    for(int i=0; i<V; i++){
        cout << dist[i] << " ";
    }    
}