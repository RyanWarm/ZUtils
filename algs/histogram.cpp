#include<cstdio>
#include<iostream>
using namespace std;
int stack[100010]={-2},len[100010];
long long ans;
int main()
{
     int n,top,h;
     while(scanf("%d",&n), n)
     {
          top=0;ans=0;
          for(int i=0;i<=n;i++)
          {
               if(i<n)scanf("%d",&h);
               else h=-1;
               if(h > stack[top])
               {
                    stack[++top]=h;
                    len[top]=1;
               }
               else
               {
                    int l = 0;
                    while(stack[top] >= h)
                    {
                         ans=max(ans,(long long)(l+len[top])*stack[top]);
                         l += len[top--];
                    }
                    stack[++top] = h;
                    len[top] = l + 1;
               }
          }
          printf("%lld\n",ans);
     }
}