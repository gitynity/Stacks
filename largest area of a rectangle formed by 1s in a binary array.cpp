#include <bits/stdc++.h>
using namespace std;

vector<int> nsl(vector<int> a)
{
	stack<int> s;
	s.push(-1);
	s.push(0);
	vector<int> left;
	left.push_back(-1);	//nothing is in the left array of the leftmost element

	for (int i = 1; i < a.size(); i++)
		while (true)
		{
			if (s.top() != -1 && a[s.top()] >= a[i])
			{
				s.pop();
			}
			else if (s.top() != -1 && a[s.top()] < a[i])
			{
				left.push_back(s.top());
				s.push(i);
				break;
			}
			else if (s.top() == -1)
			{
				left.push_back(-1);
				s.push(i);
				break;
			}
		}
	return left;
}

vector<int> nsr(vector<int> a)
{
	stack<int> s;
	s.push(a.size());	   //a.size()	nothing is in the right array of the rightmost element
	s.push(a.size() - 1); //6
	vector<int> right;
	right.push_back(a.size());

	for (int i = a.size() - 2; i >= 0; i--)
		while (true)
		{
			if (s.top() != a.size() && a[s.top()] >= a[i])
			{
				s.pop();
			}
			else if (s.top() != a.size() && a[s.top()] < a[i])
			{
				right.push_back(s.top());
				s.push(i);
				break;
			}
			else if (s.top() == a.size())
			{
				right.push_back(a.size());
				s.push(i);
				break;
			}
		}
	reverse(right.begin(), right.end());
	return right;
}

vector<int> find_area(vector<int> leftlimit , vector<int> rightlimit , vector<int> oneDheights)
{
	vector<int> lwidth;
	vector<int> rwidth;
	vector<int> area;

	int lw = 0;
	int rw = 0;

	for (int i = 0; i < leftlimit.size(); i++)
	{
		if (leftlimit[i] < 0)
			lw = i + 1;
		else if (leftlimit[i] >= 0)
		{
			lw = i - leftlimit[i];
		}

		lwidth.push_back(lw);
	}

	for (int i = 0; i < rightlimit.size(); i++)
	{
		if (rightlimit[i] >= rightlimit.size())
		{
			rw = rightlimit.size() - i;
		}
		else if (rightlimit[i] < rightlimit.size())
		{
			rw = rightlimit[i] - i;
		}
		rwidth.push_back(rw);
	}

	for(int i=0;i<leftlimit.size();i++)
	{
		int temp = lwidth[i] + rwidth[i] -1;
		area.push_back(temp*oneDheights[i]);
	}
	return area;
}

int find_max_area(int a[][5] , int row , int column)	//use and pass vectors to avoid hard setting the size of arrays
{
	vector<int> oneDheights;
	for(int i=0;i<column;i++)
		oneDheights.push_back(a[0][i]);	//first row of binary matrix is copied

	//apply nsl and nsr on on oneDheights
	
	vector<int> templ;	
	vector<int> tempr;	
	vector<int> temp;
	templ = nsl(oneDheights); 
	tempr = nsr(oneDheights);
	int m=0;
	for(int i=1;i<row;i++)
		{
			for(int j=0;j<column;j++)
				if(a[i][j]==0)
					oneDheights[j]=0;
				else if(a[i][j]==1)
					oneDheights[j]+=a[i][j];
			templ = nsl(oneDheights);
			tempr = nsr(oneDheights);
			temp = find_area(templ,tempr,oneDheights);
			m = max(m,*max_element(temp.begin() ,temp.end()));

		}	



return m;
}

int main()
{
	int binary_matrix[][5] = {
		{0,1,1,0,1},
		{1,1,1,1,0},
		{1,1,1,0,1},
		{1,1,0,1,0}
	};

	int ans = find_max_area(binary_matrix , 5 , 5);
	cout<<ans;
}
