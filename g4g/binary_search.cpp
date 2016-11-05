//http://www.practice.geeksforgeeks.org/problem-page.php?pid=700238
//  GeeksforGeeks Practice   Binary Search 
/*You need to complete this function */
int bin_search(int A[], int left, int right, int k)
{
    if(left > right)
        return -1;
    else if(A[left] == k)
        return left;
    else if(A[right] == k)
        return right;
    else {
        int m = (left + right)/2;
        if(A[m] == k)
            return m;
        else if (k > A[m])
            return bin_search(A, m+1, left, k);
        else 
            return bin_search(A, left, m-1, k);
    
    }    
}