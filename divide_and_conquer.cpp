#include<iostream>
#include<algorithm>
#include<cmath>
#include<fstream>
#include<sstream>
using namespace std;
struct Pairs{
    int x;
    int y;
    bool morn;
};
bool cmp(Pairs a,Pairs b)//排序規則 依X做排序
{
    return a.x<b.x;
}
double distance(Pairs a,Pairs b);
double divide(Pairs a[],int low,int high);//求出a從low~high範圍中兩點的最短距離
double combine(Pairs a[],int low,int mid,int high,double min_left,double min_right);//合併左右兩個集合，並確認在(line+-d)的範圍內有沒有比d更小的值，最後回傳最小值
int main()
{

    ifstream fin;
    int line=0;
    double distances;
    char dot;
    Pairs pairs[1000];
    fin.open("node.txt");
    string ss;

    while(getline(fin,ss))//卻認為幾個點
    {
        stringstream s;
        s<<ss;
        s>>pairs[line].x;
        s>>dot;
        s>>pairs[line].y;

        line++;
    }
     sort(pairs,pairs+line,cmp);//依x 做排序
     double dis=divide(pairs,0,line-1);//劃分從點pairs[0]~pairs[num-1]
     for(int i=0;i<line;i++)
        for(int j=0;j<line;j++)
     {
         distances=sqrt(pow(pairs[i].x-pairs[j].x,2)+pow(pairs[i].y-pairs[j].y,2));
         if(dis==distances)
         {
             pairs[i].morn=true;
             pairs[j].morn=true;
         }
     }
     for(int i=0;i<line;i++)
     {
         if(pairs[i].morn==true)
            cout<<pairs[i].x<<","<<pairs[i].y<<endl;
     }
     cout<<dis<<endl;

    return 0;
}
double Distance(Pairs a,Pairs b)//算每兩點的距離
{
    double distance;
    double subx,suby;
    subx=a.x-b.x;
    suby=a.y-b.y;
    distance=sqrt(pow(subx,2)+pow(suby,2));
    return distance;
}
double divide(Pairs a[],int low,int high)
{
    if(low>=high) return 99999;//切到剩一個點 return inf

    int mid=(low+high)/2;
    double min_left=divide(a,low,mid);
    double min_right=divide(a,mid+1,high);
    return combine(a,low,mid,high,min_left,min_right);
}
double combine(Pairs a[],int low,int mid,int high,double min_left,double min_right)
{
    double d=(min_left<min_right)?min_left:min_right;
    double line=(double)(a[mid].x+a[mid+1].x)*0.5; //line:左集合與右集合的中間線x座標
    double min_D=d;
    for(int i=mid+1;a[i].x<line+d && i<=high;i++){ //枚舉line+-d範圍內左右集合的點
        for(int j=mid;a[j].x>line-d && j>=low;j--){
            double temp=Distance(a[i],a[j]);
            if(temp<min_D) min_D=temp;
        }
    }
    return min_D;
}
