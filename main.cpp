#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include<fstream>
#include<sstream>

#include <stdio.h>
#include <iomanip>
#include <math.h>
#include <map>
#include <algorithm>
#include <string>
#include <cstring>
#include <string.h>
#include <iterator>
#include <bitset>
#include <queue>
#include <time.h>
#define yalam4mohm 	std::ios::sync_with_stdio(false);
using namespace std;
#define ll long long




class vertex {
private:
	int Node_Id; // o(1) T(1)
	double X_axis, Y_axis; // o(1) T(1)

public:
	vertex()
	{
		//NumberOfNode = 0; // o(1) T(1)
		Node_Id = 0; // o(1) T(1)
		X_axis = 0; Y_axis = 0; // o(1) T(1)
	}
	vertex(int id, double x, double y) // o(1) T(1)
	{

		Node_Id = id; // o(1) T(1)
		X_axis = x; // o(1) T(1)
		Y_axis = y; // o(1) T(1)
	}

	double get_x() { return X_axis; } // o(1) T(1)
	double get_y() { return Y_axis; } // o(1) T(1)
	int get_id() { return Node_Id; } // o(1) T(1)

};



class Edge
{

public:
	int Node1;// o(1) T(1)
	int Node2; // o(1) T(1)
	double Length, Speed, Time; // o(1) T(1)

	Edge() // o(1) T(1)
	{
		Node1 = 0; // o(1) T(1)
		Node2 = 0; // o(1) T(1)
		Length = 0; Speed = 0; Time = Length / Speed; // o(1) T(1)
	}

	Edge(int n1, int n2, double l, double s) // o(1) T(1)
	{
		Node1 = n1; // o(1) T(1)
		Node2 = n2; // o(1) T(1)
		Length = l; // o(1) T(1)
		Speed = s;// o(1) T(1)
		Time = (l / s) * 60; // o(1) T(1)
	}
	double getlength() { return Length; }
	bool operator < (const Edge &e) const { return Time > e.Time; }


};

#define OO 10000000000
vector<vertex>vertexList;
vector<vector<Edge> >graph;
vector<double>cost;
vector<double>dist;
vector<int>path;
vector<string>lines;
void dijkstra(int src) {
	int n = graph.size();
	cost = vector<double>(n, 100000);
	dist = vector<double>(n, 100000);
	path.resize(n+1);

	cost[src] = 0;
	dist[src] = 0;
	priority_queue<Edge>pq;
	pq.push(Edge(-1, src, 0, 1));

	while (!pq.empty())
	{
		Edge e = pq.top();
		pq.pop();
		int to = e.Node2;
		int from = e.Node1;
		double Cdist = e.getlength();
		if (e.Time > cost[to]) continue;
		path[to] = from;
		for (int i = 0; i < graph[to].size(); i++)
		{
			Edge tmp = graph[to][i];
			if (cost[tmp.Node2] > cost[tmp.Node1] + tmp.Time)
			{
			    //path[tmp.Node2]=to;
				tmp.Length = dist[tmp.Node2] = tmp.getlength() + Cdist;
				tmp.Time = cost[tmp.Node2] = cost[tmp.Node1] + tmp.Time;
				pq.push(tmp);
			}
		}

	}
}

/*============================split function===================================*/

vector<string> split(const string& str, const string& delim)
{
	vector<string> tokens;
	size_t prev = 0, pos = 0;
	do
	{
		pos = str.find(delim, prev);
		if (pos == string::npos) pos = str.length();
		string token = str.substr(prev, pos - prev);
		if (!token.empty()) tokens.push_back(token);
		prev = pos + delim.length();
	} while (pos < str.length() && prev < str.length());
	return tokens;
}

/*==============================================================================*/




