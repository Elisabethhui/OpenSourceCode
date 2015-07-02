  //3TLVS.CPP
  //��Levinson�������Toeplitz������
  #include  <iostream>
  #include  <fstream>
  #include  <cmath>
  using namespace std;
  class  tlvs
  {
  private: 
           int n;
		   double  *t, *b, *x;
  public:
	       tlvs (int nn)
		   {
			   n = nn;
	           t = new double[n];     //��̬�����ڴ�ռ�	  
	           b = new double[n];
	           x = new double[n];
		   }
	       void input ();    //���ļ���������T�Լ���������B
		   void t_tlvs ();   //ִ��Levinson�����㷨
           void output ();   //���������ļ�����ʾ
		   ~tlvs ()
		   {
			   delete [] t, b, x;
		   }
  };

  void tlvs::input ()      //���ļ���������T�Լ���������B
  {
	  int  i;
	  char str1[20];
	  cout <<"\n�����ļ���:  ";
	  cin >>str1;
	  ifstream  fin (str1);
	  if (!fin)
	  { cout <<"\n���ܴ�����ļ� " <<str1 <<endl; exit(1); }
	  for (i=0; i<n; i++)  fin >>t[i];           //��������T
	  for (i=0; i<n; i++)  fin >>b[i];           //���볣������B
	  fin.close ();
  }

  void tlvs::t_tlvs ()        //ִ��Levinson�����㷨
  { 
	  int i,j,k;
      double a,beta,q,c,h,*y,*s;
      s = new double[n];
      y = new double[n];
      a=t[0];
      if (fabs(a)+1.0==1.0)
      { 
		  delete [] s, y; 
		  cout <<"\n������ʧ�ܣ�" <<endl;
		  return;
	  }
      y[0]=1.0; x[0]=b[0]/a;
      for (k=1; k<=n-1; k++)
      { 
		  beta=0.0; q=0.0;
          for (j=0; j<=k-1; j++)
          { 
			  beta=beta+y[j]*t[j+1];
              q=q+x[j]*t[k-j];
          }
          if (fabs(a)+1.0==1.0)
		  { 
		      delete [] s, y; 
		      cout <<"\n������ʧ�ܣ�" <<endl;
		      return;
		  }
          c=-beta/a; s[0]=c*y[k-1]; y[k]=y[k-1];
          if (k!=1)
            for (i=1; i<=k-1; i++)
                s[i]=y[i-1]+c*y[k-i-1];
          a=a+c*beta;
          if (fabs(a)+1.0==1.0)
		  { 
		      delete [] s, y; 
		      cout <<"\n������ʧ�ܣ�" <<endl;
		      return;
		  }
          h=(b[k]-q)/a;
          for (i=0; i<=k-1; i++)
          { x[i]=x[i]+h*s[i]; y[i]=s[i];}
          x[k]=h*y[k];
      }
      delete [] s, y;
      return;
  }

  void tlvs::output ()       //���������ļ�����ʾ
  {
	  int  i;
	  char str2[20];
	  cout <<"\n����ļ���:  ";
	  cin >>str2;
	  ofstream fout (str2);
	  if (!fout)
	  { cout <<"\n���ܴ�����ļ� " <<str2 <<endl; exit(1); }
	  fout <<endl;  cout <<endl;
	  for (i=0; i<n; i++)
	  {
		  fout <<x[i] <<"   ";
		  cout <<x[i] <<"   ";
	  }
	  fout <<endl;  cout <<endl;
	  fout.close ();
  }

  void main ()      //������
  {
	  tlvs  t(6); 
	  t.input ();         //���ļ�����ϵ������A�Լ���������B
	  t.t_tlvs ();        //ִ��Levinson�����㷨
	  t.output ();        //���������ļ�����ʾ
  }
