#include <bits/stdc++.h>
using namespace std;
#define cyt_max 90
#define cell_max 25
#define len_max 10
struct edge
{
	int cyt,cell;
	edge() {}
	edge(int icyt,int icell)
	{
		cyt=icyt;
		cell=icell;
	}
};
map<string,string> UtoHTML;
map<pair<string,string>,float> baseline;
map<string,int> cyts,cells;
vector<string> cyt_list,cell_list;
vector<vector<string> > edges,reduced_graph;
vector<edge> v[cyt_max];
int pos[cyt_max];
bool vis[cyt_max][cyt_max][len_max][cell_max];
vector<int> top;
/*void dfs(int node)
{
	cout << cyt_list[node] << endl;
	if (vis[node]==1)
	{
		cout << "a7a" << endl;
		for (int i=0;i<cyt_max;i++)
		{
			if (vis[i]==1)
			cout << cyt_list[i] << endl;
		}
		exit(0);
		return;
	}
	vis[node]=1;
	for (auto u:v[node])
	{
		if (vis[u]!=2)
		dfs(u);
	}
	vis[node]=2;
}*/
void dfs(int st,int node,int len,int c)
{
	if (len>=len_max || vis[st][node][len][c])
	return;
	vis[st][node][len][c]=1;
	for (auto u:v[node])
	dfs(st,u.cyt,len+1,u.cell);
}
/*void topo(int node)
{
	if (vis[node])
	return;
	vis[node]=1;
	for (int u:v[node])
	topo(u);
	top.push_back(node);
}
void mark(int node)
{
	if (vis[node])
	return;
	vis[node]=1;
	for (int u:v[node])
	mark(u);
}*/
string html(string s)
{
	int pos=s.find('<');
	if (pos==-1)
	return s;
	if (s[0]=='<')
	return UtoHTML[s.substr(1,6)]+html(s.substr(8,(int)s.size()-8));
	return s.substr(0,pos)+html(s.substr(pos,(int)s.size()-pos));
}
void make_dot(vector<vector<string> > v,string filename)
{
	freopen(filename.c_str(),"w",stdout);
	cout << "digraph cytokine_cascade {" << endl;
	for (auto p:cyts)
	cout << p.second << ' ' << "[label=\""+html(p.first)+"\"]" << endl;
	map<pair<string,string>,vector<string> > merger;
	for (auto e:v)
	merger[{e[0],e[2]}].push_back(e[1]);
	for (auto e:v)
	{
		string s="";
		for (auto c:merger[{e[0],e[2]}])
		s+=html(c)+",";
		if (s.empty())
		continue;
		s.pop_back();
		cout << cyts[e[0]] << " -> " << cyts[e[2]] << " [label=\""+s+"\"]" << endl;
		merger[{e[0],e[2]}].clear();
	}
	cout << "}";
}
/*bool cmp(int a,int b)
{
	return pos[a]>pos[b];
}*/
int main()
{
	freopen("cytokine_graph_stat.txt","r",stdin);
	string line;
	while (getline(cin,line))
	{
		stringstream ss(line);
		vector<string> e;
		while (ss.good())
		{
			string substr;
			getline(ss,substr,',');
			e.push_back(substr);
		}
		cyts[e[0]];
		cells[e[1]];
		cyts[e[2]];
		edges.push_back(e);
	}
	int cnt=0,cellcnt=0;
	for (auto &p:cyts)
	{
		p.second=cnt++;
		cyt_list.push_back(p.first);
	}
	for (auto &p:cells)
	{
		p.second=cellcnt++;
		cell_list.push_back(p.first);
	}
	for (auto e:edges)
	{
		if (e[0]!=e[2])
		v[cyts[e[0]]].push_back(edge(cyts[e[2]],cells[e[1]]));
	}
	/*for (int i=0;i<cnt;i++)
	{
		memset(vis,0,sizeof(vis));
		dfs(i);
	}*/
	/*for (int i=0;i<cnt;i++)
	topo(i);
	for (int i=0;i<cnt;i++)
	pos[top[i]]=i;
	vector<vector<int> > reduced_graph;
	for (int node:top)
	{
		memset(vis,0,sizeof(vis));
		vector<int> out;
		for (int u:v[node])
		out.push_back(u);
		sort(out.begin(),out.end(),cmp);
		for (int u:out)
		{
			if (!vis[u])
			{
				reduced_graph.push_back({node,u});
				mark(u);
			}
		}
	}*/
	for (int i=0;i<cnt;i++)
	dfs(i,i,0,cellcnt);
	for (auto e:edges)
	{
		if (!vis[cyts[e[0]]][cyts[e[2]]][2][cells[e[1]]] && !vis[cyts[e[0]]][cyts[e[2]]][3][cells[e[1]]])
		reduced_graph.push_back(e);
		else
		cout << e[0] << ' ' << e[2] << endl;
	}
	/*for (int i=0;i<cnt;i++)
	{
		for (int j=0;j<cellcnt;j++)
		{
			if (vis[i][i][3][j])
			cout << cyt_list[i] << endl;
		}
	}*/
	freopen("reduced_graph.txt","w",stdout);
	for (auto e:reduced_graph)
	cout << e[0] << ',' << e[2] << ',' << e[1] << endl;
	UtoHTML["U+03B1"]="&alpha;";
	UtoHTML["U+03B2"]="&beta;";
	UtoHTML["U+03B3"]="&gamma;";
	UtoHTML["U+03BA"]="&kappa;";
	UtoHTML["U+03B5"]="&epsi;";
	make_dot(reduced_graph,"reduced_graph.dot");
}
