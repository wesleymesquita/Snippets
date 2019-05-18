#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node{
   Node* next;
   Node* prev;
   int value;
   int key;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache{
   
   protected: 
   map<int,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function

};


class LRUCache : public Cache {
public:
   LRUCache(int);
   virtual void set(int, int); //set function
   virtual int get(int); //get function
};
LRUCache::LRUCache(int capacity) {
    cp = capacity;
    tail = head = NULL;
}
void LRUCache::set(int k, int v){
    Node *n = NULL;
    bool cached = true;
    if(mp.find(k) == mp.end()) {
        n = new Node{k, v};
        mp[k] = n;
        cached = false;       
    }else { 
        n = mp[k]; 
        n->value = v; 
    }

    if(!cached) {
        if(tail == NULL && head == NULL){
           head = n;
           tail = n; 
        }else if (head != NULL && tail == head){
            head = n;
            tail->prev = head;
            head->next = tail;
        }else{
            n->next = head;
            head->prev = n;
            head = n;
        }
        if(tail != NULL && mp.size() > cp){
            Node *t = tail;
            tail = tail->prev;
            tail->next = NULL;
            mp.erase(t->key);
            delete t;
        }
    } else if(cached && n != head) {

        Node *t = n;
        if (t == tail){
            tail = tail->prev;
        }
        if(t->next != NULL) t->next->prev = t->prev;
        if(t->prev != NULL) t->prev->next = t->next;

        t->next = head;
        head->prev = t;
        head = t;
        head->prev = NULL; 

    }
}

int LRUCache::get(int k){
    auto it = mp.find(k);
     
    if (it == mp.end()) return -1;
    set(it->second->key, it->second->value);
    
    return it->second->value; 
}

int main() {
   int n, capacity,i;
   cin >> n >> capacity;
   LRUCache l(capacity);
   for(i=0;i<n;i++) {
      string command;
      cin >> command;
      if(command == "get") {
         int key;
         cin >> key;
         cout << l.get(key) << endl;
      } 
      else if(command == "set") {
         int key, value;
         cin >> key >> value;
         l.set(key,value);
      }
   }
   return 0;
}

