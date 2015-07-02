  //7EULER.CPP
  //������Euler����
  #include  <iostream>
  #include  <iomanip>
  #include  <fstream>
  #include  <cmath>
  using namespace std;
  class  euler
  {
  private: 
	       int n, k;
		   double  t, h, *y, **z;
		   double  *d, *p, *q;
  public:
	       euler (int nn, int kk)
		   {
			   int i;
			   n = nn; k = kk;
               y = new double[n];       //��̬�����ڴ�
	           d = new double[n];
	           p = new double[n];
	           q = new double[n];
	           z = new double*[n];
	           for (i=0; i<n; i++) { z[i] = new double[k]; }
		   }
	       void  input ();         //���ļ��������ݳ�Աt,h
		                      //�Լ�n��δ֪��������ʼ��t���ĺ���ֵ
		   void solution ();    //ִ�ж�����Euler����
           void output ();        //���k�����ֵ���
		                          //��δ֪����ֵ���ļ�����ʾ
		   void func (double,double*,double*);   
		                         //����΢�ַ������и������Ҷ˺���ֵ
		   ~euler ()
		   { 
			   int i;
			   for (i=0; i<n; i++) { delete [] z[i]; }
			   delete [] z;
			   delete [] y, d, p, q;
		   }
  };

  void euler::input ()     //���ļ��������ݳ�Աt,h
		                      //�Լ�n��δ֪��������ʼ��t���ĺ���ֵ
  {
	  int  i;
	  char str1[20];
	  cout <<"\n�����ļ���:  ";
	  cin >>str1;
	  ifstream  fin (str1);
	  if (!fin)
	  { cout <<"\n���ܴ�����ļ� " <<str1 <<endl; exit(1); }
      fin >>t >>h;          //����t,h
      for (i=0; i<n; i++)  fin >>y[i];  
	                            //����n��δ֪��������ʼ��t���ĺ���ֵ	  
	  fin.close ();
  }

  void euler::solution ()  //ִ�ж�����Euler����
  { 
	  int i,j;
      double x;
      for (j=0; j<k; j++)
	  { 
		  x=t+(j-1)*h;
          func (x,y,d);
          for (i=0; i<=n-1; i++)  p[i]=y[i]+h*d[i];
          x=t+j*h;
          func (x,p,d);
          for (i=0; i<=n-1; i++)  q[i]=y[i]+h*d[i];
          for (i=0; i<=n-1; i++)
          { 
			  y[i]=(p[i]+q[i])/2.0;
              z[i][j]=y[i];
          }
      }
  }

  void euler::output () //���k�����ֵ��ϵ�δ֪����ֵ���ļ�����ʾ
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

  void euler::func (double t, double y[], double d[])
  {
	  d[0] = y[1];
	  d[1] = -y[0];
	  d[2] = -y[2];
  }

  void main ()      //������
  {
	  euler  s(3, 10);           //��������
	  s.input ();        //���ļ��������ݳ�Աt,h
		                 //�Լ�n��δ֪��������ʼ��t���ĺ���ֵ	  
	  s.solution ();    //ִ�ж�����Euler����
	  s.output ();   //���k�����ֵ��ϵ�δ֪����ֵ���ļ�����ʾ
  }
