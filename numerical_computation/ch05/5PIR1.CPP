  //5PIR1.CPP
  //��С�����������
  #include  <iostream>
  #include  <fstream>
  #include  <cmath>
  using namespace std;
  class  pir1
  {
  private: 
           int n, m;
		   double  *x, *y, *a, dt[3];
  public:
	       pir1 (int nn, int mm)
		   {
			   n = nn;  m = mm;
               x = new double[n];  //��̬�����ڴ�
	           y = new double[n];
	           a = new double[m+1]; 
		   }
	       void input ();          //���ļ�����n�����ݵ�(x, y)
		   void fit ();      //ִ����С�����������
           void output ();         //���m����϶���ʽ��m+1��ϵ��
		                           //�Լ�����ͳ�������ļ�����ʾ
		   ~pir1 ()
		   {  delete [] x, y, a;  }
  };

  void pir1::input ()      //���ļ�����n�����ݵ�(x, y)
  {
	  int  k;
	  char str1[20];
	  cout <<"\n�����ļ���:  ";
	  cin >>str1;
	  ifstream  fin (str1);
	  if (!fin)
	  { cout <<"\n���ܴ�����ļ� " <<str1 <<endl; exit(1); }
      for (k=0; k<n; k++)              //����n�����ݵ�
	  { fin >>x[k];  fin >>y[k]; }
	  fin.close ();
  }

  void pir1::fit ()       //ִ����С�����������
  { 
	  int i,j,k;
      double z,p,c,g,q,d1,d2,s[20],t[20],b[20];
      for (i=0; i<=m; i++) a[i]=0.0;
      if (m+1>n) m=n-1;
      if (m>19) m=19;
      z=0.0;
      for (i=0; i<=n-1; i++) z=z+x[i]/(1.0*n);
      b[0]=1.0; d1=1.0*n; p=0.0; c=0.0;
      for (i=0; i<=n-1; i++)
      { p=p+(x[i]-z); c=c+y[i]; }
      c=c/d1; p=p/d1;
      a[0]=c*b[0];
      if (m>0)
      { 
		  t[1]=1.0; t[0]=-p;
          d2=0.0; c=0.0; g=0.0;
          for (i=0; i<=n-1; i++)
          { 
			  q=x[i]-z-p; d2=d2+q*q;
              c=c+y[i]*q;
              g=g+(x[i]-z)*q*q;
          }
          c=c/d2; p=g/d2; q=d2/d1;
          d1=d2;
          a[1]=c*t[1]; a[0]=c*t[0]+a[0];
      }
      for (j=2; j<=m; j++)
      { 
		  s[j]=t[j-1];
          s[j-1]=-p*t[j-1]+t[j-2];
          if (j>=3)
          for (k=j-2; k>=1; k--)
              s[k]=-p*t[k]+t[k-1]-q*b[k];
          s[0]=-p*t[0]-q*b[0];
          d2=0.0; c=0.0; g=0.0;
          for (i=0; i<=n-1; i++)
          { 
			  q=s[j];
              for (k=j-1; k>=0; k--)
                  q=q*(x[i]-z)+s[k];
              d2=d2+q*q; c=c+y[i]*q;
              g=g+(x[i]-z)*q*q;
          }
          c=c/d2; p=g/d2; q=d2/d1;
          d1=d2;
          a[j]=c*s[j]; t[j]=s[j];
          for (k=j-1; k>=0; k--)
          { 
			  a[k]=c*s[k]+a[k];
              b[k]=t[k]; t[k]=s[k];
          }
      }
      dt[0]=0.0; dt[1]=0.0; dt[2]=0.0;
      for (i=0; i<=n-1; i++)
      { 
		  q=a[m];
          for (k=m-1; k>=0; k--)
              q=a[k]+q*(x[i]-z);
          p=q-y[i];
          if (fabs(p)>dt[2]) dt[2]=fabs(p);
          dt[0]=dt[0]+p*p;
          dt[1]=dt[1]+fabs(p);
      }
  }

  void pir1::output ()       //���m����϶���ʽ��m+1��ϵ��
		                       //�Լ�����ͳ�������ļ�����ʾ
  {
	  int i;
	  char str2[20];
	  cout <<"\n����ļ���:  ";
	  cin >>str2;
	  ofstream fout (str2);
	  if (!fout)
	  { cout <<"\n���ܴ�����ļ� " <<str2 <<endl; exit(1); }
      for (i=0; i<=m; i++)
	  {
		  fout <<a[i] <<endl;
		  cout <<a[i] <<endl;
	  }
	  fout <<dt[0] <<"     "<<dt[1] <<"     "<<dt[2] <<endl;
	  cout <<dt[0] <<"     "<<dt[1] <<"     "<<dt[2] <<endl;	  
	  fout.close ();
  }

  void main ()      //������
  {
	  int k;
	  pir1  solution(20, 5);
	  ofstream ft ("pir1.txt");
	  if (!ft)
	  { cout <<"\n���ܴ��ļ� pir1.txt" <<endl; exit(1); }
	  for (k=0; k<20; k++)
	     ft <<0.1*k <<"   " <<0.1*k-exp(-0.1*k) <<endl;
	  ft.close ();
	  solution.input ();          //���ļ�����n�����ݵ�(x, y)
	  solution.fit ();            //ִ����С�����������
	  solution.output ();          //���m����϶���ʽ��m+1��ϵ��
		                           //�Լ�����ͳ�������ļ�����ʾ
  }