int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	 freopen("Answer.txt", "w", stdout);  // ÇáÓØÑ ÏÉ ÈíßÊÈ ßá ÇæÊÈæÊ Ý ÇáÝÇíá
	/****************************************************************************************************************************/
	int ver;
	string line;

	ifstream f;
	int index;
	float x, y;
	f.open("NAMap.txt");
	if (!f) {
		cout << "Unable to open file";
		exit(1); // terminate with error
	}
	getline(f, line);
	ver = atoi(line.c_str()); //Parse String To Int

	vertexList = vector<vertex>(ver);
	for (int i = 0; i < ver; i++) {
		getline(f, line);
		index = atoi(split(line, " ")[0].c_str());
		x = atof(split(line, " ")[1].c_str());
		y = atof(split(line, " ")[2].c_str());
		vertex v(index, x, y);
		vertexList[index] = v;
	}

	/**********************************************************************/
	int e;
	int from, to;
	double l, s;

	getline(f, line);
	e = atoi(line.c_str());
	graph = vector<vector<Edge> >(e+1);
	path = vector<int>(e);
	for (int i = 0; i < e; i++) {
		getline(f, line);
		from = atoi(split(line, " ")[0].c_str());
		to = atoi(split(line, " ")[1].c_str());
		l = atof(split(line, " ")[2].c_str());
		s = atof(split(line, " ")[3].c_str());
		Edge edg(from, to, l, s);
		graph[from].push_back(edg);
		Edge tmp(to, from, l, s);
		graph[to].push_back(tmp);
	}

	f.close();
	/****************************************************************************************************************************/


	f.open("NAQueries.txt");
	int num_query ;
	double src_x,src_y,dest_x,dest_y,R ;

	getline(f, line);
	num_query = atoi(line.c_str());

	lines = vector<string>(num_query);
	int nt = num_query-1;
	for (int i = 0; i < num_query; i++)
		getline(f, lines[i]);

	clock_t start = clock();
	for (int i = 0; i < num_query; i++)
	{
		vector<pair<int, double> > possible_start;
		vector<pair<int, double> > possible_dest;
		src_x = atof(split(lines[i], " ")[0].c_str());
		src_y = atof(split(lines[i], " ")[1].c_str());
		dest_x = atof(split(lines[i], " ")[2].c_str());
		dest_y = atof(split(lines[i], " ")[3].c_str());
		R = atof(split(lines[i], " ")[4].c_str());
		R /= 1000;

		int sz = vertexList.size();
		for (int i = 0; i < sz; i++)
		{
			double diff_x = (src_x - vertexList[i].get_x());
			diff_x *= diff_x;
			double diff_y = (src_y - vertexList[i].get_y());
			diff_y *= diff_y;
			double D = sqrt(diff_x + diff_y);

			if (D <= R)
			{
				pair<int, double> s = pair<int, double>(vertexList[i].get_id(), D);
				possible_start.push_back(s);
			}
			diff_x = (dest_x - vertexList[i].get_x());
			diff_x *= diff_x;
			diff_y = (dest_y - vertexList[i].get_y());
			diff_y *= diff_y;
			D = sqrt(diff_x + diff_y);

			if (D <= R)
			{
				pair<int, double> d = pair<int, double>(vertexList[i].get_id(), D);
				possible_dest.push_back(d);
			}
		}


		//stack<int>way;
		vector<int> fpath;

		int num_possible_start = possible_start.size();
		int num_possible_end = possible_dest.size();
		const int speed_walking = 5;
		double time_walking_src;
		double time_walking_dest;
		//**********************************
		int Source;
		int Destination;
		double Total_Time = 1000000000000;
		double Total_Distance;
		double Total_road_length;
		double Total_walking_distance;
		//**********************************
		int source;
		int destination;
		double min_time = 1000000000000;
		double distance;
		double road_length;
		double walking_distance;
		//**********************************
		for (int i = 0; i < num_possible_start; i++)
		{

			time_walking_src = (possible_start[i].second / speed_walking) * 60;
			dijkstra(possible_start[i].first);
			for (int j = 0; j < num_possible_end; j++)
			{

				time_walking_dest = (possible_dest[j].second / speed_walking) * 60;
				double t_time = cost[possible_dest[j].first] + time_walking_src + time_walking_dest;
				double t_dist = dist[possible_dest[j].first];
				if (t_time < min_time)
				{
					min_time = t_time;
					distance = t_dist + possible_start[i].second + possible_dest[j].second;
					road_length = t_dist;
					walking_distance = possible_start[i].second + possible_dest[j].second;
					destination = possible_dest[j].first;
					fpath = path;
				}


			}

			if (min_time < Total_Time)
			{
				Total_Time = min_time;
				Total_Distance = distance;
				Total_road_length = road_length;
				Total_walking_distance = walking_distance;
				Destination = destination;
				source = possible_start[i].first;
			}

		}
		stack<int>way;

	    way.push(Destination);
	    while (true)
        {
		  if (way.top() == source) break; // way.top == src break;
	        	way.push(fpath[way.top()]);
	    }

	    while (!way.empty())
	   {
	       if (way.top() != Destination)
                cout << way.top() << " ";
           else
                cout << way.top() << endl;
	    	way.pop();
       }
		/*int c = Destination;
		while (c!=-1)
		{
            way.push(c) ;
			c=path[c];
		}
		cout<<way.top();
		way.pop();
		while (!way.empty())
		{
            cout <<" "<< way.top();
			way.pop();
		}
		cout << endl;*/

		cout << fixed<<setprecision(2)<<Total_Time << " mins" << endl <<fixed<<setprecision(2)<< Total_Distance << " km" << endl <<fixed<<setprecision(2)<< Total_walking_distance << " km" << endl <<fixed<<setprecision(2)<< Total_road_length << " km" << endl << endl;

	}

	cout << ((clock() - start) / CLOCKS_PER_SEC)/1000 <<"sec"<< endl;
	cout << endl;


	//system("pause");
	return 0;
}
