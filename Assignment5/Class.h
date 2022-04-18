#include "Struct.h"
#include "AA.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

class Dijkstra
{
private :
	CityNode* graph = NULL;
	CityNode* Trav = NULL;
	bool FindCity(std::string);
	void clearNetwork();
public:
	Dijkstra(std::string);
	Dijkstra();
	~Dijkstra();
	//bool FindShortestWay(std::string, std::string);
	bool FindShortestTime(std::string, std::string);
	bool FindShortestDistance(std::string, std::string);
	void AddCity(std::string);
	void AddConnection(std::string, std::string, int, int);
	void LoadFromFile(std::string);
};

Dijkstra::Dijkstra()
{
	graph = NULL;
}

Dijkstra::Dijkstra(std::string filename)
{
	LoadFromFile(filename);
}

void Dijkstra::LoadFromFile(std::string filename)
{
	std::ifstream inFile;
	inFile.open(filename);
	if (inFile.good())
	{
		do
		{
			std::string getCity;
			std::getline(inFile, getCity);
			if (getCity != "*")
			{
				AddCity(getCity);
			}
			else
			{
				break;
			}
		} while (true);
		do
		{
			std::string src, dst, readmiles, readmin;
			std::getline(inFile, src, '\t');
			if (src == "*")
			{
				break;
			}
			else
			{
				std::getline(inFile, dst, '\t');
				std::getline(inFile, readmiles, '\t');
				std::getline(inFile, readmin, '\n');
				AddConnection(src, dst, stoi(readmiles), stoi(readmin));
			}
		} while (true);
		inFile.close();
	}
}

Dijkstra::~Dijkstra()
{
	clearNetwork();
}

void Dijkstra::clearNetwork()
{
	CityNode* tmp = graph;
	RoadNode* tmpRoad = NULL;
	while (tmp)
	{
		tmpRoad = tmp->connection;
		while (tmpRoad)
		{
			RoadNode* delRoad = tmpRoad;
			tmpRoad = tmpRoad->nextRoad;
			delete delRoad;
		}
		CityNode* delCity = tmp;
		tmp = tmp->nextCity;
		delete delCity;
	}
	graph = NULL;
}

void Dijkstra :: AddCity(std::string name)
{
	CityNode* temp = new CityNode;
	temp->name = name;
	temp->nextCity = graph;
	graph = temp;
}

void Dijkstra::AddConnection(std::string src, std::string dst, int miles, int min)
{
	if (!FindCity(src))
	{
		std::cout << "There is no such city. " << std::endl;
		exit(0);
	}
	CityNode* srcPtr = Trav;
	if (!FindCity(dst))
	{
		std::cout << "There is no such city. " << std::endl;
		exit(0);
	}
	CityNode* dstPtr = Trav;
	RoadNode* temp = new RoadNode;
	temp->distance = miles;
	temp->minute = min;
	temp->nextRoad = srcPtr->connection;
	temp->destintion = dstPtr;
	srcPtr->connection = temp;
	

	RoadNode* temp1 = new RoadNode;
	temp1->distance = miles;
	temp1->minute = min;
	temp1->nextRoad = dstPtr->connection;
	temp1->destintion = srcPtr;
	dstPtr->connection = temp1;
	
}

