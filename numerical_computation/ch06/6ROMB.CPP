  //6ROMB.CPP
  //Romberg�����
  #include  <iostream>
  #include  <fstream>
  #include  <cmath>
  using namespace std;
  class  romb 
  {
  private: 
		   double  a, b, eps, integ;
  public:
	       romb (double aa, double bb, double es)//˳���ṩa,b,epsֵ�Ĺ��캯��
           { a = aa; b = bb; eps = es; }
		   void integration ();    //ִ��Romberg�����
           void output ();         //�������ֵ���ļ�����ʾ
		   double func (double);   //���㱻������ֵ
  };

  void romb::integration ()     //ִ��Romberg�����
  { 
	  int m,n,i,k;
      double y[10],h,ep,p,x,s,q;
      h=b-a;
      y[0]=h*(func (a)+func (b))/2.0;
      m=1; n=1; ep=eps+1.0;
      while ((ep>=eps)&&(m<=9))
      { 
		  p=0.0;
          for (i=0;i<=n-1;i++)
          { 
			  x=a+(i+0.5)*h;
              p=p+func (x);
          }
          p=(y[0]+h*p)/2.0;
          s=1.0;
          for (k=1;k<=m;k++)
          { 
			  s=4.0*s;
              q=(s*p-y[k-1])/(s-1.0);
              y[k-1]=p; p=q;
          }
          ep=fabs(q-y[m-1]);
          m=m+1; y[m-1]=q; n=n+n; h=h/2.0;
      }
      integ = q;
  }

  void romb::output ()       //�������ֵ���ļ�����ʾ
  {
	  char str2[20];
	  cout <<"\n����ļ���:  ";
	  cin >>str2;
	  ofstream fout (str2);
	  if (!fout)
	  { cout <<"\n���ܴ�����ļ� " <<str2 <<endl; exit(1); }
	  fout <<integ <<endl;  cout <<"����ֵ = " <<integ <<endl;
	  fout.close ();
  }

  double romb::func (double x)
  {  return x/(4+x*x); }

  void main ()      //������
  {
	  romb  solution(0.0, 1.0, 0.000001); //��������˳���ṩa, b, epsֵ
	  solution.integration ();    //ִ��Romberg�����
	  solution.output ();    //�������ֵ���ļ�����ʾ
  }
