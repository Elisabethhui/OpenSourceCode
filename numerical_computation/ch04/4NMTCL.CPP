  //4NMTCL.CPP
  //Monte-Carlo���������Է�����
  #include  <iostream>
  #include  <fstream>
  #include  <cmath>
  using namespace std;
  class  nmtcl
  {
  private: 
           int n, m;
		   double  b, eps, *x;
		   double  r, *y;
  public:
	       nmtcl (int nn)
		   {
			   n = nn;
	           x = new double[n];  //��̬�����ڴ�ռ�
	           y = new double[n];
		   }
	       void input ();    //���ļ�����b,m,eps�Լ��������ĳ�ֵ
		   void solution ();        //ִ��Monte-Carlo��
		   double rnd ();           //����һ�������
           void output ();         //������������ļ�����ʾ
		   double func (double *);   //����ģ����
		   ~nmtcl ()
		   { delete [] x, y;  }
  };

  void nmtcl::input ()      //���ļ�����b,m,eps�Լ��������ĳ�ֵ
  {
	  int  i;
	  char str1[20];
	  cout <<"\n�����ļ���:  ";
	  cin >>str1;
	  ifstream  fin (str1);
	  if (!fin)
	  { cout <<"\n���ܴ�����ļ� " <<str1 <<endl; exit(1); }
	  fin >>b;   fin >>m;  fin >>eps;      //����b,m,eps
	  for (i=0; i<n; i++) fin >>x[i];    //�����������ֵ
	  fin.close ();
  }

  void nmtcl::solution ()        //ִ��Monte-Carlo��
  { 
	  int k,i;
      double a,z,z1;
      a=b; k=1; r=1.0; z=func (x);
      while (a>=eps)
      { 
		  for (i=0; i<=n-1; i++)
              y[i]=-a+2.0*a*rnd()+x[i];
          z1=func (y);
          k=k+1;
          if (z1>=z)
          { if (k>m) { k=1; a=a/2.0; }}
          else
          { 
			  k=1; 
              for (i=0; i<=n-1; i++) x[i]=y[i];
              z=z1;
              if (z<eps)  return;
          }
      }
  }

  double nmtcl::rnd ()      //����һ�������
  { 
	  int m;
      double s,u,v,p;
      s=65536.0; u=2053.0; v=13849.0;
      m=(int)(r/s); r=r-m*s;
      r=u*r+v; m=(int)(r/s);
      r=r-m*s; p=r/s;
      return(p);
  }

  void nmtcl::output ()       //������������ļ�����ʾ
  {
	  int  k;
	  char str2[20];
	  cout <<"\n����ļ���:  ";
	  cin >>str2;
	  ofstream fout (str2);
	  if (!fout)
	  { cout <<"\n���ܴ�����ļ� " <<str2 <<endl; exit(1); }
	  fout <<endl;  cout <<endl;
	  for (k=0; k<n; k++)
	  {
		  fout <<x[k] <<"   ";
		  cout <<x[k] <<"   ";
	  }
	  fout <<endl;  cout <<endl;
	  fout.close ();
  }

  double nmtcl::func (double *x)    //����ģ����
  {
	  double f, f0, f1, f2;
	  f0 = 3*x[0] + x[1] + 2*x[2]*x[2] - 3;
	  f1 = -3*x[0] + 5*x[1]*x[1] + 2*x[0]*x[2] - 1;
	  f2 = 25*x[0]*x[1] + 20*x[2] + 12;
	  f = sqrt(f0*f0 + f1*f1 + f2*f2);
	  return f;
  }

  void main ()      //������
  {
	  nmtcl  root(3); 
	  root.input ();       //���ļ�����b,m,eps�Լ��������ĳ�ֵ
	  root.solution ();    //ִ��Monte-Carlo��
	  root.output ();     //������������ļ�����ʾ
  }

//1.09603   -0.799754   0.495681 