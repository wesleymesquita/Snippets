#include<iostream>
#pragma vector aligned

class node3{
private:
    double c_value[9];
public:
	double GetSum(void);
};	

double node3::GetSum(void){
    double sum=0.0;
    double tmp[10];
	tmp[0] = c_value[0];
	for(int i=1;i<8;i++) sum += c_value[i];//tmp[i] = c_value[i];
    return sum;
}

int main(){
	node3 n;
	float res = n.GetSum();
}

//#pragma vector aligned

/*class node3{
private:
public:
	static int c_value[9] __attribute__((aligned(0x1000)));
	int GetSum(void);
};	

int node3::GetSum(void){
    int sum=0.0;
    int i=0;
	int c_value_tmp[9]; ;
	c_value_tmp[0] = c_value[0];
	for(i=1;i<8;i++) {
		c_value_tmp[i] = c_value_tmp[i-1] + c_value[i];
    }
	sum = c_value_tmp[7];
	return sum;
}

int main(){
	node3* n = new node3();
	float res = n->GetSum();
}*/