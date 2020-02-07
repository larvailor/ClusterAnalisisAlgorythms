#include "Kmeans.hpp"

#include <ctime>
#include <chrono>
#include <thread>

/////////////////////////////////////////////////
// 
//		PRIVATE METHODS
//
/////////////////////////////////////////////////


void Kmeans::createEmptyClusters(std::vector<Point>& kernels)
{
	for (auto& kernel : kernels)
	{
		createCluster(kernel);
	}
}



//-----------------------------------------------
//		Algorythm
//

void Kmeans::recalculateKernels()
{
	m_bSolved = true;

	double newX = 0;
	double newY = 0;

	for (auto& cluster : m_clusters)
	{
		newX = 0;
		newY = 0;

		for (auto& item : cluster.items)
		{
			newX = (newX + item->pos.x) / 2;
			newY = (newY + item->pos.y) / 2;
		}

		if (cluster.kernel.x != static_cast<unsigned short>(newX) || cluster.kernel.y != static_cast<unsigned short>(newY))
			m_bSolved = false;

		cluster.kernel.x = newX;
		cluster.kernel.y = newY;
	}
}



/////////////////////////////////////////////////
// 
//		PUBLIC METHODS
//
/////////////////////////////////////////////////

//-----------------------------------------------
//		Constructors
//

Kmeans::Kmeans(unsigned nOfItems, unsigned short nOfClusters, std::vector<Point> kernels, unsigned short areaWidth, unsigned short areaHeight) :
	Algorythm(nOfItems, areaWidth, areaHeight)
{
	createEmptyClusters(kernels);
}



//-----------------------------------------------
//		Algorythm
//

void Kmeans::solve()
{
	m_bSolved = false;

	while (!m_bSolved)
	{
		recalculateClusters();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		recalculateKernels();
	}
}
