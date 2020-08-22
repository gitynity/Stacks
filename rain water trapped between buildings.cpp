#include <bits/stdc++.h>
using namespace std;

int rain_water_trap(vector<int> v)
{
	vector<int> leftmax;	// to store the absolute largest building on the left of the current building
	vector<int> rightmax;	// to store the absolute largest building on the right of the current building
	int mx = v[0];
	leftmax.push_back(mx);
	for (int i = 1; i < v.size(); i++)
	{
		if (v[i] > mx)
			mx = v[i];
		leftmax.push_back(mx);
	}
	mx = v[v.size() - 1];
	rightmax.push_back(mx);
	for (int i = v.size() - 2; i >= 0; i--)
	{
		if (v[i] > mx)
			mx = v[i];
		rightmax.push_back(mx);
	}
	vector<int> bottleneckheight;	//the water level above the current building will be equal to the height of the smaller building among leftmax and rightmax
	for (int i = 0; i < v.size(); i++)
	{
		bottleneckheight.push_back(min(leftmax[i], rightmax[i]));
	}
	vector<int> waterabovebuilding;
	for (int i = 0; i < v.size(); i++)
	{
		waterabovebuilding.push_back(bottleneckheight[i] - v[i]);
	}

	int a = accumulate(waterabovebuilding.begin(), waterabovebuilding.end(), 0);
	return a;
}

int main()
{
	vector<int> building_height = {3, 0, 0, 2, 4};
	int ans = rain_water_trap(building_height);

	cout << "Total water trapped between buildings is: " << ans;
	return 0;
}
