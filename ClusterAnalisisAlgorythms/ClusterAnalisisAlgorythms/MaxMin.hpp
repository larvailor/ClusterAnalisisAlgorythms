#pragma once

#include <iostream>
#include <vector>
#include <mutex>

struct Point
{
	unsigned short x;
	unsigned short y;
};

struct Item
{
	Point pos;

	Item(unsigned short x, unsigned short y)
	{
		pos.x = x;
		pos.y = y;
	}
};

struct Cluster
{
	Point kernel;
	std::vector<Item*> items;

	Cluster(Point pos) : kernel(pos) { }
};

class MaxMin
{
private:
	/////////////////////////////////////////////////
	// 
	//		VARIABLES
	//
	/////////////////////////////////////////////////

	unsigned m_nOfItems;
	unsigned short m_areaWidth;
	unsigned short m_areaHeight;

	std::vector<Item> m_allItems;
	std::vector<Cluster> m_clusters;
	std::vector<Cluster> m_clustersCopyForDraw;

	std::mutex m_mutex;
	bool m_bSolved;
	double m_averageDistance;

	/////////////////////////////////////////////////
	// 
	//		METHODS
	//
	/////////////////////////////////////////////////

	//-----------------------------------------------
	//		Algorythm
	//

	void randomizeItems();
	void randomizeFirstCluster();
	void createCluster(Point& kernel);
	void recalculateAverageDistance();
	Item* findTheFartestItem(const Cluster* const cluster);
	void recalculateClusters();
	double calculateEuclidDistance(const Point& point, const Point& kernel);

public:
	/////////////////////////////////////////////////
	// 
	//		METHODS
	//
	/////////////////////////////////////////////////

	//-----------------------------------------------
	//		Constructors
	//

	MaxMin(unsigned nOfItems, unsigned short areaWidth, unsigned short areaHeight);

	//-----------------------------------------------
	//		Accessors
	//

	// Getters
	std::vector<Cluster> getAllClusters();

	//-----------------------------------------------
	//		Algorythm
	//

	void solve();
};
