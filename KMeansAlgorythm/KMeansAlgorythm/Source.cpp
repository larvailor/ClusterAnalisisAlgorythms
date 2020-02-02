
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include "Kmeans.hpp"


//-----------------------------------------------
//		Global variables
//

std::unique_ptr<sf::RenderWindow> renderWindow;
std::unique_ptr<Kmeans> kmeans;



//-----------------------------------------------
//		Forward declarations
//

void draw();




//-----------------------------------------------
//		Implementations
//

int main()
{
	std::cout << "Enter the number of points: ";
	unsigned nOfPoints;
	std::cin >> nOfPoints;

	std::cout << "Enter the number of clusters: ";
	unsigned short nOfClusters;
	std::cin >> nOfClusters;

	renderWindow = std::make_unique<sf::RenderWindow>(sf::VideoMode(1500, 800), "Kmeans", sf::Style::Titlebar | sf::Style::Close);
	renderWindow->setFramerateLimit(60);
	
	kmeans = std::make_unique<Kmeans>(
		nOfPoints,
		nOfClusters,
		static_cast<unsigned short>(renderWindow->getSize().x),
		static_cast<unsigned short>(renderWindow->getSize().y)
	);

	sf::Event event;
	while (renderWindow->isOpen())
	{
		while (renderWindow->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				renderWindow->close();
				break;
			}
		}

		renderWindow->clear();
		draw();
		renderWindow->display();
	}


	return 0;
}


void draw()
{
	static std::vector<std::shared_ptr<Point>>& allPoints = kmeans->getAllPoints();

	static sf::CircleShape cs(1);
	cs.setFillColor(sf::Color::Red);

	for (auto& point : allPoints)
	{
		cs.setPosition(sf::Vector2f(point->x, point->y));
		renderWindow->draw(cs);
	}
}