bool Dijkstra::FindCity(std::string name)
{
	Trav = graph;
	while (name != Trav->name)
	{
		Trav = Trav->nextCity;
	}
	if (name == Trav->name)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Dijkstra::FindShortestDistance(std::string src, std::string dst)
{
	AArray <DijkstraNode> CalcTable;
	DijkstraNode* srcNode=NULL;
	DijkstraNode* dstNode=NULL;
	CityNode* temp = graph;
	while (temp)
	{
		DijkstraNode tempNode;
		tempNode.cityPtr = temp;
		CalcTable[temp->name] = tempNode;
		if (temp->name == src)
		{
			srcNode = &CalcTable[temp->name];
			CalcTable[temp->name].include = true;
			CalcTable[temp->name].metric = 0;
			CalcTable[temp->name].time = 0;
		}
		if (temp->name == dst)
		{
			dstNode = &CalcTable[temp->name];
		}
		temp = temp->nextCity;	
	}
	if (!srcNode || !dstNode)
	{
		return false;
	}
	DijkstraNode* curNode = srcNode;
	while (curNode->cityPtr != dstNode->cityPtr)
	{
		RoadNode* tempRoad = curNode->cityPtr->connection;
		while (tempRoad)
		{
			if (curNode->metric + tempRoad->distance < CalcTable[tempRoad->destintion->name].metric)
			{
				CalcTable[tempRoad->destintion->name].metric = curNode->metric + tempRoad->distance;
				CalcTable[tempRoad->destintion->name].path = curNode->cityPtr->name;
			}
			/*if (curNode->time + tempRoad->minute < CalcTable[tempRoad->destintion->name].time)
			{
				CalcTable[tempRoad->destintion->name].time = curNode->time + tempRoad->minute;
			}*/
			tempRoad = tempRoad->nextRoad;
		}

		CalcTable.first();
		int bestDistance = INT_MAX;
		//int bestTime = INT_MAX;
		std::string bestCity;
		
		do
		{
			if (CalcTable[CalcTable.keyvalue()].metric < bestDistance && !CalcTable[CalcTable.keyvalue()].include ) //update
			{
				bestDistance = CalcTable[CalcTable.keyvalue()].metric;
				bestCity = CalcTable.keyvalue();
			}
			

		} while (CalcTable.next());
		if (bestDistance == INT_MAX)
		{
			return false; 
		}
		/*if (bestTime == INT_MAX)
		{
			return false;
		}*/
		curNode = &CalcTable[bestCity];
		curNode->include = true;
	}
	std::cout << src << " to " << dst << " is " << curNode->metric << std::endl;
	//std::cout << src << " to " << dst << " take " << dstNode->time << " minutes."<< std::endl;
	std::vector<std::string> v;
	do
	{
		v.push_back(curNode->cityPtr->name);
		curNode = &CalcTable[curNode->path];
	} while (curNode->cityPtr != srcNode->cityPtr);
	v.push_back(curNode->cityPtr->name);
	for (int i = v.size() - 1; i > 0; i--)
	{
		std::cout << v[i] << "--->>";
	}
	std::cout << v[0] << std::endl;
	return true;
}
bool Dijkstra::FindShortestTime(std::string src, std::string dst)
{
	AArray <DijkstraNode> CalcTable;
	DijkstraNode* srcNode = NULL;
	DijkstraNode* dstNode = NULL;
	CityNode* temp = graph;
	while (temp)
	{
		DijkstraNode tempNode;
		tempNode.cityPtr = temp;
		CalcTable[temp->name] = tempNode;
		if (temp->name == src)
		{
			srcNode = &CalcTable[temp->name];
			CalcTable[temp->name].include = true;
			CalcTable[temp->name].metric = 0;
			CalcTable[temp->name].time = 0;
		}
		if (temp->name == dst)
		{
			dstNode = &CalcTable[temp->name];
		}
		temp = temp->nextCity;
	}
	if (!srcNode || !dstNode)
	{
		return false;
	}
	DijkstraNode* curNode = srcNode;
	while (curNode->cityPtr != dstNode->cityPtr)
	{
		RoadNode* tempRoad = curNode->cityPtr->connection;
		while (tempRoad)
		{
			/*if (curNode->metric + tempRoad->distance < CalcTable[tempRoad->destintion->name].metric)
			{
				CalcTable[tempRoad->destintion->name].metric = curNode->metric + tempRoad->distance;
				CalcTable[tempRoad->destintion->name].path = curNode->cityPtr->name;
			}*/
			if (curNode->time + tempRoad->minute < CalcTable[tempRoad->destintion->name].time)
			{
				CalcTable[tempRoad->destintion->name].time = curNode->time + tempRoad->minute;
				CalcTable[tempRoad->destintion->name].path = curNode->cityPtr->name;
			}
			tempRoad = tempRoad->nextRoad;
		}

		CalcTable.first();
		//int bestDistance = INT_MAX;
		int bestTime = INT_MAX;
		std::string bestCity;

		do
		{
			if (CalcTable[CalcTable.keyvalue()].time < bestTime && !CalcTable[CalcTable.keyvalue()].include) //update
			{
				bestTime = CalcTable[CalcTable.keyvalue()].time;
				bestCity = CalcTable.keyvalue();
			}


		} while (CalcTable.next());
		/*if (bestDistance == INT_MAX)
		{
			return false;
		}*/
		if (bestTime == INT_MAX)
		{
			return false;
		}
		curNode = &CalcTable[bestCity];
		curNode->include = true;
	}
	std::cout << src << " to " << dst << " takes " << curNode->time<< " minutes." << std::endl;
	//std::cout << src << " to " << dst << " take " << dstNode->time << " minutes."<< std::endl;
	std::vector<std::string> v;
	do
	{
		v.push_back(curNode->cityPtr->name);
		curNode = &CalcTable[curNode->path];
	} while (curNode->cityPtr != srcNode->cityPtr);
	v.push_back(curNode->cityPtr->name);
	for (int i = v.size() - 1; i > 0; i--)
	{
		std::cout << v[i] << "--->>";
	}
	std::cout << v[0] << std::endl;
	return true;
}


