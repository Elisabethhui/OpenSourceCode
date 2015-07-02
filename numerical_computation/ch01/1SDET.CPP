  //1SDET.CPP
  //������ʽֵ
  #include  <iostream>
  #include  <fstream>
  #include  <cmath>
  using namespace std;
  class  sdet
  {
  private: 
           int n;
		   double  **a, det;
  public:
	       sdet (int  nn)
		   {
			   int i;
			   n = nn;
	           a = new double*[n];  //��̬�����ڴ�ռ�
	           for (i=0; i<n; i++) a[i] = new double[n];
		   }
	       void input ();      //���ļ��������Ԫ��
		   void a_det ();      //ִ��������ʽֵ
           void output ();     //�������ʽֵ���ļ�����ʾ
		   ~sdet ()
		   {
			   int i;
			   for (i=0; i<n; i++) { delete [] a[i]; }
			   delete [] a;
		   }
  };

  void sdet::input ()      //���ļ��������Ԫ��
  {
	  int  i, j;
	  char str1[20];
	  cout <<"\n�����ļ���:  ";
	  cin >>str1;
	  ifstream  fin (str1);
	  if (!fin)
	  { cout <<"\n���ܴ�����ļ� " <<str1 <<endl; exit(1); }
	  for (i=0; i<n; i++)                       //�������A
		  for (j=0; j<n; j++)  fin >>a[i][j];
	  fin.close ();
  }

  void sdet::a_det ()                //ִ��������ʽֵ
  { 
	  int i,j,k,is,js;
      double f,q,d;
      f=1.0; det=1.0;
      for (k=0; k<=n-2; k++)
      { 
		  q=0.0;
          for (i=k; i<=n-1; i++)
          for (j=k; j<=n-1; j++)
          { 
			  d=fabs(a[i][j]);
	          if (d>q)  { q=d; is=i; js=j;}
          }
          if (q+1.0==1.0)  det=0.0;
          else
		  {
			  if (is!=k)
			  {
				  f=-f;
                  for (j=k; j<=n-1; j++)
				  { 
                     d=a[k][j]; a[k][j]=a[is][j]; a[is][j]=d;
				  }
			  }
              if (js!=k)
			  {
				 f=-f;
                 for (i=k; i<=n-1; i++)
				 { 
                     d=a[i][js]; a[i][js]=a[i][k]; a[i][k]=d;
				 }
			  }
              det=det*a[k][k];
              for (i=k+1; i<=n-1; i++)
			  {
				 d=a[i][k]/a[k][k];
                 for (j=k+1; j<=n-1; j++)
				 {
                     a[i][j]=a[i][j]-d*a[k][j];
				 }
			  }
		  }
	  }
	  det=f*det*a[n-1][n-1];
  }

  void sdet::output ()       //�������ʽֵ���ļ�����ʾ
  {
	  char str2[20];
	  cout <<"\n����ļ���:  ";
	  cin >>str2;
	  ofstream fout (str2);
	  if (!fout)
	  { cout <<"\n���ܴ�����ļ� " <<str2 <<endl; exit(1); }
	  fout <<endl <<det <<endl;
	  cout <<endl <<det <<endl;
	  fout.close ();
  }

  void main ()      //������
  {
	  sdet  d(4);
	  d.input ();         //���ļ��������Ԫ��
	  d.a_det ();         //������ʽֵ
	  d.output ();        //�������ʽֵ���ļ�����ʾ
  }
