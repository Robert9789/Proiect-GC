#include<bits/stdc++.h>
#include<graphics.h>
#include<string>
using namespace std;

struct valori{
int x;
int y;
};
valori val[100][100];
int lungimi[100];

pair<int, int> mid;




int quad(pair<int, int> p)
{
	if (p.first >= 0 && p.second >= 0)
		return 1;
	if (p.first <= 0 && p.second >= 0)
		return 2;
	if (p.first <= 0 && p.second <= 0)
		return 3;
	return 4;
}


int orientation(pair<int, int> a, pair<int, int> b,
				pair<int, int> c)
{
	int res = (b.second-a.second)*(c.first-b.first) -
			(c.second-b.second)*(b.first-a.first);

	if (res == 0)
		return 0;
	if (res > 0)
		return 1;
	return -1;
}

bool compare(pair<int, int> p1, pair<int, int> q1)
{
	pair<int, int> p = make_pair(p1.first - mid.first,
								p1.second - mid.second);
	pair<int, int> q = make_pair(q1.first - mid.first,
								q1.second - mid.second);

	int one = quad(p);
	int two = quad(q);

	if (one != two)
		return (one < two);
	return (p.second*q.first < q.second*p.first);
}


vector<pair<int, int>> merger(vector<pair<int, int> > a,
							vector<pair<int, int> > b)
{

	int n1 = a.size(), n2 = b.size();

	int ia = 0, ib = 0;
	for (int i=1; i<n1; i++)
		if (a[i].first > a[ia].first)
			ia = i;


	for (int i=1; i<n2; i++)
		if (b[i].first < b[ib].first)
			ib=i;


	int inda = ia, indb = ib;
	bool done = 0;
	while (!done)
	{
		done = 1;
		while (orientation(b[indb], a[inda], a[(inda+1)%n1]) >=0)
			inda = (inda + 1) % n1;

		while (orientation(a[inda], b[indb], b[(n2+indb-1)%n2]) <=0)
		{
			indb = (n2+indb-1)%n2;
			done = 0;
		}
	}

	int uppera = inda, upperb = indb;
	inda = ia, indb=ib;
	done = 0;
	int g = 0;
	while (!done)
	{
		done = 1;
		while (orientation(a[inda], b[indb], b[(indb+1)%n2])>=0)
			indb=(indb+1)%n2;

		while (orientation(b[indb], a[inda], a[(n1+inda-1)%n1])<=0)
		{
			inda=(n1+inda-1)%n1;
			done=0;
		}
	}

	int lowera = inda, lowerb = indb;
	vector<pair<int, int>> ret;

	int ind = uppera;
	ret.push_back(a[uppera]);
	while (ind != lowera)
	{
		ind = (ind+1)%n1;
		ret.push_back(a[ind]);
	}

	ind = lowerb;
	ret.push_back(b[lowerb]);
	while (ind != upperb)
	{
		ind = (ind+1)%n2;
		ret.push_back(b[ind]);
	}
	return ret;

}

vector<pair<int, int>> bruteHull(vector<pair<int, int>> a)
{

	set<pair<int, int> >s;

	for (int i=0; i<a.size(); i++)
	{
		for (int j=i+1; j<a.size(); j++)
		{
			int x1 = a[i].first, x2 = a[j].first;
			int y1 = a[i].second, y2 = a[j].second;

			int a1 = y1-y2;
			int b1 = x2-x1;
			int c1 = x1*y2-y1*x2;
			int pos = 0, neg = 0;
			for (int k=0; k<a.size(); k++)
			{
				if (a1*a[k].first+b1*a[k].second+c1 <= 0)
					neg++;
				if (a1*a[k].first+b1*a[k].second+c1 >= 0)
					pos++;
			}
			if (pos == a.size() || neg == a.size())
			{
				s.insert(a[i]);
				s.insert(a[j]);
			}
		}
	}

	vector<pair<int, int>>ret;
	for (auto e:s)
		ret.push_back(e);


	mid = {0, 0};
	int n = ret.size();
	for (int i=0; i<n; i++)
	{
		mid.first += ret[i].first;
		mid.second += ret[i].second;
		ret[i].first *= n;
		ret[i].second *= n;
	}
	sort(ret.begin(), ret.end(), compare);
	for (int i=0; i<n; i++)
		ret[i] = make_pair(ret[i].first/n, ret[i].second/n);

	return ret;
}


