#include <iostream>
using namespace std;
///运用next数组回朔
void GetNext(string T,int *next){
    int j=0;
    int i=1;
    next[1]=0;
    while(i < T[0]){
        if(0 == j || T[i] == T[j]){
            i++;
            j++;
            //这个判断主要是为了区别两个字符相等的情况
            if(next[i] != next[j]){
                next[i] = j;///将j的数值赋值给next[i];
            }else {
                next[i]=next[j];///此时是下标移动，就是将前一个next数组的值赋值给后一个,然后下次不相等的时候就会返回到这个下标的值
                                ///这个情况是几个字符串相等的时候直接就会回朔到相等的第一个，使得效率提升
            }
        }else{
            j=next[j];///此时是回朔到next[j]的下标的值，假设这个数值是k,此时应该比较的数组就是next[i]与next[k];
        }
    }
}
//返回子串在主串s第pos个字符之后的位置
///开始主串与子串匹配
int Index_Next(string S,string T,int position){
    int i=position;
    int j=1;
    int next[100];
    GetNext(T,next);
    while(i <= S[0] && j <= T[0]){
        if(0 == j || S[i] == T[j]){///主串和子串相等的话,就继续往下遍历
            i++;
            j++;
        }else{
            j=next[j];///不相等的话,就将用赋值后的j的T[j]的数值去与T[i]比较
        }
    }
    if(j > T[0]){
        return i-T[0];
    }else{
        return 0;
    }
}
int main() {
    char str[100];
    char str1[100];
    int next[100];
    int position,i=1,j=1;
    char m,n;
    cout<<"输入S串字符:"<<endl;
    cin>>m;
    str[0]=9;
    str1[0]=5;
    while('#' != m){
        str[i++]=m;
        str[i]='\0';
        cin>>m;
    }
    cout<<"输入T串字符:"<<endl;
    cin>>n;
    while('#' != n){
        str1[j++]=n;
        str1[j]='\0';
        cin>>n;
    }
    GetNext(str1,next);
    for(i=1;i<=str1[0]; i++){
        cout<<next[i]<<" ";
    }
    cout<<endl;
    cout<<"输入位置:";
    cin>>position;
    int x=Index_Next(str,str1,position);
    cout<<x;
    return 0;
}