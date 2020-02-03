#include "Kmeans.hpp"

#include <ctime>
#include <chrono>
#include <thread>

/////////////////////////////////////////////////
// 
//		PRIVATE METHODS
//
/////////////////////////////////////////////////

void Kmeans::randomizeItems()
{
	std::srand(unsigned(std::time(0)));

	for (unsigned int pointN = 0; pointN < m_nOfItems; pointN++)
	{
		m_allItems.emplace_back(
			Item {
				static_cast<unsigned short>(15 + rand() % (m_areaWidth - 25)),
				static_cast<unsigned short>(15 + rand() % (m_areaHeight - 25))
			}
		);
	}
}

void Kmeans::createEmptyClusters(std::vector<Point>& kernels)
{
	for (auto& kernel : kernels)
	{
		m_clusters.emplace_back(Cluster{ kernel });
	}
}



//-----------------------------------------------
//		Algorythm
//

void Kmeans::recalculateClusters()
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

double Kmeans::calculateEuclidDistance(Point& point, Point& kernel)
{
	return sqrt((point.x - kernel.x) * (point.x - kernel.x) + (point.y - kernel.y) * (point.y - kernel.y));
}

void Kmeans::recalculateKernels()
{
	bSolved = true;

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
			bSolved = false;

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

Kmeans::Kmeans(unsigned nOfPoints, unsigned short nOfClusters, std::vector<Point> kernels, unsigned short areaWidth, unsigned short areaHeight) :
	m_nOfItems(nOfPoints),
	m_nOfClusters(nOfClusters),
	m_areaWidth(areaWidth),
	m_areaHeight(areaHeight)

{
	randomizeItems();
	createEmptyClusters(kernels);
}



//-----------------------------------------------
//		Accessors
//

//		Getters

std::vector<Item>& Kmeans::getAllItems()
{
	return m_allItems;
}

std::vector<Cluster> Kmeans::getAllClusters()
{
	std::lock_guard<std::mutex> lock(m_mutex);
	return m_clustersCopyForDraw;
}



//-----------------------------------------------
//		Algorythm
//

void Kmeans::solve()
{
	bSolved = false;

	while (!bSolved)
	{
		recalculateClusters();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		recalculateKernels();
	}
}
