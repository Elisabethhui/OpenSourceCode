  //4NETN.CPP
  //��ţ�ٷ��������Է�����
  #include  <iostream>
  #include  <fstream>
  #include  <cmath>
  using namespace std;
  class  netn
  {
  private: 
           int n, Max;
		   double  *x, *f, eps, t, h;
		   double  **a, *b;
  public:
	       netn (int nn)
		   {
			   int k;
			   n = nn;
               x = new double[n];  //��̬�����ڴ�
	           f = new double[n];
	           b = new double[n];
	           a = new double*[n];
	           for (k=0; k<n; k++) a[k] = new double[n];
		   }
	       void input ();    //���ļ����뾫��Ҫ��eps�����Ʊ���t��
		                 //����h��ֵ������������Max�Լ����һ���ֵ
		   void netn_root ();      //ִ����ţ�ٷ�
		   void gauss ();          //ȫѡ��ԪGauss��ȥ��
           void output ();         //��������Է������һ��⵽�ļ�����ʾ
		   void func (double *);   //���㷽�������˺���ֵf
		   ~netn ()
		   {
			   int  k;
			   for (k=0; k<n; k++) { delete [] a[k]; }
			   delete [] a;
			   delete [] x, f, b; 
		   }
  };

  void netn::input ()      //���ļ����뾫��Ҫ��eps�����Ʊ���t��
		              //����h��ֵ������������Max�Լ����һ���ֵ
  {
	  int  k;
	  char str1[20];
	  cout <<"\n�����ļ���:  ";
	  cin >>str1;
	  ifstream  fin (str1);
	  if (!fin)
	  { cout <<"\n���ܴ�����ļ� " <<str1 <<endl; exit(1); }
	  fin >>eps;  fin >>t; fin >>h;  fin >>Max;  //����eps��t��h��Max
	  for (k=0; k<n; k++)  fin>>x[k];     //�����ֵ
	  fin.close ();
  }

  void netn::netn_root ()         //ִ����ţ�ٷ�
  { 
	  int i,j,l;
      double am,z,beta,d;
      l=0; am=1.0+eps;
      while (am>=eps)
      { 
          func (x);
          am=0.0;
          for (i=0; i<=n-1; i++)
          {
			  b[i] = f[i];
			  z=fabs(f[i]);
              if (z>am) am=z;
          }
          if (am>=eps)
          { 
			  l=l+1;
              if (l==Max)
              {
				  cout <<"\n���ܲ�������" <<endl;
                  return;
              }
              for (j=0; j<=n-1; j++)
              { 
				  z=x[j]; x[j]=x[j]+h;
                  func (x);
                  for (i=0; i<=n-1; i++) a[i][j] = f[i];
                  x[j]=z;
              }
              gauss();
              beta=1.0;
              for (i=0; i<=n-1; i++) beta=beta-b[i];
              if (fabs(beta)+1.0==1.0)
              {
				  cout <<"\nBeta=0. ������ʧ�ܣ�" <<endl;
                  return;
              }
              d=h/beta;
              for (i=0; i<=n-1; i++) x[i]=x[i]-d*b[i];
              h=t*h;
          }
      }
      cout <<"\nʵ�ʵ�������Ϊ: " <<l <<endl;
  }

  void netn::gauss ()         //ִ��ȫѡ��ԪGauss��ȥ��
  { 
	  int *js,l,k,i,j,is;
      double d,t;
      js = new int[n];
      l=1;
      for (k=0; k<=n-2; k++)
      { 
		  d=0.0;
          for (i=k;i<=n-1;i++)
          for (j=k;j<=n-1;j++)
          { 
			  t=fabs(a[i][j]);
              if (t>d) { d=t; js[k]=j; is=i;}
          }
          if (d+1.0==1.0) l=0;
          else
          { if (js[k]!=k)
              for (i=0;i<=n-1;i++)
              { 
                  t=a[i][k]; 
				  a[i][k]=a[i][js[k]]; 
				  a[i][js[k]]=t;
              }
              if (is!=k)
              { 
				  for (j=k;j<=n-1;j++)
                  { 
                      t=a[k][j]; 
					  a[k][j]=a[is][j]; 
					  a[is][j]=t;
                  }
                  t=b[k]; b[k]=b[is]; b[is]=t;
              }
          }
          if (l==0)
          { 
			  delete [] js;
			  cout <<"\nϵ���������죡�޽�." <<endl;
              return;
          }
          d=a[k][k];
          for (j=k+1;j<=n-1;j++)
              a[k][j]=a[k][j]/d;
          b[k]=b[k]/d;
          for (i=k+1;i<=n-1;i++)
          { 
			  for (j=k+1;j<=n-1;j++)
                  a[i][j]=a[i][j]-a[i][k]*a[k][j];
              b[i]=b[i]-a[i][k]*b[k];
          }
      }
      d=a[n-1][n-1];
      if (fabs(d)+1.0==1.0)
      { 
		  delete [] js;
		  cout <<"\nϵ���������죡�޽�." <<endl;
          return;
      }
      b[n-1]=b[n-1]/d;
      for (i=n-2;i>=0;i--)
      { 
		  t=0.0;
          for (j=i+1;j<=n-1;j++)
              t=t+a[i][j]*b[j];
          b[i]=b[i]-t;
      }
      js[n-1]=n-1;
      for (k=n-1;k>=0;k--)
        if (js[k]!=k)
        { 
			t=b[k]; b[k]=b[js[k]]; b[js[k]]=t;
		}
    delete [] js;
  }

  void netn::output ()       //��������Է������һ��⵽�ļ�����ʾ
  {
	  int k;
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

  void netn::func (double *x)//���㷽�������˺���ֵf
  {
	  f[0] = x[0]*x[0] + x[1]*x[1] + x[2]*x[2] - 1.0;
	  f[1] = 2*x[0]*x[0] + x[1]*x[1] - 4*x[2];
	  f[2] = 3*x[0]*x[0] - 4*x[1] + x[2]*x[2];
  }

  void main ()      //������
  {
	  netn  root(3);
	  root.input ();      //���ļ����뾫��Ҫ��eps�����Ʊ���t��
		                   //����h��ֵ������������Max�Լ����һ���ֵ
	  root.netn_root ();    //ִ����ţ�ٷ�
	  root.output ();      //��������Է������һ��⵽�ļ�����ʾ
  }

//0.785197   0.496611   0.369923   
//ʵ�ʵ���5��