#pragma once

#include <iostream>
#include <vector>

struct Point
{
	unsigned short x;
	unsigned short y;
};

struct Cluster
{
	unsigned short kernelX;
	unsigned short kernelY;
	std::vector<std::shared_ptr<Point>> m_points;
};

class Kmeans
{
private:
	/////////////////////////////////////////////////
	// 
	//		VARIABLES
	//
	/////////////////////////////////////////////////

	unsigned m_nOfPoints;
	unsigned short m_nOfClusters;
	unsigned short m_areaWidth;
	unsigned short m_areaHeight;

	std::vector<std::shared_ptr<Point>> m_allPoints;
	std::vector<Cluster> m_clusters;

	/////////////////////////////////////////////////
	// 
	//		METHODS
	//
	/////////////////////////////////////////////////

	void randomizePoints();

public:
	/////////////////////////////////////////////////
	// 
	//		METHODS
	//
	/////////////////////////////////////////////////

	//-----------------------------------------------
	//		Constructors
	//
	
	Kmeans(unsigned nOfPoints, unsigned short nOfClusters, unsigned short areaWidth, unsigned short areaHeight);

	//-----------------------------------------------
	//		Accessors
	//

		// Getters
	std::vector<std::shared_ptr<Point>>& getAllPoints();
	std::vector<Cluster>& getAllClusters();
};
