#include<iostream>
#include<vector>
#include<string>
using namespace std;

void reverse(vector<char> &v, int left, int right)
{
	while (left <= right)
	{
		swap(v[left], v[right]);
		left++;
		right--;
	}
}
int main()
{
	char ch;
	vector<char> v;
	string s;
	getline(cin, s);
	//cout << s.c_str();
	for (int i = 0; i < s.size(); ++i)
	{
		v.push_back(s[i]);
	}
	reverse(v, 0, v.size()-1);
	int left = 0;
	for (int i = 0; i < v.size(); ++i)
	{
	
		int right = 0;
		if (v[i] == ' ')
		{
			right = i;
			reverse(v, left, right-1);
			left = i + 1;
		}
	}
	reverse(v, left, v.size() - 1);
	for (int i = 0; i < v.size(); ++i)
	{
		cout << v[i];
	}

	return 0;
}
