#include <iostream>
#include <iomanip>
#include <list>
#include <algorithm>
#include "Graph.h"
#include "BFS_Dijkstra.h"
using namespace std;
void BreadthFirstSearch::initialize()
{
	Vertex* pVrtx = getGraph().getpVrtxArray();
	VrtxList vrtxLst;
	graph.vertices(vrtxLst);
	int num_vertices = graph.getNumVertices();
	for (int vID = 0; vID < num_vertices; vID++)
		pVrtx[vID].setVrtxStatus(UN_VISITED);
	EdgeList edges;
	graph.edges(edges);
	for (EdgeItor pe = edges.begin(); pe != edges.end(); ++pe)
		pe->setEdgeStatus(EDGE_UN_VISITED);
}

void BreadthFirstSearch::initDistMtrx()
{
	double** ppDistMtrx;
	double* pLeaseCostMtrx;
	int num_nodes;
	Vertex* pVrtxArray;
	EdgeList* pAdjLstArray;
	int curVID, vID;
	num_nodes = getNumVertices();
	pVrtxArray = graph.getpVrtxArray();
	pAdjLstArray = graph.getpAdjLstArray();
	ppDistMtrx = getppDistMtrx();
	for (int i = 0; i < num_nodes; i++)
	{
		curVID = pVrtxArray[i].getID();
		EdgeItor pe = pAdjLstArray[curVID].begin();
		while (pe != pAdjLstArray[curVID].end())
		{
			vID = (*(*pe).getpVrtx_2()).getID();
			ppDistMtrx[curVID][vID] = (*pe).getDistance();
			pe++;
		}
		ppDistMtrx[curVID][curVID] = 0.0;
	}
}

void BreadthFirstSearch::fprintDistMtrx(ostream& fout)
{
	double** ppDistMtrx;
	Vertex* pVrtxArray;
	int num_nodes;
	double dist;
	int vID;
	string vName;
	pVrtxArray = graph.getpVrtxArray();
	num_nodes = getNumVertices();
	ppDistMtrx = getppDistMtrx();
	fout << "\nDistance Matrix of Graph (" << graph.getName() << ") :" << endl;
	fout << " |";
	for (int i = 0; i < num_nodes; i++) {
		vName = pVrtxArray[i].getName();
		fout << setw(5) << vName;
	} fout << endl;
	fout << "-------+";
	for (int i = 0; i < num_nodes; i++) {
		fout << "-----";
	} fout << endl;
	for (int i = 0; i < num_nodes; i++) {
		vName = pVrtxArray[i].getName();
		fout << setw(5) << vName << " |";
		for (int j = 0; j < num_nodes; j++) {
			dist = ppDistMtrx[i][j];
			if (dist == PLUS_INF)
				fout << " +oo";
			else
				fout << setw(5) << dist;
		} fout << endl;
	} fout << endl;
}

void test_BreadthFirstSearch(Graph* pG)
{
	cout << "\n*********************************************" << endl;
	cout << "Testing bfsGraph..." << endl;
	BreadthFirstSearch bfsGraph(*pG);
	bfsGraph.fprintDistMtrx(cout);
	string start_nm, end_nm;
	Vertex* pStart, * pEnd;
	Graph::VrtxList path;
	while (1)
	{
		cout << "Input start and end of path to search shortest path (. . to quit) : ";
		cin >> start_nm;
		if (start_nm == ".")
			exit(1);
		cin >> end_nm;
		pStart = pG->getVertex(start_nm);
		pEnd = pG->getVertex(end_nm);
		if (pStart == NULL || pEnd == NULL)
		{
			cout << "Error in start or end vertex name !!" << endl;
			return;
		}
		path.clear();
		cout << "\nFinding shortest paths (using BFS) from " << pStart->getName() << " to " << pEnd->getName() << " : " << endl;
		bfsGraph.DijkstraShortestPath(cout, *pStart, *pEnd, path);
		cout << "Path found by BFS (shortest) from " << pStart->getName() << " to " << pEnd->getName() << " : ";
		for (VrtxItor vItor = path.begin(); vItor != path.end(); ++vItor)
			cout << *vItor << " ";
		cout << endl;
		bfsGraph.DijkstraShortestPath(cout, *pEnd, *pStart, path);
		cout << "Path found by BFS (shortest) from " << pEnd->getName() << " to " << pStart->getName() << " : ";
		for (VrtxItor vItor = path.begin(); vItor != path.end(); ++vItor)
			cout << *vItor << " ";
		cout << endl;
	}
}

