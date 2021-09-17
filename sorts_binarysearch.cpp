#include <iostream>
#include <bits/stdc++.h>
using namespace std;
int a[10000];
int binarysearch(int x, int a[], int left, int right){
    if(left <= right){
        int mid = (left+right)/2;
        if(a[mid] == x){
            return mid;
        }
        if(a[mid] > x){
            return binarysearch(x, a, left, mid-1);
        }
        return binarysearch(x, a, mid+1, right);
    }
    return -1;
}
void SelectionSort(int n){
    for(int i = 1; i <= n-1; i++){
        int jmin = i;
        for(int j = i+1; j <= n; j++){
            if(a[jmin] > a[j]){
                jmin = j;
            }
        }
        if(jmin != i){
            swap(a[i], a[jmin]);
        }
    }
}
void BubbleSort(int n){
    for(int i = 2; i <= n; i++){
        for(int j = n; j >= i; j--){
            if(a[j] < a[j-1]){
                swap(a[j], a[j-1]);
            }
        }
    }
}
void InsertSort(int n){
    for(int i = 2; i <= n; i++){
        int tmp = a[i];
        int j = i-1;
        while(j > 0 && a[j] > tmp){
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = tmp;
    }
}
void InsertSortwithBinarySearch(int n){
    for(int i = 2; i <= n; i++){
        int tmp = a[i];
        int left = 1;
        int right = i-1;
        while(left <= right){       //binary searching
            int mid = (left+right)/2;
            if(a[mid] > tmp){
                right = mid-1;
            }
            else{
                left = mid+1;
            }
        }
        for(int j = i; j >= left+1; j--){
            a[j] = a[j-1];
        }
        a[left] = tmp;
    }
}
void ShellSort(int n){
    int h = n/2; //La InsertSort voi buoc nhay la h (sort tung day con X = {a[i],a[i+h],a[i+2h],...} voi i = 1..h)
    while(h != 0){
        for(int k = 1; k <= h; k++){
            for(int i = k+h; i <= n; i += h){
                int tmp = a[i];
                int j = i-h;
                while(j>0 && a[j] > tmp){
                    a[j+h] = a[j];
                    j -= h;
                }
                a[j+h] = tmp;
            }
        }
        h /= 2;
    }
}
 //QuickSort
    void partQS(int L, int R){
        if(L >= R) return;
        int pivot = a[R];
        int i = L, j = R;
        while(i <= j){
            while(a[i] < pivot) i++;
            while(a[j] > pivot) j--;
            if(i <= j){
                if(i < j){
                swap(a[i], a[j]);
                }
                i++;
                j--;
            }
        }
        partQS(L, j);
        partQS(i, R);
    }
    void QuickSort(int n){
        partQS(1,n);
    }
//
//HeapSort
    void Adjust(int root, int endnode){ //Vun dong binary tree voi goc la root, voi dieu kien 2 nhanh con da dc vun dong.
        int key = a[root];
        while(root*2 <= endnode){
            int c = root*2;
            if(c < endnode && a[c] < a[c+1]) c++;
            if(a[c] <= key) break;
            a[root] = a[c];
            root = c;
        }
        a[root] = key;
    }
    void HeapSort(int n){
        for(int i = n/2; i >= 1; i--){
            Adjust(i,n);
        }
        for(int i = n; i >= 2; i--){
            swap(a[1],a[i]);
            Adjust(1,i-1);
        }
    }
//
void DistributionCountingSort(int n){ //Gia tri cua a[n] nam trong [1..M]
    int M = -999999;
    for(int i = 1; i <= n; i++){
        M = max(M, a[i]);
    }
    int c[M+1];
    int tmp[n+1];
    memset(c, 0, sizeof(c));
    for(int i = 1; i <= n; i++){
        c[a[i]]++;
    }
    for(int i = 1; i <= M; i++){
        c[i] += c[i-1];
    }
    for(int i = n; i >= 1; i--){ //dem nguoc tu n ve 1 vi Stability of Sort
        int v = a[i];
        tmp[c[v]] = a[i];
        c[v]--;
    }
    for(int i = 1; i <= n; i++){
        a[i] = tmp[i];
    }
}
//Radix Exchange Sort
    bool getbit(int x, int b){ //tra ve bit thu i cua x (zero-based). VD: getbit(0b1111011, 2) = 0
        return ((x>>b)&1);
    }
    void partRS(int L, int R, int b){
        if(L >= R) return;
        int i = L, j = R;
        while(i < j){
            while(i < j && !getbit(a[i],b)) i++;
            while(i < j && getbit(a[j],b)) j--;
            swap(a[i],a[j]);
        }
        if(!getbit(a[j],b)) j++;
        if(b > 0){
            partRS(L,j-1,b-1);
            partRS(j,R,b-1);
        }
    }
    void RadixExchangeSort(int n){
        partRS(1,n,31); //int lay toi da la 32bit -> bit tu 0 toi 31 la max.
    }
//
// Straight Radix Sort
    int GetDigit(int x, int radix, int p){ //Tim chu so thu p (zero-based) cua x theo co so radix
        for(int i = 1; i <= p; i++){
            x /= radix;
        }
        return x%radix;
    }
    void DCSort(int n, int radix, int p){ //Sort theo chu so thu p (co so radix) day x[n] sang day y[n].
        int c[radix];
        memset(c, 0, sizeof(c));
        for(int i = 1; i <= n; i++){
            int k = GetDigit(a[i], radix, p);
            c[k]++;
        }
        for(int i = 0; i <= radix-1; i++){
            c[i] += c[i-1];
        }
        int y[n+1];
        for(int i = n; i >= 1; i--){
            int k = GetDigit(a[i], radix, p);
            y[c[k]] = a[i];
            c[k]--;
        }
        for(int i = 1; i <= n; i++){
            a[i] = y[i];
        }
    }
    void StraightRadixSort(int n, int radix){ //Sort theo co so radix.
        int maxx = -999;
        for(int i = 1; i <= n; i++){
            maxx = max(maxx, a[i]);
        }
        int nDigit = 0;
        while(maxx > 0){
            nDigit++;
            maxx /= radix;
        }
        for(int p = 0; p <= nDigit-1; p++){
            DCSort(n, radix, p);
        }
    }
//
//Merge Sort (Collation Sort)
    void Merge(int x[], int y[], int L, int M, int H){ //Merge x[L..M] va x[M+1..H] vao y[L..H].
        int p = L, i = L, j = M+1;
        while(i <= M && j <= H){
            if(x[i] <= x[j]){
                y[p] = x[i];
                i++;
            }
            else{
                y[p] = x[j];
                j++;
            }
            p++;
        }
        if(i <= M){
            for(int k = i; k <= M; k++){
                y[p] = x[k];
                p++;
            }
        }
        else{
            for(int k = j; k <= H; k++){
                y[p] = x[k];
                p++;
            }
        }
    }
    void MergeLength(int x[], int y[], int n, int len){ //Chia x thanh cac cap do dai len, roi merge.
        int L = 1, M = len, H = 2*len;
        while(H <= n){
            Merge(x, y, L, M, H);
            L += 2*len;
            M += 2*len;
            H += 2*len;
        }
        if(M < n){
            Merge(x, y, L, M, n);
        }
        else if(L <= n){
            for(int i = L; i <= n; i++){
                y[i] = x[i];
            }
        }
    }
    void MergeSort(int n){
        int tmp[n+1];
        bool flag = true;
        int len = 1;
        while(len < n){
            if(flag){
                MergeLength(a, tmp, n, len);
            }
            else{
                MergeLength(tmp, a, n, len);
            }
            flag = !flag;
            len *= 2;
        }
        if(!flag){
            for(int i = 1; i <= n; i++){
                a[i] = tmp[i];
            }
        }
    }
//
int Select(int L, int R, int p){ //Ham tim ra gia tri cua a[p] sau khi sort (ko can sort).
    if(L >= R) return -1;
    int pivot = a[R];
    int i = L, j = R;
    while(i <= j){
        while(a[i] < pivot) i++;
        while(a[j] > pivot) j--;
        if(i < j){
            swap(a[i], a[j]);
        }
        i++;
        j--;
    }
    if(p <= j){
        return Select(L, j, p);
    }
    else if(p >= i){
        return Select(i, R, p);
    }
    else{
        return pivot;
    }
}
int main(){
    int n;
    cin>>n;
    for(int i = 1; i <= n; i++){
        cin>>a[i];
    }
    MergeSort(n);
    for(int i = 1; i <= n; i++) cout<<a[i]<<" ";
    return 0;
}
