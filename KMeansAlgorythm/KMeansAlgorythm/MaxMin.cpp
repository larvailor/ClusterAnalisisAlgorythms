#include "MaxMin.hpp"

#include <ctime>
#include <thread>
#include <iostream>

/////////////////////////////////////////////////
// 
//		PRIVATE METHODS
//
/////////////////////////////////////////////////

//-----------------------------------------------
//		Algorythm
//

void MaxMin::randomizeItems()
{
	std::srand(unsigned(std::time(0)));

	for (unsigned int pointN = 0; pointN < m_nOfItems; pointN++)
	{
		m_allItems.emplace_back(
			Item{
				static_cast<unsigned short>(15 + rand() % (m_areaWidth - 25)),
				static_cast<unsigned short>(15 + rand() % (m_areaHeight - 25))
			}
		);
	}
}

void MaxMin::randomizeFirstCluster()
{
	unsigned firstKernelN = rand() % (m_allItems.size() - 1);
	createCluster(m_allItems[firstKernelN].pos);

	for (auto& item : m_allItems)
	{
		m_clusters.back().items.emplace_back(&item);
	}
}

void MaxMin::createCluster(Point& kernel)
{
	m_clusters.emplace_back(
		Cluster{ kernel }
	);
}

void MaxMin::recalculateAverageDistance()
{
	m_averageDistance = 0;
	for (auto clusterN = 0; clusterN < m_clusters.size() - 1; clusterN++)
	{
		for (auto neighborClusterN = clusterN + 1; neighborClusterN < m_clusters.size(); neighborClusterN++)
		{
			m_averageDistance = (m_averageDistance + calculateEuclidDistance(m_clusters[clusterN].kernel, m_clusters[neighborClusterN].kernel)) / 2;
		}
	}

	m_averageDistance = m_averageDistance / 2;
}

Item* MaxMin::findTheFartestItem(const Cluster* const cluster)
{
	double currFartestItemDistance = 0;
	double newFartestItemDistance = 0;
	Item* currFartestItem = nullptr;
	for (auto item : cluster->items)
	{
		newFartestItemDistance = calculateEuclidDistance(item->pos, cluster->kernel);
		if (newFartestItemDistance > currFartestItemDistance)
		{
			currFartestItemDistance = newFartestItemDistance;
			currFartestItem = item;
		}
	}

	return currFartestItem;
}

void MaxMin::recalculateClusters()
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

double MaxMin::calculateEuclidDistance(const Point& point, const Point& kernel)
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

MaxMin::MaxMin(unsigned nOfItems, unsigned short areaWidth, unsigned short areaHeight) :
	m_nOfItems(nOfItems),
	m_areaWidth(areaWidth),
	m_areaHeight(areaHeight),
	m_bSolved(false)
{
	randomizeItems();
}



//-----------------------------------------------
//		Algorythm
//

void MaxMin::solve()
{
	m_bSolved = false;

	randomizeFirstCluster();
	auto item = findTheFartestItem(&m_clusters[0]);
	createCluster(item->pos);
	m_averageDistance = calculateEuclidDistance(m_clusters.front().kernel, m_clusters.back().kernel) / 2;

	std::vector<Item*> fartestItems;
	std::vector<bool> vSolved;


	while (!m_bSolved)
	{
		recalculateClusters();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));

		fartestItems.clear();
		for (auto& cluster : m_clusters)
		{
			fartestItems.emplace_back(
				findTheFartestItem(&cluster)
			);
		}
		
		vSolved.clear();
		for (auto i = 0; i < fartestItems.size(); i++)
		{
			vSolved.emplace_back(true);
		}

		for (auto itemN = 0; itemN < fartestItems.size(); itemN++)
		{
			if (calculateEuclidDistance(fartestItems[itemN]->pos, m_clusters[itemN].kernel) > m_averageDistance)
			{
				vSolved[itemN] = false;

				createCluster(fartestItems[itemN]->pos);

				break;
			}
		}

		m_bSolved = true;
		for (auto i = 0; i < fartestItems.size(); i++)
		{
			m_bSolved = m_bSolved && vSolved[i];
		}

		if (!m_bSolved)
		{
			recalculateAverageDistance();
		}

	}
}



//-----------------------------------------------
//		Accessors
//

//		Getters

std::vector<Cluster> MaxMin::getAllClusters()
{
	std::lock_guard<std::mutex> lock(m_mutex);
	return m_clustersCopyForDraw;
}
