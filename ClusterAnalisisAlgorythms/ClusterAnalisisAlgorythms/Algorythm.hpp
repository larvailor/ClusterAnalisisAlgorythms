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

class Algorythm
{
protected:
	/////////////////////////////////////////////////
	// 
	//		VARIABLES
	//
	/////////////////////////////////////////////////

	std::vector<Item> m_allItems;
	std::vector<Cluster> m_clusters;
	std::vector<Cluster> m_clustersCopyForDraw;

	std::mutex m_mutex;
	bool m_bSolved;

	/////////////////////////////////////////////////
	// 
	//		METHODS
	//
	/////////////////////////////////////////////////

	//-----------------------------------------------
	//		Algorythm
	//

	virtual void randomizeItems(unsigned& nOfItems, unsigned short& areaWidth, unsigned short& areaHeight);
	virtual void createCluster(Point& kernel);
	virtual void recalculateClusters();
	virtual double calculateEuclidDistance(const Point& point, const Point& kernel);

public:
	/////////////////////////////////////////////////
	// 
	//		METHODS
	//
	/////////////////////////////////////////////////

	//-----------------------------------------------
	//		Constructors
	//

	Algorythm(unsigned nOfItems, unsigned short areaWidth, unsigned short areaHeight);

	//-----------------------------------------------
	//		Accessors
	//

	// Getters

	virtual std::vector<Cluster> getAllClusters();

	//-----------------------------------------------
	//		Algorythm
	//

	virtual void solve() = 0;
};
