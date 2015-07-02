  //1CINV.CPP
  //����������
  #include  <iostream>
  #include  <cmath>
  #include  <fstream>
  using namespace std;
  class  cinv
  {
  private: 
           int n;
		   double  **ar, **ai;
  public:
	       cinv (int nn)
		   {
			   int i;
			   n = nn;
	           ar = new double*[n];   //��̬�����ڴ�ռ�
	           for (i=0; i<n; i++) ar[i] = new double[n];
	           ai = new double*[n];
	           for (i=0; i<n; i++) ai[i] = new double[n];
		   }
	       void input ();    //���ļ��������A��Ԫ��
		   void inv ();      //ִ����������
           void output ();   //���������ļ�
		   ~cinv ()          //�ͷ��ڴ�ռ�
		   {
			   int i;
			   for (i=0; i<n; i++) { delete [] ar[i]; }
			   delete [] ar;
			   for (i=0; i<n; i++) { delete [] ai[i]; }
			   delete [] ai;
		   }
  };

  void cinv::input ()      //���ļ��������A��Ԫ��
  {
	  int  i, j;
	  char str1[20];
	  cout <<"\n�����ļ���:  ";
	  cin >>str1;
	  ifstream  fin (str1);
	  if (!fin)
	  { cout <<"\n���ܴ�����ļ� " <<str1 <<endl; exit(1); }
	  for (i=0; i<n; i++)                       //�������A
		  for (j=0; j<n; j++)  fin >>ar[i][j];
	  for (i=0; i<n; i++)
		  for (j=0; j<n; j++)  fin >>ai[i][j];
	  fin.close ();
  }

  void cinv::inv ()          //ִ����������
  { 
	  int *is,*js,i,j,k;
      double p,q,s,t,d,b;
      is = new int[n];
      js = new int[n];
      for (k=0; k<=n-1; k++)
      { 
		  d=0.0;
          for (i=k; i<=n-1; i++)
          for (j=k; j<=n-1; j++)
          {
			  
              p=ar[i][j]*ar[i][j]+ai[i][j]*ai[i][j];
              if (p>d) { d=p; is[k]=i; js[k]=j;}
          }
          if (d+1.0==1.0)
          {
			  delete [] is, js;
              cout <<"\n�������죡û�������.  ";
			  exit(1);
          }
          if (is[k]!=k)
            for (j=0; j<=n-1; j++)
			{

                t=ar[k][j]; ar[k][j]=ar[is[k]][j]; ar[is[k]][j]=t;
                t=ai[k][j]; ai[k][j]=ai[is[k]][j]; ai[is[k]][j]=t;
			}
          if (js[k]!=k)
            for (i=0; i<=n-1; i++)
            { 
                t=ar[i][k]; ar[i][k]=ar[i][js[k]]; ar[i][js[k]]=t;
                t=ai[i][k]; ai[i][k]=ai[i][js[k]]; ai[i][js[k]]=t;
            }
          ar[k][k]=ar[k][k]/d; ai[k][k]=-ai[k][k]/d;
          for (j=0; j<=n-1; j++)
            if (j!=k)
            {
                p=ar[k][j]*ar[k][k]; q=ai[k][j]*ai[k][k];
                s=(ar[k][j]+ai[k][j])*(ar[k][k]+ai[k][k]);
                ar[k][j]=p-q; ai[k][j]=s-p-q;
            }
          for (i=0; i<=n-1; i++)
            if (i!=k)
            { 
                for (j=0; j<=n-1; j++)
                  if (j!=k)
                  { 
                      p=ar[k][j]*ar[i][k]; q=ai[k][j]*ai[i][k];
                      s=(ar[k][j]+ai[k][j])*(ar[i][k]+ai[i][k]);
                      t=p-q; b=s-p-q;
                      ar[i][j]=ar[i][j]-t;
                      ai[i][j]=ai[i][j]-b;
                  }
            }
          for (i=0; i<=n-1; i++)
            if (i!=k)
            { 
                p=ar[i][k]*ar[k][k]; q=ai[i][k]*ai[k][k];
                s=(ar[i][k]+ai[i][k])*(ar[k][k]+ai[k][k]);
                ar[i][k]=q-p; ai[i][k]=p+q-s;
            }
      }
      for (k=n-1; k>=0; k--)
      { 
		  if (js[k]!=k)
            for (j=0; j<=n-1; j++)
            { 
                t=ar[k][j]; ar[k][j]=ar[js[k]][j]; ar[js[k]][j]=t;
                t=ai[k][j]; ai[k][j]=ai[js[k]][j]; ai[js[k]][j]=t;
            }
          if (is[k]!=k)
            for (i=0; i<=n-1; i++)
            { 
                t=ar[i][k]; ar[i][k]=ar[i][is[k]]; ar[i][is[k]]=t;
                t=ai[i][k]; ai[i][k]=ai[i][is[k]]; ai[i][is[k]]=t;
            }
      }
      delete [] is,js;
  }

  void cinv::output ()       //���������ļ�
  {
	  int  i, j;
	  char str2[20];
	  cout <<"\n����ļ���:  ";
	  cin >>str2;
	  ofstream fout (str2);
	  if (!fout)
	  { cout <<"\n���ܴ�����ļ� " <<str2 <<endl; exit(1); }
	  for (i=0; i<n; i++)
	  {
		  for (j=0; j<n; j++)
		  {
			  fout <<"    " <<ar[i][j];
			  cout <<"    " <<ar[i][j];
		  }
		  fout <<endl;  cout <<endl;
	  }
	  fout <<endl;  cout <<endl;
	  for (i=0; i<n; i++)
	  {
		  for (j=0; j<n; j++)
		  {
			  fout <<"    " <<ai[i][j];
			  cout <<"    " <<ai[i][j];
		  }
		  fout <<endl;  cout <<endl;
	  }
	  fout.close ();
  }

  void main ()      //������
  {
	  cinv  c(4);
	  c.input ();         //���ļ��������A��Ԫ��
	  c.inv ();           //ִ����������
	  c.output ();        //���������ļ�
  }