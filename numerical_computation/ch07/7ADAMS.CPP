  //7ADAMS.CPP
  //AdamsԤ��У����
  #include  <iostream>
  #include  <iomanip>
  #include  <fstream>
  #include  <cmath>
  using namespace std;
  class  adams
  {
  private: 
	       int n, k;
		   double  t, h, eps, *y, **z;
		   double  *d, *b, *e, *c, *g, *bb;
  public:
	       adams (int nn, int kk)
		   {
			   int i;
			   n = nn; k = kk;
               y = new double[n];      //��̬�����ڴ�
	           d = new double[n];
	           b = new double[4*n];
	           e = new double[n];
	           c = new double[n];
	           g = new double[n];
	           bb = new double[n];
	           z = new double*[n];
	           for (i=0; i<n; i++) { z[i] = new double[k]; }
		   }
	       void  input ();         //���ļ��������ݳ�Աt,h,eps
		                      //�Լ�n��δ֪��������ʼ��t���ĺ���ֵ
		   void solution ();    //ִ��AdamsԤ��У����
		   void rkt();          //ִ���Ľ�Runge-Kutta��ʽ
           void output ();        //���k�����ֵ���
		                          //��δ֪����ֵ���ļ�����ʾ
		   void func (double,double*,double*);   
		                         //����΢�ַ������и������Ҷ˺���ֵ
		   ~adams ()
		   { 
			   int i;
			   for (i=0; i<n; i++) { delete [] z[i]; }
			   delete [] z;
			   delete [] y, d, b, e, c, g, bb;
		   }
  };

  void adams::input ()     //���ļ��������ݳ�Աt,h,eps
		                      //�Լ�n��δ֪��������ʼ��t���ĺ���ֵ
  {
	  int  i;
	  char str1[20];
	  cout <<"\n�����ļ���:  ";
	  cin >>str1;
	  ifstream  fin (str1);
	  if (!fin)
	  { cout <<"\n���ܴ�����ļ� " <<str1 <<endl; exit(1); }
      fin >>t >>h >>eps;        //����t,h,eps
      for (i=0; i<n; i++)  fin >>y[i];  
	                            //����n��δ֪��������ʼ��t���ĺ���ֵ	  
	  fin.close ();
  }

  void adams::solution ()   //ִ��AdamsԤ��У����
  { 
      int i,j,m;
      double a,q;
      a=t;
      func (t,y,d);
      for (i=0; i<=n-1; i++) b[i]=d[i];
      for (i=0; i<3; i++)
          if (i<=k-1)
		  { 
			  t=a+i*h;
              rkt();
              for (j=0; j<=n-1; j++) z[j][i]=y[j];
              t = a + (i+1)*h;
              func (t,y,d);
              for (j=0; j<=n-1; j++) b[(i+1)*n+j]=d[j];
		  }
      for (i=3; i<k; i++)
      { 
		  for (j=0; j<=n-1; j++)
          { 
			  q=55.0*b[3*n+j]-59.0*b[2*n+j];
              q=q+37.0*b[n+j]-9.0*b[j];
              y[j]=z[j][i-1]+h*q/24.0;
              b[j]=b[n+j];
              b[n+j]=b[n+n+j];
              b[n+n+j]=b[n+n+n+j];
          }
          t=a+(i+1)*h;
          func (t,y,d);
          for (m=0; m<=n-1; m++) b[n+n+n+m]=d[m];
          for (j=0; j<=n-1; j++)
          { 
			  q=9.0*b[3*n+j]+19.0*b[n+n+j]-5.0*b[n+j]+b[j];
              y[j]=z[j][i-1]+h*q/24.0;
              z[j][i]=y[j];
          }
          func (t,y,d);
          for (m=0; m<=n-1; m++) b[3*n+m]=d[m];
      }
      t = a;
  }

  void adams::rkt ()  //ִ���Ľ�Runge-Kutta��ʽ
  { 
	  int m,i,j,k;
      double hh,p,dt,x,tt,q,a[4];
      hh=h; m=1; p=1.0+eps; x=t;
      for (i=0; i<=n-1; i++) c[i]=y[i];
      while (p>=eps)
      { 
		  a[0]=hh/2.0; a[1]=a[0]; a[2]=hh; a[3]=hh;
          for (i=0; i<=n-1; i++)
          { g[i]=y[i]; y[i]=c[i];}
          dt=h/m; t=x;
          for (j=0; j<=m-1; j++)
          { 
			  func (t,y,d);
              for (i=0; i<=n-1; i++) 
              { bb[i]=y[i]; e[i]=y[i];}
              for (k=0; k<=2; k++)
              { 
				  for (i=0; i<=n-1; i++)
                  { 
					  y[i]=e[i]+a[k]*d[i];
                      bb[i]=bb[i]+a[k+1]*d[i]/3.0;
                  }
                  tt=t+a[k];
                  func(tt,y,d);
              }
              for (i=0; i<=n-1; i++)
                  y[i]=bb[i]+hh*d[i]/6.0;
              t=t+dt;
          }
          p=0.0;
          for (i=0; i<=n-1; i++)
          { 
			  q=fabs(y[i]-g[i]);
              if (q>p) p=q;
          }
          hh=hh/2.0; m=m+m;
      }
  }

  void adams::output ()   //���k�����ֵ���
	                      //��δ֪����ֵ���ļ�����ʾ
  {
	  int i, j;
	  char str2[20];
	  cout <<"\n����ļ���:  ";
	  cin >>str2;
	  ofstream fout (str2);
	  if (!fout)
	  { cout <<"\n���ܴ�����ļ� " <<str2 <<endl; exit(1); }
      for (i=0; i<k; i++)
	  {
		  cout <<"t = " <<t+(i+1)*h <<endl;
		  for (j=0; j<n; j++)
		  {
			  fout <<z[j][i] <<"   ";
			  cout <<"y(" <<j <<")=" <<setw(12) <<z[j][i] <<"  ";
		  }
		  fout <<endl;  cout <<endl;
	  }
	  fout.close ();
  }

  void adams::func (double t, double y[], double d[])
  {
	  d[0] = y[1];
	  d[1] = -y[0];
	  d[2] = -y[2];
  }

  void main ()      //������
  {
	  adams  s(3, 10);           //��������
	  s.input ();        //���ļ��������ݳ�Աt,h,eps
		                 //�Լ�n��δ֪��������ʼ��t���ĺ���ֵ
	  s.solution ();    //ִ��AdamsԤ��У����
	  s.output (); //���k�����ֵ��ϵ�δ֪����ֵ���ļ�����ʾ
  }
