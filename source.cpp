#include <iostream>
#include <queue>
#include <string>
#include <array>
#include <list>
using namespace std;




int main() {
	//Variables
	int x;
	int y;
	cin >> x;
	cin >> y;
	string addin;
	vector<vector<char>>maze;
	vector<int> start;
	vector<int> end;
	getline(cin >> ws, addin);
	vector<vector<bool>> visited;
	//Read in maze
	for (int rows = 0; rows < x; ++rows) {
		vector<char> in;
		for (int cols = 0; cols < y; ++cols) {

		if (addin[cols] == 'S') {
			start.push_back(rows);
			start.push_back(cols);
			}
		if (addin[cols] == 'G') {
			end.push_back(rows);
			end.push_back(cols);
		}

			in.push_back(addin[cols]);
		}
		maze.push_back(in);
		if (rows < x - 1) {
			getline(cin >>ws, addin);
		}
	}

	for (int k = 0; k < x; ++k) {
		vector<bool> rowb;
		for (int p = 0; p < y; ++p) {
			if (k == start[0] && p == start[1]) {
				rowb.push_back(true);
			}
			else {
				rowb.push_back(false);
			}
		}
		visited.push_back(rowb);
	}

	//Solve maze
	int counter = 0;
	vector<vector<int>>counterv(x,vector<int>(y,0));

	vector<vector<pair<int, int>>>parent(x, vector<pair<int, int>>(y, {-2,-2}));

	//Row and Col queue
	queue<int> r;
	queue<int> c;

	//Push starting point to queue
	r.push(start[0]);
	c.push(start[1]);

	//Initialise current row and current col holders
	int cr = 0;
	int cc = 0;
	
	//Initialise next row and next col holders
	int nr, nc;

	//Moving north, east, south, west(coordinate system)
	int dr[4] = { +1,0,-1,0 };
	int dc[4] = { 0,-1,0,+1 };
	
	//Bool for if maze is complete or not
	bool complete = false;


	//Adding to queue
	while (c.size() >= 1 && !complete) {

		//current is front of queue
		cr = r.front();
		cc = c.front();

		//dequeue
		r.pop();
		c.pop();


		
		//If Goal is not visited
		if (maze[cr][cc] == 'G') {
			complete = true;
		}

		//Find next blocks: down, left, up , right
		for (int i = 0; i < 4; ++i) {
			nr = cr + dr[i];
			nc = cc + dc[i];

			//Is it a valid move checks

			//#1 Out of bounds check, smaller
			if (nr < 0 || nc < 0) {
				continue;
			}
			//#2 Out of bounds check, larger
			if (nr >= x || nc >= y) {
				continue;
			}
			//#3 Already visited check, if it is not 0 it has been visited
			if (counterv[nr][nc] != 0) {
				continue;
			}
			//#4 Is it accesable check, if there is and x it is not visitable
			if (maze[nr][nc] == 'x') {
				continue;
			}

			
			
			counterv[nr][nc] = counterv[cr][cc]+1;
			parent[nr][nc] = {cr,cc};
			r.push(nr);
			c.push(nc);
		}
		//end of finding next blocks
	}

	//Just make start zero and start pair the rc of start
	counterv[start[0]][start[1]] = 0;
	pair<int, int>start_pair = { start[0],start[1] };
	parent[start[0]][start[1]] = start_pair;

	list<pair<int, int>>out_list;

	

	//If queue is empty AND goal has not been visited
	if ((r.size() == 0 || c.size()==0) && !complete)
	{
		cout << "No Path" << endl;
		
	}
	else {

		cr = parent[end[0]][end[1]].first;
		cc = parent[end[0]][end[1]].second;
		pair<int, int> rc;
		int crph = 0;

		bool is_start = false;

		//while the current is not start
		while (!is_start) {
			//Add current to front of output
			if (cr == start[0] && cc == start[1]) {
				is_start = true;
			}

			rc.first = cr;
			rc.second = cc;
			out_list.push_front(rc);

			//Make current the parent
			crph = parent[cr][cc].first;
			cc = parent[cr][cc].second;
			cr = crph;
		}
		out_list.pop_front();





		//Output maze
		int dispr;
		int dispc;

		while (out_list.size() > 0) {
			dispr = out_list.front().first;
			dispc = out_list.front().second;
			maze[dispr][dispc] = '*';
			out_list.pop_front();

		}


		for (int rows = 0; rows < x; ++rows) {
			for (int cols = 0; cols < y; ++cols) {
				cout << maze[rows][cols];
			}
			cout << endl;
		}

	}
	return 0;
}