#include<vector>
#include<iostream>
#include<string>

template<typename T>
void insertionSort(std::vector<T>& vec){
  int n = vec.size();
  T key;
  for(int i=1; i<n; i++){
    key = vec[i];
    int j = i - 1;
    while(j >= 0 && vec[j] > key){
      std::swap(vec[j+1], vec[j]);
      j--;
    }  
    
    vec[j+1] = key;
  }
}

template<typename T>
void printVector(const std::vector<T>& vec){
  std::cout << "{";
  size_t size = vec.size();
  for(size_t i=0; i<size; i++){
    std::cout << vec[i];
    if(i != size -1){
      std::cout << " , ";
    }
  }
  std::cout << "}" << std::endl;
}

int main(){
  std::vector<int> vec{5,2,4,6,1,3};
  std::cout << "Before: ";
  printVector<int>(vec);
  insertionSort<int>(vec);
  std::cout << "After: ";
  printVector<int>(vec);
  
  /////////////////////////////
 
  std::vector<std::string> vec_str{"5","2","4","6","1","3"};
  std::cout << "Before: ";
  printVector<std::string>(vec_str);
  insertionSort<std::string>(vec_str);
  std::cout << "After: ";
  printVector<std::string>(vec_str);
  

  return 0;
}