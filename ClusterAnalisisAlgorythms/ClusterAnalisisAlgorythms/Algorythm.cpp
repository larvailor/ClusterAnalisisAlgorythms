#include "Algorythm.hpp"

#include <ctime>
#include <thread>

/////////////////////////////////////////////////
// 
//		PRIVATE METHODS
//
/////////////////////////////////////////////////

//-----------------------------------------------
//		Algorythm
//

void Algorythm::randomizeItems(unsigned& nOfItems, unsigned short& areaWidth, unsigned short& areaHeight)
{
	std::srand(unsigned(std::time(0)));

	for (unsigned int pointN = 0; pointN < nOfItems; pointN++)
	{
		m_allItems.emplace_back(
			Item{
				static_cast<unsigned short>(15 + rand() % (areaWidth - 25)),
				static_cast<unsigned short>(15 + rand() % (areaHeight - 25))
			}
		);
	}
}

void Algorythm::createCluster(Point& kernel)
{
	m_clusters.emplace_back(
		Cluster{ kernel }
	);
}

void Algorythm::recalculateClusters()
{
	for (auto& cluster : m_clusters)
	{
		cluster.items.clear();
	}

	static double currNearestClusterDistance;
	static unsigned short currNearestClusterN;
	static double newClusterDistance;

	for (auto& item : m_allItems)
	{
		currNearestClusterDistance = calculateEuclidDistance(item.pos, m_clusters[0].kernel);
		currNearestClusterN = 0;

		for (unsigned short clusterN = 1; clusterN < m_clusters.size(); clusterN++)
		{
			newClusterDistance = calculateEuclidDistance(item.pos, m_clusters[clusterN].kernel);
			if (newClusterDistance < currNearestClusterDistance)
			{
				currNearestClusterDistance = newClusterDistance;
				currNearestClusterN = clusterN;
			}
		}

		m_clusters[currNearestClusterN].items.emplace_back(&item);
	}

	std::lock_guard<std::mutex> lock(m_mutex);
	m_clustersCopyForDraw = m_clusters;
}

double Algorythm::calculateEuclidDistance(const Point& point, const Point& kernel)
{
	return sqrt((point.x - kernel.x) * (point.x - kernel.x) + (point.y - kernel.y) * (point.y - kernel.y));
}



/////////////////////////////////////////////////
// 
//		PUBLIC METHODS
//
/////////////////////////////////////////////////

//-----------------------------------------------
//		Constructors
//

Algorythm::Algorythm(unsigned nOfItems, unsigned short areaWidth, unsigned short areaHeight) :
	m_bSolved(false)
{
	randomizeItems(nOfItems, areaWidth, areaHeight);
}



//-----------------------------------------------
//		Accessors
//

//		Getters

std::vector<Cluster> Algorythm::getAllClusters()
{
	std::lock_guard<std::mutex> lock(m_mutex);
	return m_clustersCopyForDraw;
}
