  //3GMQR.CPP
  //��Householder�任���������С��������
  #include  <iostream>
  #include  <fstream>
  #include  <cmath>
  using namespace std;
  class  gmqr
  {
  private: 
           int m, n;
		   double  **a, **q, *b;
  public:
	       gmqr (int mm, int nn)
		   {
			   int i;
			   m = mm; n = nn;
	           a = new double*[m];   //��̬�����ڴ�ռ�
	           for (i=0; i<m; i++) a[i] = new double[n];
	           q = new double*[m];
	           for (i=0; i<m; i++) q[i] = new double[m];
	           b = new double[m];
		   }
	       void input ();    //���ļ�����ϵ������A�볣������B
		   void qr ();       //QR�ֽ�
		   void a_gmqr ();   //������С���˽�
           void output ();   //���Q��R�����Լ���С���˽⵽�ļ�����ʾ
		   ~gmqr ()
		   {
			   int i;
			   for (i=0; i<m; i++) { delete [] a[i]; }
			   delete [] a;
			   for (i=0; i<m; i++) { delete [] q[i]; }
			   delete [] q;
			   delete [] b;
		   }
  };

  void gmqr::input ()      //���ļ�����ϵ������A�볣������B
  {
	  int  i, j;
	  char str1[20];
	  cout <<"\n�����ļ���:  ";
	  cin >>str1;
	  ifstream  fin (str1);
	  if (!fin)
	  { cout <<"\n���ܴ�����ļ� " <<str1 <<endl; exit(1); }
	  for (i=0; i<m; i++)                       //�������A
		  for (j=0; j<n; j++)  fin >>a[i][j];
	  for (i=0; i<m; i++) fin >>b[i];           //���볣������B
	  fin.close ();
  }

  void gmqr::qr ()      //QR�ֽ�
  { 
	  int i,j,k,nn,jj;
      double u,alpha,w,t;
      if (m<n)
      { 
		  cout <<"\nQR�ֽ�ʧ�ܣ�" <<endl;
		  exit(1);
	  }
      for (i=0; i<=m-1; i++)
      for (j=0; j<=m-1; j++)
      { 
		  q[i][j]=0.0;
          if (i==j) q[i][j]=1.0;
      }
      nn=n;
      if (m==n) nn=m-1;
      for (k=0; k<=nn-1; k++)
	  {
		  
		  u=0.0;
          for (i=k; i<=m-1; i++)
          { 
			  w=fabs(a[i][k]);
              if (w>u) u=w;
          }
          alpha=0.0;
          for (i=k; i<=m-1; i++)
          { t=a[i][k]/u; alpha=alpha+t*t; }
          if (a[k][k]>0.0) u=-u;
          alpha=u*sqrt(alpha);
          if (fabs(alpha)+1.0==1.0)
          { 
			  cout <<"\nQR�ֽ�ʧ�ܣ�" <<endl;
			  exit(1);
		  }
          u=sqrt(2.0*alpha*(alpha-a[k][k]));
          if ((u+1.0)!=1.0)
          { 
			  a[k][k]=(a[k][k]-alpha)/u;
              for (i=k+1; i<=m-1; i++) a[i][k]=a[i][k]/u;
              for (j=0; j<=m-1; j++)
              { 
				  t=0.0;
                  for (jj=k; jj<=m-1; jj++)
                      t=t+a[jj][k]*q[jj][j];
                  for (i=k; i<=m-1; i++)
                      q[i][j]=q[i][j]-2.0*t*a[i][k];
              }
              for (j=k+1; j<=n-1; j++)
              { 
				  t=0.0;
                  for (jj=k; jj<=m-1; jj++)
                      t=t+a[jj][k]*a[jj][j];
                  for (i=k; i<=m-1; i++)
                      a[i][j]=a[i][j]-2.0*t*a[i][k];
              }
              a[k][k]=alpha;
              for (i=k+1; i<=m-1; i++)  a[i][k]=0.0;
          }
      }
      for (i=0; i<=m-2; i++)
      for (j=i+1; j<=m-1;j++)
      { 
          t=q[i][j]; q[i][j]=q[j][i]; q[j][i]=t;
      }
  }

  void gmqr::a_gmqr()         //������С���˽�
  { 
	  int i,j;
      double d,*c;
      qr ();                 //QR�ֽ�
      c = new double[n];
      for (i=0; i<=n-1; i++)
      { 
		  d=0.0;
          for (j=0; j<=m-1; j++)
          d=d+q[j][i]*b[j];
          c[i]=d;
      }
      b[n-1]=c[n-1]/a[n-1][n-1];
      for (i=n-2; i>=0; i--)
      { 
		  d=0.0;
          for (j=i+1; j<=n-1; j++)
          d=d+a[i][j]*b[j];
          b[i]=(c[i]-d)/a[i][i];
      }
      delete [] c; 
	  return;
  }

  void gmqr::output ()   //���Q��R�����Լ���С���˽⵽�ļ�����ʾ
  {
	  int  i, j;
	  char str2[20];
	  cout <<"\n����ļ���:  ";
	  cin >>str2;
	  ofstream fout (str2);
	  if (!fout)
	  { cout <<"\n���ܴ�����ļ� " <<str2 <<endl; exit(1); }
	  for (i=0; i<m; i++)
	  {
		  for (j=0; j<m; j++)
		  {
			  fout <<"    " <<q[i][j];
			  cout <<"    " <<q[i][j];
		  }
		  fout <<endl;  cout <<endl;
	  }
      fout <<endl;  cout <<endl;
	  for (i=0; i<m; i++)
	  {
		  for (j=0; j<n; j++)
		  {
			  fout <<"    " <<a[i][j];
			  cout <<"    " <<a[i][j];
		  }
		  fout <<endl;  cout <<endl;
	  }
	  fout <<endl;  cout <<endl;
	  for (i=0; i<n; i++)
	  {
		  fout <<b[i] <<"   ";
		  cout <<b[i] <<"   ";
	  }
	  fout <<endl;  cout <<endl;
	  fout.close ();
  }

  void main ()      //������
  {
	  gmqr  q(4, 3); 
	  q.input ();         //���ļ�����ϵ������A�볣������B
	  q.a_gmqr ();        //������С���˽�
	  q.output ();    //���Q��R�����Լ���С���˽⵽�ļ�����ʾ
  }
