#include <iostream>

#include "Kmeans.hpp"

int main()
{
	std::cout << "Enter the number of points: ";
	sf::Uint32 nOfPoints;
	std::cin >> nOfPoints;

	std::cout << "Enter the number of clusters: ";
	sf::Uint32 nOfClusters;
	std::cin >> nOfClusters;


	std::shared_ptr<sf::RenderWindow> renderWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(1500, 800), "Kmeans", sf::Style::Titlebar | sf::Style::Close);
	renderWindow->setFramerateLimit(60);
	
	std::unique_ptr<Kmeans> km = std::make_unique<Kmeans>(nOfPoints, nOfClusters, renderWindow->getSize(), renderWindow);
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
		km->draw();
		renderWindow->display();
	}


	return 0;
}