vector<pair<int, int>> divide(vector<pair<int, int>> a)
{
	if (a.size() <= 5)
		return bruteHull(a);


	vector<pair<int, int>>left, right;
	for (int i=0; i<a.size()/2; i++)
		left.push_back(a[i]);
	for (int i=a.size()/2; i<a.size(); i++)
		right.push_back(a[i]);


	vector<pair<int, int>>left_hull = divide(left);
	vector<pair<int, int>>right_hull = divide(right);


	return merger(left_hull, right_hull);
}

int main()
{ int i,j,x,y,k,cord1,cord2,prim , second;



    cout<<"Introduceti perechi de valori intre 1 si 1000, urmate de un Enter pentru urmatoarea pereche";
    cout<<"\n";
    cout<<"\n";
    cout<<"Introduceti 'Exit' si apasati Enter cand ati terminat de introdus valorile";
	vector<pair<int, int> > a;
	int Max;
	while(cin>>x>>y)
    {   // introduce punctele in vectorul a
        a.push_back(make_pair(x,y));
        if(x>Max) Max=x;
        if(y>Max) Max=y;
    }


    int diviziune;

  diviziune=(Max/100)+1;
  if(Max%100==0) diviziune--;


	int n = a.size();


	sort(a.begin(), a.end());
	vector<pair<int, int> >ans ;


	cout<<"Multimea initiala de puncte :"<<"\n";
	 for ( auto e:a)
        cout <<"("<< e.first << " ,"
			<< e.second <<")"<< endl;

    cout<<"\n";
	cout << "Straturi ale Convex Layers:\n";


         vector<int>::iterator it;
        int rankk=0;
        int lungime = a.size();
        while(lungime>=1)
        { ans=divide(a);

            for (auto e:ans)

        for( auto p: ans)
        { prim = p.first;
             int seconds =p.second;
             int poz =-1;
        for (auto e :a)
       { poz++;
           if(prim== e.first&&seconds == e.second)
             {
                a.erase(a.begin()+poz);

             }
       }
        }
               rankk++;
               lungimi[rankk]=ans.size();
          int poz2=0;
        for (auto e:ans){
        val[rankk][++poz2].x=e.first;
        val[rankk][poz2].y=e.second;
        lungime = a.size();

        ans.clear();

        if(a.size()==1) lungime=0;


        }}




        for(i=1;i<=rankk;i++)
       {   cout<<"Strat "<< i <<": \n";
           for(j=1;j<=lungimi[i];j++)
            cout<<"("<<val[i][j].x<<","<<val[i][j].y<<")"<<"\n";
            cout<<"\n";
       }

       int  Lengthx=610;
       int Heighty=610;
       initwindow(Lengthx,Heighty);






     int vol=Heighty/100;
    for(i=1;i<=rankk;i++)
      {
          line((val[i][1].x/diviziune)*vol+10, Heighty-(val[i][1].y/diviziune)*vol-10,(val[i][lungimi[i]].x/diviziune)*vol+10, Heighty-(val[i][lungimi[i]].y/diviziune)*vol-10);

      for(j=1;j<lungimi[i];j++)
      {
           line((val[i][j].x/diviziune)*vol+10,Heighty-(val[i][j].y/diviziune)*vol-10,(val[i][j+1].x/diviziune)*vol+10, Heighty-(val[i][j+1].y/diviziune)*vol-10);
      }
      }




     for(i=1;i<=rankk;i++)
       for(j=1;j<=lungimi[i];j++)
      outtextxy((val[i][j].x/diviziune)*vol+10 , Heighty-(val[i][j].y/diviziune)*vol-10 ,"*");


        char buff[33];
        char buff2[33];
        char buff3[33];

     for(i=1;i<=rankk;i++)


       for(j=1;j<=lungimi[i];j++)
        {itoa(val[i][j].x,buff,10);
       itoa(val[i][j].y,buff2,10);
       strcpy(buff3,"(");
       strcat(buff,",");
       strcat(buff,buff2);
       strcat(buff,")");
       strcat(buff3,buff);
    outtextxy((val[i][j].x/diviziune)*vol-40 , Heighty-(val[i][j].y/diviziune)*vol-10 ,buff3);
      }


         line(10,1,10,Heighty-10);
          line(10,Heighty-10,Lengthx,Heighty-10);

            char buffer[33];
             int proportieL = (Lengthx-10)/10;
             int proportieH = (Heighty-10)/10;
          for(int i=1;i<=10;i++)
          {  itoa(i*10*diviziune,buffer,10);
             outtextxy(proportieL*i+10,Heighty-10,buffer);// asta face pt axa Ox
             outtextxy(10,proportieH*(10-i),buffer);//asta face pt axa OY

          }


        getch();
       closegraph();




	return 0;
}
