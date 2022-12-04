/** Graph.h */
#ifndef GRAPH_H
#define GRAPH_H
#include <list>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <string>
using namespace std;
#define PLUS_INF INT_MAX
enum VrtxStatus { UN_VISITED, VISITED, VRTX_NOT_FOUND };
enum EdgeStatus { DISCOVERY, BACK, CROSS, EDGE_UN_VISITED, EDGE_VISITED, EDGE_NOT_FOUND };

class Graph // Graph based on Adjacency Matrix
{
public:
	class Vertex;
	class Edge;
	typedef std::list<Graph::Vertex> VrtxList;
	typedef std::list<Graph::Edge> EdgeList;
	typedef std::list<Vertex>::iterator VrtxItor;
	typedef std::list<Edge>::iterator EdgeItor;
public:
	class Vertex // Graph::Vertex
	{
		friend ostream& operator<<(ostream& fout, Vertex v)
		{
			fout << v.getName();
			return fout;
		}
	public:
		Vertex() : name(""), ID(-1) {}
		Vertex(string n, int id) : name(n), ID(id) { }
		Vertex(int id) : ID(id) {}
		string getName() { return name; }
		void setName(string c_name) { name = c_name; }
		int getID() { return ID; }
		void setID(int id) { ID = id; }
		void setVrtxStatus(VrtxStatus vs) { vrtxStatus = vs; }
		VrtxStatus getvrtxStatus() { return vrtxStatus; }
		bool operator==(Vertex v) { return ((ID == v.getID()) && (name == v.getName())); }
		bool operator!=(Vertex v) { return ((ID != v.getID()) || (name != v.getName())); }
	private:
		string name;
		int ID;
		VrtxStatus vrtxStatus;
	}; // end class Vertex

public:
	class Edge
	{
		friend ostream& operator<<(ostream & fout, Edge & e)
		{
			fout << "Edge(" << *e.pVrtx_1 << ", " << *e.pVrtx_2 << ", " << e.distance << ")";
			return fout;
		}
	public:
		Edge() : pVrtx_1(NULL), pVrtx_2(NULL), distance(PLUS_INF) {}
		Edge(Vertex & v1, Vertex & v2, double d)
			:distance(d), pVrtx_1(&v1), pVrtx_2(&v2), edgeStatus(EDGE_UN_VISITED)
		{ }
		void endVertices(VrtxList & vrtxLst) {  }
		Vertex opposite(Vertex v) {  } 
		Vertex* getpVrtx_1() { return pVrtx_1; }
		Vertex* getpVrtx_2() { return pVrtx_2; }
		double getDistance() { return distance; }
		void setpVrtx_1(Vertex* pV) { pVrtx_1 = pV; }
		void setpVrtx_2(Vertex* pV) { pVrtx_2 = pV; }
		void setDistance(double d) { distance = d; }
		bool operator!=(Edge e) { return ((pVrtx_1 != e.getpVrtx_1()) || (pVrtx_2 != e.getpVrtx_2())); }
		bool operator==(Edge e) { return ((pVrtx_1 == e.getpVrtx_1()) && (pVrtx_2 == e.getpVrtx_2())); }
		void setEdgeStatus(EdgeStatus es) { edgeStatus = es; }
		EdgeStatus getEdgeStatus() { return edgeStatus; }
	private:
		Vertex* pVrtx_1;
		Vertex* pVrtx_2;
		double distance;
		EdgeStatus edgeStatus;
	}; // end class Edge
public:
	Graph() : name(""), pVrtxArray(NULL), pAdjLstArray(NULL) {} // default constructor
	Graph(string nm, int num_nodes) : name(nm), pVrtxArray(NULL), pAdjLstArray(NULL)
	{
		pVrtxArray = new Graph::Vertex[num_nodes];
		for (int i = 0; i < num_nodes; i++)
			pVrtxArray[i] = NULL;
		pAdjLstArray = new EdgeList[num_nodes];
		for (int i = 0; i < num_nodes; i++)
			pAdjLstArray[i].clear();
		num_vertices = 0; // num_vertices is increased at insertVertex
	}
	string getName() { return name; }
	void initGraph(string nm, int num_nodes)
	{
		name = nm;
		pVrtxArray = new Graph::Vertex[num_nodes];
		for (int i = 0; i < num_nodes; i++)
			pVrtxArray[i] = NULL;
		pAdjLstArray = new EdgeList[num_nodes];
		for (int i = 0; i < num_nodes; i++)
			pAdjLstArray[i].clear();
		num_vertices = 0; // num_vertices is increased at insertVertex
	}
	void vertices(VrtxList& vrtxLst)
	{
		vrtxLst.clear();
		for (int i = 0; i < getNumVertices(); i++)
			vrtxLst.push_back(pVrtxArray[i]);
	}
	void edges(EdgeList& edges)
	{
		EdgeItor eItor;
		Graph::Edge e;
		edges.clear();
		for (int i = 0; i < getNumVertices(); i++)
		{
			eItor = pAdjLstArray[i].begin();
			while (eItor != pAdjLstArray[i].end())
			{
				e = *eItor;
				edges.push_back(e);
				eItor++;
			}
		}
	}
	//bool isAdjacentTo(Vertex v, Vertex w);
	Vertex* insertVertex(Vertex& newV)
	{
		int vID, num_vrtx;
		string vName;
		vName = newV.getName();
		for (int i = 0; i < this->num_vertices; i++)
		{
			if (pVrtxArray[i].getName() == vName)
				return &pVrtxArray[i]; // vertex is already existing
		}
		vID = this->num_vertices;
		newV.setID(vID);
		if (pVrtxArray[vID] == NULL) {
			pVrtxArray[vID] = newV;
			this->num_vertices++;
		}
		return& pVrtxArray[vID];
	}
	Vertex* getVertex(string vName)
	{
		for (int i = 0; i < this->num_vertices; i++)
		{
			if (pVrtxArray[i].getName() == vName)
				return &pVrtxArray[i]; // vertex is already existing
		}return NULL;
	}
	void insertEdge(Edge& e)
	{
		Vertex vrtx_1, vrtx_2;
		Vertex* pVrtx;
		int vrtx_1_ID, vrtx_2_ID;
		vrtx_1 = *e.getpVrtx_1();
		vrtx_2 = *e.getpVrtx_2();
		vrtx_1_ID = vrtx_1.getID();
		vrtx_2_ID = vrtx_2.getID();
		if (pVrtxArray[vrtx_1_ID] == NULL) {
			pVrtxArray[vrtx_1_ID] = vrtx_1;
		}
		if(pVrtxArray[vrtx_2_ID] == NULL) {
			pVrtxArray[vrtx_2_ID] = vrtx_2;
		}
		e.setpVrtx_1(&pVrtxArray[vrtx_1_ID]);
		e.setpVrtx_2(&pVrtxArray[vrtx_2_ID]);
		pAdjLstArray[vrtx_1_ID].push_back(e);
	}
	//void eraseEdge(Edge e);
	//void eraseVertex(Vertex v);
	int getNumVertices() { return num_vertices; }
	void incidentEdges(Vertex v, EdgeList& edgeLst)
	{
		Graph::Edge e;
		EdgeItor eItor;
		int vID = v.getID();
		eItor = pAdjLstArray[vID].begin();
		while (eItor != pAdjLstArray[vID].end())
		{
			e = *eItor;
			edgeLst.push_back(e);
			eItor++;
		}
	}
	Vertex* getpVrtxArray() { return pVrtxArray; }
	EdgeList* getpAdjLstArray() { return pAdjLstArray; }
	void fprintGraph(ostream& fout)
	{
		int i, j;
		EdgeItor eItor;
		Graph::Edge e;
		int numOutgoingEdges;
		fout << this->getName() << " with " << this->getNumVertices() << " vertices has following adjacency lists :" << endl;
		for (i = 0; i < num_vertices; i++)
		{
			fout << " vertex (" << setw(3) << pVrtxArray[i].getName() << ") : ";
			numOutgoingEdges = pAdjLstArray[i].size();
			eItor = pAdjLstArray[i].begin();
			while (eItor != pAdjLstArray[i].end())
			{
				e = *eItor;
				fout << e << " ";
				eItor++;
			}
			fout << endl;
		}
	}
	bool isValidvID(int vid)
	{
		if ((vid >= 0) && (vid < num_vertices))
			return true;
		else
		{
			//cout << "Vertex ID (" << vid << ") is invalid for Graph (" << getName();
			//cout << ") with num_vertices (" << num_vertices << ")" << endl;
			return false;
		}
	}
private:
	string name;
	Vertex* pVrtxArray;
	EdgeList* pAdjLstArray;
	int num_vertices;
};
#endif