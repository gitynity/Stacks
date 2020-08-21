#include <bits/stdc++.h>
using namespace std;

vector<int> nsl(int a[], int l)
{
	stack<int> s;
	s.push(-1);
	s.push(0);
	vector<int> left;
	left.push_back(-1);	//nothing is in the left array of the leftmost element

	for (int i = 1; i < l; i++)
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

vector<int> nsr(int a[], int l)
{
	stack<int> s;
	s.push(l);	   //7	nothing is in the right array of the rightmost element
	s.push(l - 1); //6
	vector<int> right;
	right.push_back(7);

	for (int i = l - 2; i >= 0; i--)
		while (true)
		{
			if (s.top() != 7 && a[s.top()] >= a[i])
			{
				s.pop();
			}
			else if (s.top() != 7 && a[s.top()] < a[i])
			{
				right.push_back(s.top());
				s.push(i);
				break;
			}
			else if (s.top() == 7)
			{
				right.push_back(7);
				s.push(i);
				break;
			}
		}
	reverse(right.begin(), right.end());
	return right;
}

vector<int> maxarea(int a[], int l)
{
	vector<int> leftlimit = nsl(a, l);
	vector<int> rightlimit = nsr(a, l);
	vector<int> lwidth;
	vector<int> rwidth;
	vector<int> area;
	int lw = 0;
	int rw = 0;

	for (int i = 0; i < l; i++)
	{
		if (leftlimit[i] < 0)
			lw = i + 1;
		else if (leftlimit[i] >= 0)
		{
			lw = i - leftlimit[i];
		}

		lwidth.push_back(lw);
	}

	for (int i = 0; i < l; i++)
	{
		if (rightlimit[i] >= l)
		{
			rw = l - i;
		}
		else if (rightlimit[i] < l)
		{
			rw = rightlimit[i] - i;
		}
		rwidth.push_back(rw);
	}

	for (int i = 0; i < l; i++)
		cout << setw(3) << lwidth[i]<<" "; //lwftwidths of buildings

	cout << setw(3) << endl;

	for (int i = 0; i < l; i++)
		cout << setw(3) << rwidth[i]<<" "; //rightwidths of buildings
	cout << setw(3) << endl;

	for (int i = 0; i < l; i++)
	{
		int temp = lwidth[i] + rwidth[i] - 1; //areas of buildings
		area.push_back(temp * a[i]);
	}
	return area;
}

int main()
{
	int building_heights[] = {6, 2, 5, 4, 5, 1, 7};
	vector<int> ans = maxarea(building_heights, 7);

	for (auto i : building_heights)
		cout << setw(3) << i << " ";

	cout << setw(3) << endl;

	for (int i = 0; i < 7; i++)
		cout << setw(3) << ans[i] << " ";

	cout << setw(3) << endl;

	int c = 0;

	for (auto i = 0; i < 7; i++)
	{
		if (ans[i] > c)
			c = ans[i];
	}
	cout << "\nThem maximum rectangular area possible is " << c << "square units"<<endl;

	return 0;
}
