#include<iostream>
using namespace std;

template<class T>
T max(T arr[], int n){
  //pram: n 数组长度，防止越界
  T max=arr[0]; //max存储最大值
  for(int i=0;i<n;i++){
    if(arr[i]>max)max=arr[i];
  }
  return max;
}

template<class T>
T min(T arr[], int n){
  T min=arr[0];
  for(int i=0;i<n;i++){
    if(arr[i]<min)min=arr[i];
  }
  return min;
}

int main(){
  int arr_int[] = {1,2,3,4,3,1,6};
  double arr_dou[] = {1.23,4.3,2.4,6.5,6.6,0.3};
  cout<<"int \n"<<"max: "<<max(arr_int, 7)<<"; min: "<<min(arr_int, 7)<<endl;
  cout<<"double \n"<<"max: "<<max(arr_dou, 6)<<"; min: "<<min(arr_dou, 6)<<endl;
}
