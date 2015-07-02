  //1RANK.CPP
  //�������
  #include  <iostream>
  #include  <fstream>
  #include  <cmath>
  using namespace std;
  class  rank
  {
  private: 
           int m, n, k;
		   double  **a;
  public:
	       rank (int mm, int nn)
		   {
			   int i;
			   m = mm; n = nn;
	           a = new double*[m];   //��̬�����ڴ�ռ�
	           for (i=0; i<m; i++) a[i] = new double[n];
		   }
	       void input ();       //���ļ��������A��Ԫ��
		   void a_rank ();      //ִ���������
           void output ();      //��������ȵ��ļ�����ʾ
		   ~rank ()        //�ͷ��ڴ�ռ�
		   {
			   int i;
			   for (i=0; i<m; i++) { delete [] a[i]; }
			   delete [] a;
		   }
  };

  void rank::input ()      //���ļ��������A��Ԫ��
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
	  fin.close ();
  }

  void rank::a_rank()
  { 
	  int i,j,nn,is,js,l;
      double q,d;
      nn=m;
      if (m>=n) nn=n;
      k=0;
      for (l=0; l<=nn-1; l++)
      { 
		  q=0.0;
          for (i=l; i<=m-1; i++)
          for (j=l; j<=n-1; j++)
		  {
			  d=fabs(a[i][j]);
	          if (d>q) { q=d; is=i; js=j;}
		  }
          if (q+1.0==1.0) break;
          k=k+1;
          if (is!=l)
		  {
			  for (j=l; j<=n-1; j++)
			  {
                  d=a[l][j]; a[l][j]=a[is][j]; a[is][j]=d;
			  }
		  }
          if (js!=l)
		  {
			  for (i=l; i<=m-1; i++)
			  {
                  d=a[i][js]; a[i][js]=a[i][l]; a[i][l]=d;
			  }
          }
          for (i=l+1; i<=n-1; i++)
		  {
			  d=a[i][l]/a[l][l];
              for (j=l+1; j<=n-1; j++)
			  {
                  a[i][j]=a[i][j]-d*a[l][j];
			  }
		  }
	  }
  }

  void rank::output ()       //������д���ļ�����ʾ
  {
	  char str2[20];
	  cout <<"\n����ļ���:  ";
	  cin >>str2;
	  ofstream fout (str2);
	  if (!fout)
	  { cout <<"\n���ܴ�����ļ� " <<str2 <<endl; exit(1); }
	  fout <<endl <<k <<endl;
	  cout <<endl <<k <<endl;
	  fout.close ();
  }

  void main ()      //������
  {
	  rank  c(5, 4); 
	  c.input ();            //���ļ��������Ԫ��
	  c.a_rank ();           //�������
	  c.output ();           //��������ȵ��ļ�����ʾ
  }
