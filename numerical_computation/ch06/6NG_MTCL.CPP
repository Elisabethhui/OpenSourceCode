  //6NG_MTCL.CPP
  //Monte-Carlo�������ػ���
  #include  <iostream>
  #include  <fstream>
  #include  <cmath>
  using namespace std;
  class  ng_mtcl
  {
  private: 
	       int  n;
		   double  *a, *b, integ, r;
		   double  *x;
  public:
	       ng_mtcl (int nn)
		   {
			   n = nn;
               a = new double[n];  //��̬�����ڴ�
	           b = new double[n];
	           x = new double[n];
		   }
	       void input ();   //���ļ�������ָ������ޡ�����ֵ
		   void integration ();    //ִ��Monte-Carlo��
           void output ();         //�������ֵ���ļ�����ʾ
		   double func ();        //���㱻������ֵ
           double rnd ();          //����һ�������
		   ~ng_mtcl ()
		   { delete [] a, b, x;  }
  };

  void ng_mtcl::input ()  //���ļ�������ָ������ޡ�����ֵ
  {
	  int  k;
	  char str1[20];
	  cout <<"\n�����ļ���:  ";
	  cin >>str1;
	  ifstream  fin (str1);
	  if (!fin)
	  { cout <<"\n���ܴ�����ļ� " <<str1 <<endl; exit(1); }
      for (k=0; k<n; k++)  fin >>a[k];  //˳������������ֵ
      for (k=0; k<n; k++)  fin >>b[k];  //˳������������ֵ
	  fin.close ();
  }

  void ng_mtcl::integration ()  //ִ��Monte-Carlo��
  { 
	  int m,i;
      double s,d;
      r=1.0; d=10000.0; s=0.0;
      for (m=0; m<=9999; m++)
      { 
		  for (i=0; i<=n-1; i++)
              x[i]=a[i]+(b[i]-a[i])*rnd ();
          s=s+func ()/d;
      }
      for (i=0; i<=n-1; i++) s=s*(b[i]-a[i]);
      integ = s;
  }

  double ng_mtcl::rnd ()      //����һ�������
  { 
	  int m;
      double s,u,v,p;
      s=65536.0; u=2053.0; v=13849.0;
      m=(int)(r/s); r=r-m*s;
      r=u*r+v; m=(int)(r/s);
      r=r-m*s; p=r/s;
      return(p);
  }

  void ng_mtcl::output ()       //�������ֵ���ļ�����ʾ
  {
	  char str2[20];
	  cout <<"\n����ļ���:  ";
	  cin >>str2;
	  ofstream fout (str2);
	  if (!fout)
	  { cout <<"\n���ܴ�����ļ� " <<str2 <<endl; exit(1); }
	  fout <<integ <<endl;  cout <<"����ֵ = " <<integ <<endl;
	  fout.close ();
  }

  double ng_mtcl::func ()
  {  return (x[0]*x[0] + x[1]*x[1] + x[2]*x[2]); }

  void main ()      //������
  {
	  ng_mtcl  solution(3); 
	  solution.input ();     //���ļ�������ָ������ޡ�����ֵ
	  solution.integration ();    //ִ��Monte-Carlo��
	  solution.output ();    //�������ֵ���ļ�����ʾ
  }
