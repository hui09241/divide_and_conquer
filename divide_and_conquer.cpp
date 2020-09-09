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
bool cmp(Pairs a,Pairs b)//�ƧǳW�h ��X���Ƨ�
{
    return a.x<b.x;
}
double distance(Pairs a,Pairs b);
double divide(Pairs a[],int low,int high);//�D�Xa�qlow~high�d�򤤨��I���̵u�Z��
double combine(Pairs a[],int low,int mid,int high,double min_left,double min_right);//�X�֥��k��Ӷ��X�A�ýT�{�b(line+-d)���d�򤺦��S����d��p���ȡA�̫�^�ǳ̤p��
int main()
{

    ifstream fin;
    int line=0;
    double distances;
    char dot;
    Pairs pairs[1000];
    fin.open("node.txt");
    string ss;

    while(getline(fin,ss))//�o�{���X���I
    {
        stringstream s;
        s<<ss;
        s>>pairs[line].x;
        s>>dot;
        s>>pairs[line].y;

        line++;
    }
     sort(pairs,pairs+line,cmp);//��x ���Ƨ�
     double dis=divide(pairs,0,line-1);//�����q�Ipairs[0]~pairs[num-1]
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
double Distance(Pairs a,Pairs b)//��C���I���Z��
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
    if(low>=high) return 99999;//����Ѥ@���I return inf

    int mid=(low+high)/2;
    double min_left=divide(a,low,mid);
    double min_right=divide(a,mid+1,high);
    return combine(a,low,mid,high,min_left,min_right);
}
double combine(Pairs a[],int low,int mid,int high,double min_left,double min_right)
{
    double d=(min_left<min_right)?min_left:min_right;
    double line=(double)(a[mid].x+a[mid+1].x)*0.5; //line:�����X�P�k���X�������ux�y��
    double min_D=d;
    for(int i=mid+1;a[i].x<line+d && i<=high;i++){ //�T�|line+-d�d�򤺥��k���X���I
        for(int j=mid;a[j].x>line-d && j>=low;j--){
            double temp=Distance(a[i],a[j]);
            if(temp<min_D) min_D=temp;
        }
    }
    return min_D;
}
