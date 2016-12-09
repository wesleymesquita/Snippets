/* http://www.practice.geeksforgeeks.org/problem-page.php?pid=247*/
/* Series AP */
#include <stdio.h>

int main() {
	//code
    int t; scanf("%d", &t);
    while(t--){
        int f, s; scanf("%d %d", &f, &s);
        int a = s-f;
        int n; scanf("%d", &n);
        int r;
        r = f + (n-1)*a;
        printf("%d\n", r);
    }
	
	return 0;
}