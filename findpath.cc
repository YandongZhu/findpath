#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

// record the path structure
struct path
{
	bool type;
	int terminal;
	path(bool type,int terminal){
	this->type = type;
	this->terminal = terminal;
	}
};

// total # of city
int city = 0;
// total amount of money
int money = 0;
// total amount of the path
int total = 0;
// the start city
int startCity = 0;
// the end city
int endCity = 0;
// record the current max distance that can reach
int maxDistance = 0;
// record if we already find the shortest path or not
bool findTerminal = false;
// record the current cheapest money
int cheapest = 0;
// create an adjcent list of all path
vector <struct path> arr [100000];
// record shortest path to corresponding required money
std::vector<int> totalPath [11];
// record the current path
std::vector<int> curPath;

void findPath(int curCity, int curMoney, int curDistance){
	// push the current city into the path
	curPath.push_back(curCity);
	// base case
	// if we dont have enough money or the current distance 
	// exceed the max distance, then return
	if (curMoney > cheapest || curDistance > maxDistance)
	{
		// pop the last path
		curPath.pop_back();
		return;
	}

	// if we already find the shortest path
	else if (curCity == endCity)
	{
		// if the current money path has not been find
		if (totalPath[curMoney].size() == 0)
		{
			for (int i = 0; i < curPath.size(); ++i)
			{
				totalPath[curMoney].push_back(curPath[i]);
			}
			cheapest = curMoney;
			findTerminal = true;
		}
		curPath.pop_back();
		return;
	}

	else {
		// recursively find the path less than the max distance
		for (std::vector<struct path>::iterator it = arr[curCity].begin() ; it != arr[curCity].end(); ++it)
		{
			if (it->type)
				curMoney++;
			findPath(it->terminal, curMoney, curDistance++);
			if (it->type)
				curMoney--;
			curDistance--;
		}
		curPath.pop_back();	
	}
}


int main(int argc, char const *argv[])
{
	// cin the basic infomation
	cin >> city >> money >> total;
	cheapest = money;

	// cin the amount of path 
	for (int i = 0; i < total; ++i)
	{
		int start = 0;
		int end = 0;
		bool type = false;
		cin >> start >> end >> type;
		struct path newpath = path(type, end-1);
		arr[start-1].push_back(newpath);
	}

	// cin and modify the start city and end city
	cin >> startCity >> endCity;
	startCity--;
	endCity--;

	// check if we find the path or not, 
	// if not, then increase the max distance
	for (int i = 0; i < city; ++i)
	{
			findPath(startCity, 0, 0);
			maxDistance++;
			if (findTerminal) break;
	}

	// if we not find
	if (!findTerminal)
		cout << -1 << endl;
	// else cout the time and path
	else
	{
		cout << totalPath[cheapest].size() - 1 << endl;
		for (int j = 0; j < totalPath[cheapest].size(); ++j)
		{
			cout << totalPath[cheapest][j] + 1 << " ";
		}
		cout << endl;
	}
	return 0;
}