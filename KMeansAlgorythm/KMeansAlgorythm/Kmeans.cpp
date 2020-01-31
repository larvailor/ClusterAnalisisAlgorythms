#include "Kmeans.hpp"

#include <ctime>

/////////////////////////////////////////////////
// 
//		PRIVATE METHODS
//
/////////////////////////////////////////////////

void Kmeans::randomizePoints(sf::Uint32& nOfPoints, sf::Uint32& nOfClusters, sf::Vector2u& areaSize)
{
	std::srand(unsigned(std::time(0)));

	sf::Uint8 frame = m_renderWindow->getSize().x * 0.01;

	for (auto pointN = 0; pointN < nOfPoints; pointN++)
	{
		std::shared_ptr<Point> point = std::make_shared<Point>();
		point->radius = 1;
		point->pos.x = frame + rand() % (areaSize.x - frame - 15);
		point->pos.y = frame + rand() % (areaSize.y - frame - 15);

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


Kmeans::Kmeans(sf::Uint32& nOfPoints, sf::Uint32& nOfClusters, sf::Vector2u areaSize, std::shared_ptr<sf::RenderWindow>& renderWindow) :
	m_renderWindow(renderWindow)
{
	randomizePoints(nOfPoints, nOfClusters, areaSize);

}

void Kmeans::draw()
{

	sf::CircleShape cs;
	cs.setFillColor(sf::Color::Red);
	for (auto& point : m_allPoints)
	{
		cs.setPosition(point->pos);
		cs.setRadius(point->radius);
		m_renderWindow->draw(cs);
	}
}

