#include "Kmeans.hpp"

#include <ctime>

/////////////////////////////////////////////////
// 
//		PRIVATE METHODS
//
/////////////////////////////////////////////////

void Kmeans::randomizePoints()
{
	std::srand(unsigned(std::time(0)));

	for (auto pointN = 0; pointN < m_nOfPoints; pointN++)
	{
		std::shared_ptr<Point> point = std::make_shared<Point>();
		point->x = 15 + rand() % (m_areaWidth - 25);
		point->y = 15 + rand() % (m_areaHeight - 25);

		m_allPoints.push_back(std::move(point));
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

Kmeans::Kmeans(unsigned nOfPoints, unsigned short nOfClusters, unsigned short areaWidth, unsigned short areaHeight) :
	m_nOfPoints(nOfPoints),
	m_nOfClusters(nOfClusters),
	m_areaWidth(areaWidth),
	m_areaHeight(areaHeight)

{
	randomizePoints();
}



//-----------------------------------------------
//		Accessors
//

//		Getters

std::vector<std::shared_ptr<Point>>& Kmeans::getAllPoints()
{
	return m_allPoints;
}

std::vector<Cluster>& Kmeans::getAllClusters()
{
	return m_clusters;
}
