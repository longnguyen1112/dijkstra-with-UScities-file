#include <string>

struct CityNode
{
	std::string name;
	CityNode* nextCity = NULL;
	struct RoadNode* connection = NULL;
};

struct RoadNode
{
	int distance = 0;
	int minute = 0;
	struct CityNode* destintion = NULL;
	RoadNode* nextRoad = NULL;
};

struct DijkstraNode
{
	int metric = INT_MAX;
	int time = INT_MAX;
	std::string path;
	bool include = false;
	struct CityNode* cityPtr = NULL;
};

