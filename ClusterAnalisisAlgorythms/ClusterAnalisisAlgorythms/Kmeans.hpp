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

class Kmeans
{
private:
	/////////////////////////////////////////////////
	// 
	//		VARIABLES
	//
	/////////////////////////////////////////////////

	unsigned m_nOfItems;
	unsigned short m_nOfClusters;
	unsigned short m_areaWidth;
	unsigned short m_areaHeight;

	std::vector<Item> m_allItems;
	std::vector<Cluster> m_clusters;
	std::vector<Cluster> m_clustersCopyForDraw;

	std::mutex m_mutex;
	bool bSolved;

	/////////////////////////////////////////////////
	// 
	//		METHODS
	//
	/////////////////////////////////////////////////

	void randomizeItems();
	void createEmptyClusters(std::vector<Point>& kernels);

	//-----------------------------------------------
	//		Algorythm
	//

	void recalculateClusters();
	double calculateEuclidDistance(Point& point, Point& kernel);
	void recalculateKernels();

public:
	/////////////////////////////////////////////////
	// 
	//		METHODS
	//
	/////////////////////////////////////////////////

	//-----------------------------------------------
	//		Constructors
	//
	
	Kmeans(unsigned nOfItems, unsigned short nOfClusters, std::vector<Point> kernels, unsigned short areaWidth, unsigned short areaHeight);

	//-----------------------------------------------
	//		Accessors
	//

		// Getters
	std::vector<Item>& getAllItems();
	std::vector<Cluster> getAllClusters();

	//-----------------------------------------------
	//		Algorythm
	//

	void solve();
};
