  //6SIMP.CPP
  //�䲽��Simpson�����
  #include  <iostream>
  #include  <fstream>
  #include  <cmath>
  using namespace std;
  class  simp 
  {
  private: 
		   double  a, b, eps, integ;
  public:
	       simp (double aa, double bb, double es)//˳���ṩa,b,epsֵ�Ĺ��캯��
           { a = aa; b = bb; eps = es; }
		   void integration ();    //ִ�б䲽��Simpson�����
           void output ();         //�������ֵ���ļ�����ʾ
		   double func (double);   //���㱻������ֵ
  };

  void simp::integration ()   //ִ�б䲽��Simpson�����
  { 
	  int n,k;
      double h,t1,t2,s1,s2,ep,p,x;
      n=1; h=b-a;
      t1=h*(func (a) + func (b))/2.0;
      s1=t1;
      ep=eps+1.0;
      while (ep>=eps)
      { 
		  p=0.0;
          for (k=0;k<=n-1;k++)
          { 
			  x=a+(k+0.5)*h;
              p=p+func (x);
          }
          t2=(t1+h*p)/2.0;
          s2=(4.0*t2-t1)/3.0;
          ep=fabs(s2-s1);
          t1=t2; s1=s2; n=n+n; h=h/2.0;
      }
      integ = s2;
  }

  void simp::output ()       //�������ֵ���ļ�����ʾ
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

  double simp::func (double x)
  {  double y;
     y = log(1.0+x)/(1.0+x*x);
	 return y; 
  }

  void main ()      //������
  {
	  simp  solution(0.0, 1.0, 0.000001); //��������˳���ṩa, b, epsֵ
	  solution.integration ();    //ִ�б䲽��Simpson�����
	  solution.output ();    //�������ֵ���ļ�����ʾ
  }
