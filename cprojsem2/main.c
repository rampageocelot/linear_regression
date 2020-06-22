
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BSIZE 100


struct values
{
    int a[3][1000];
    float b[3][1000];
    int s1,s2,s3,m11,m21,m31;
    float m12,m22,m32;
    float m,ci;
};
struct values coeff(struct values s)
{
    int i;
    float cd=0,xd=0,m,c;
    for(i=0;i<s.s2;i++)
    {
        cd=cd+(s.a[1][i]-s.m21)*(s.a[1][i]-s.m22);
        xd=xd+((s.a[1][i]-s.m21)*(s.a[1][i]-s.m21));
    }
    printf("CD = %f\n",cd);
    printf("XD = %f\n",xd);
    m=cd/xd;
    c=s.m22-m*s.m21;
    printf("m = %f\n",m);
    printf("c = %f\n",c);
    s.m=m;
    s.ci=c;
    printf("The coefficients have been determined.\n");
    return(s);
}
struct values preprocess(struct values s)
{
    int i;
    for(i=0;i<s.s1;i++)
    {
        if(s.a[0][i]==0)
            s.a[0][i]=s.m11;
        if(s.b[0][i]==0)
            s.b[0][i]=s.m12;
    }
    for(i=0;i<s.s2;i++)
    {
        if(s.a[1][i]==0)
            s.a[1][i]=s.m21;
        if(s.b[1][i]==0)
            s.b[1][i]=s.m22;
    }
    for(i=0;i<s.s3;i++)
    {
        if(s.a[2][i]==0)
            s.a[2][i]=s.m31;
        if(s.b[2][i]==0)
            s.b[2][i]=s.m32;
    }
    printf("Elements have been Pre-Processed\n");
    return(s);
}
struct values pred(struct values s)
{
    float pr[s.s3];
    float er=0,sum=0,ac,finer;
    int i;
    for(i=0;i<s.s3;i++)
    {
        sum=sum+s.b[2][i];
    }
    for(i=0;i<s.s3;i++)
    {
       float u=(float)s.a[2][i];
       pr[i]=(s.m*u)+s.ci;
    }
    for(i=0;i<s.s3;i++)
    {
        er=er+abs(s.b[2][i]-pr[i]);
    }
    finer=(er/sum)*100;
    ac=100.00-finer;
    printf("The Accuracy is : %f\n",ac);
    return(s);
}
struct values mean(struct values s)
{
    int sx=0;
    float sy=0;
    int i=0;
    for(i=0;i<s.s1;i++)
    {
        sx=sx+s.a[0][i];
        sy=sy+s.b[0][i];
    }
    s.m11=sx/s.s1;
    s.m12=sy/s.s1;
    sx=0;
    sy=0;
    for(i=0;i<s.s2;i++)
    {
        sx=sx+s.a[1][i];
        sy=sy+s.b[1][i];
    }
    s.m21=sx/s.s2;
    s.m22=sy/s.s2;
    sx=0;
    sy=0;
    for(i=0;i<s.s3;i++)
    {
        sx=sx+s.a[2][i];
        sy=sy+s.b[2][i];
    }
    s.m31=sx/s.s3;
    s.m32=sy/s.s3;
    sx=0;
    sy=0;
    printf("The means have been determined.\n");
    return(s);
}
struct values price(struct values s)
{
    int area;
    float price;
    printf("Enter the area in kilo sq. feet : ");
    scanf("%d",&area);
    price=(s.m*area)+s.ci;
    printf("The Approximate price would be : %fK USD\n",price);
}
int main(void)
{
        char buffer[BSIZE];
        FILE *f;
        char *field;
        int x1,i;
        float y1;
        struct values val;
        i=0;
        f=fopen("tr.csv","r");
        if(f==NULL)
        {
                printf("The file could not be Opened\n");
                exit(1);
        }
        while(fgets(buffer,BSIZE,f))
        {
                field=strtok(buffer,",");
                x1=atoi(field);
                val.a[0][i]=x1;
                field=strtok(NULL,",");
                y1=atof(field);
                val.b[0][i]=y1;
                i++;
        }
        fclose(f);
        val.s1=i;
        for(i=0;i<val.s1-1;i++)
    {
        val.a[0][i]=val.a[0][i+1];
        val.b[0][i]=val.b[0][i+1];
    }
    val.s1=val.s1-1;
        int train;
        printf("Enter the percentage to be trained : ");
        scanf("%d",&train);
        val.s2=((train*val.s1)/100);
        val.s3=val.s1-val.s2;
        for(i=0;i<val.s2;i++)
    {
        val.a[1][i]=val.a[0][i];
        val.b[1][i]=val.b[0][i];
    }
    int o=0;
    for(i=val.s1-val.s2;i<val.s1;i++)
    {
        val.a[2][o]=val.a[0][i];
        val.b[2][o]=val.b[0][i];
        o++;
    }
    int flag=0;
    while(flag!=1)
    {
        int choice=0;
        printf("\n\n1.Find Mean.\n");
        printf("2.Pre-process Values.\n");
        printf("3.Find Coefficients.\n");
        printf("4.Predict Accuracy.\n");
        printf("5.Find Approximate Price.\n");
        printf("6.Exit.\n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                val=mean(val);
                break;
            case 2:
                val=preprocess(val);
                break;
            case 3:
                val=coeff(val);
                break;
            case 4:
                val=pred(val);
                break;
            case 5:
                val=price(val);
                break;
            case 6:
                flag=1;
                break;
            default:
                printf("Enter Correct option.");
        }
    }
}