void BreadthFirstSearch::DijkstraShortestPath(ostream& fout, Vertex& start, Vertex& target, VrtxList& path)
{
	double** ppDistMtrx;
	double* pLeastCost, minCost;
	int num_nodes, num_selected, minID;
	BFS_PROCESS_STATUS* pBFS_Process_Stat;
	int* pPrev;
	Vertex* pVrtxArray;
	Vertex vrtx, * pPrevVrtx, v;
	Edge e;
	int start_vID, target_vID, curVID, vID;
	EdgeList* pAdjLstArray;
	pVrtxArray = graph.getpVrtxArray();
	pAdjLstArray = graph.getpAdjLstArray();
	start_vID = start.getID();
	target_vID = target.getID();
	num_nodes = getNumVertices();
	ppDistMtrx = getppDistMtrx();
	pLeastCost = new double[num_nodes];
	pPrev = new int[num_nodes];
	pBFS_Process_Stat = new BFS_PROCESS_STATUS[num_nodes];
	for (int i = 0; i < num_nodes; i++)
	{
		pLeastCost[i] = ppDistMtrx[start_vID][i];
		pPrev[i] = start_vID;
		pBFS_Process_Stat[i] = NOT_SELECTED;
	}
	pBFS_Process_Stat[start_vID] = SELECTED;
	num_selected = 1;
	path.clear();
	int round = 0;
	int cost;
	string vName;
	fout << "Dijkstra::Least Cost from Vertex (" << start.getName() << ") at each round : " << endl;
	fout << " |";
	for (int i = 0; i < num_nodes; i++)
	{
		vName = pVrtxArray[i].getName();
		fout << setw(5) << vName;
	} fout << endl;
	fout << "-----------+";
	for (int i = 0; i < num_nodes; i++)
	{
		fout << setw(5) << "-----";
	} fout << endl;
	while (num_selected < num_nodes)
	{
		round++;
		fout << "round [" << setw(2) << round << "] |";
		minID = -1;
		minCost = PLUS_INF;
		for (int i = 0; i < num_nodes; i++) // find a node with LeastCost
		{
			if ((pLeastCost[i] < minCost) && (pBFS_Process_Stat[i] != SELECTED))
			{
				minID = i;
				minCost = pLeastCost[i];
			}
		}
		if (minID == -1)
		{
			fout << "Error in Dijkstra() -- found not connected vertex !!" << endl;
			break;
		}
		else
		{
			pBFS_Process_Stat[minID] = SELECTED;
			num_selected++;
			if (minID == target_vID)
			{
				fout << endl << "reached to the target node (" << pVrtxArray[minID].getName() << ") at Least Cost = " << minCost << endl;
				vID = minID;
				do {
					vrtx = pVrtxArray[vID];
					path.push_front(vrtx);
					vID = pPrev[vID];
				} while (vID != start_vID);
				vrtx = pVrtxArray[vID];
				path.push_front(vrtx); // start node
				break;
			}
		}
		for (int i = 0; i < num_nodes; i++)
		{
			if ((pBFS_Process_Stat[i] != SELECTED) &&
				(pLeastCost[i] > (pLeastCost[minID] + ppDistMtrx[minID][i])))
			{
				pPrev[i] = minID;
				pLeastCost[i] = pLeastCost[minID] + ppDistMtrx[minID][i];
			}
		}
		// print out the pLeastCost[] for debugging
		for (int i = 0; i < num_nodes; i++)
		{
			cost = pLeastCost[i];
			if (cost == PLUS_INF)
				fout << " +oo";
			else
				fout << setw(5) << pLeastCost[i];
		} fout << " ==> selected vertex :" << pVrtxArray[minID] << endl;
	}
}