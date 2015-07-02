  //6RATG2.CPP
  //������ػ��ֵ�����ʽ��
  #include  <iostream>
  #include  <fstream>
  #include  <cmath>
  using namespace std;
  class  ratg2
  {
  private: 
		   double  a, b, eps, integ;
  public:
	       ratg2 (double aa,double bb,double es)  
			                        //˳���ṩa,b,epsֵ�Ĺ��캯��
		   { a = aa; b = bb; eps = es; }
		   void integration ();    //ִ�м�����ػ��ֵ�����ʽ��
		   double ratg1(double);  //һά���ֺ���
           void output ();         //�������ֵ���ļ�����ʾ
		   double func (double,double);   //���㱻������ֵ
		   double lower(double);          //�����ڲ��������ֵy0
		   double upper(double);          //�����ڲ��������ֵy1
  };

  void ratg2::integration ()   //ִ�м�����ػ��ֵ�����ʽ��
  { 
	  int m,n,k,l,j;
      double bb[10],h[10],hh,s1,s2,t1,t2,x,g,s0,ep,s;
      m=1; n=1;
      hh=b-a; h[0]=hh;
      s1=ratg1(a); s2=ratg1(b);
      t1=hh*(s1+s2)/2.0;
      s0=t1; bb[0]=t1; ep=1.0+eps;
      while ((ep>=eps)&&(m<=9))
      { 
		  t2=0.5*t1;
          for (k=0;k<=n-1;k++)
          { 
			  x=a+(k+0.5)*hh;
              s1=ratg1(x);
              t2=t2+0.5*s1*hh;
          }
          m=m+1;
          h[m-1]=h[m-2]/2.0;
          g=t2; l=0; j=2;
          while ((l==0)&&(j<=m))
          { 
			  s=g-bb[j-2];
              if (fabs(s)+1.0==1.0) l=1;
              else g=(h[m-1]-h[j-2])/s;
              j=j+1;
          }
          bb[m-1]=g;
          if (l!=0) bb[m-1]=1.0e+35;
          s=bb[m-1];
          for (j=m;j>=2;j--) s=bb[j-2]-h[j-2]/s;
          ep=fabs(s-s0)/(1.0+fabs(s));
          n=n+n; t1=t2; s0=s; hh=hh/2.0;
      }
      integ = s;
  }

  double ratg2::ratg1(double x)
  { 
	  int m,n,k,l,j;
      double b[10],h[10],y0,y1,hh,t1,t2,s0,yy,g,ep,s;
      m=1; n=1;
	  y0 = lower(x);
	  y1 = upper(x);
      hh=y1-y0; h[0]=hh;
      t1=0.5*hh*(func(x,y0)+func(x,y1));
      s0=t1; b[0]=t1; ep=1.0+eps;
      while ((ep>=eps)&&(m<=9))
      { 
		  t2=0.5*t1;
          for (k=0;k<=n-1;k++)
          { 
			  yy=y0+(k+0.5)*hh;
              t2=t2+0.5*hh*func(x,yy);
          }
          m=m+1;
          h[m-1]=h[m-2]/2.0;
          g=t2; l=0; j=2;
          while ((l==0)&&(j<=m))
          { 
			  s=g-b[j-2];
              if (fabs(s)+1.0==1.0) l=1;
              else g=(h[m-1]-h[j-2])/s;
              j=j+1;
          }
          b[m-1]=g;
          if (l!=0) b[m-1]=1.0e+35;
          s=b[m-1];
          for (j=m;j>=2;j--) s=b[j-2]-h[j-2]/s;
          ep=fabs(s-s0)/(1.0+fabs(s));
          n=n+n; t1=t2; s0=s; hh=0.5*hh;
      }
      return(s);
  }

  void ratg2::output ()       //�������ֵ���ļ�����ʾ
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

  double ratg2::func (double x, double y)    //���㱻������ֵ
  {  return exp(x*x+y*y); }

  double ratg2::lower(double x)   //�����ڲ��������ֵy0
  {  return (-sqrt(1-x*x));  }

  double ratg2::upper(double x)   //�����ڲ��������ֵy1
  {  return (sqrt(1-x*x));  }

  void main ()      //������
  {
	  ratg2  solution (0.0, 1.0, 0.0001); 
	                        //��������˳���ṩa,b,eps��ֵ
	  solution.integration ();    //ִ�м�����ػ��ֵ�����ʽ��
	  solution.output ();    //�������ֵ���ļ�����ʾ
  }
