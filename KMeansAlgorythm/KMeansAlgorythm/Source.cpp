
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include "Kmeans.hpp"

//-----------------------------------------------
//		Constants
//

const unsigned short winWidth = 1400;
const unsigned short winHeight = 750;
const bool bVertex = true;

//-----------------------------------------------
//		Global variables
//

// Drawing

std::unique_ptr<sf::RenderWindow> renderWindow;
std::vector<sf::Vertex> points;


// Algorythms

std::unique_ptr<Kmeans> kmeans;



//-----------------------------------------------
//		Forward declarations
//

void initKmeans();
void draw();
void drawVertex();




//-----------------------------------------------
//		Implementations
//

int main()
{
	initKmeans();

	for (auto& point : kmeans->getAllPoints())
	{
		points.push_back(sf::Vertex(sf::Vector2f(point->x, point->y), sf::Color::Red));
	}



	renderWindow = std::make_unique<sf::RenderWindow>(sf::VideoMode(winWidth, winHeight), "Kmeans", sf::Style::Titlebar | sf::Style::Close);
	renderWindow->setFramerateLimit(60);

	sf::Clock frameTime;
	sf::Event event;
	while (renderWindow->isOpen())
	{
		frameTime.restart().asSeconds();
		
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
		
		bVertex ? drawVertex() : draw();
		
		renderWindow->display();
		
		std::cout << "FT: " << frameTime.getElapsedTime().asSeconds() << std::endl;
		frameTime.restart().asSeconds();
	}


	return 0;
}



void initKmeans()
{
	std::cout << "Enter the number of points: ";
	unsigned nOfPoints;
	std::cin >> nOfPoints;

	std::cout << "Enter the number of clusters: ";
	unsigned short nOfClusters;
	std::cin >> nOfClusters;

	std::vector<Point> kernels;
	Point kernel;
	for (auto clusterN = 0; clusterN < nOfClusters; clusterN++)
	{
		std::cout << "Enter kernel "<< clusterN + 1 << " position [xpos ypox] in [" << winWidth << ", " << winHeight << "]" << std::endl;
		std::cin >> kernel.x >> kernel.y;
		kernels.push_back(kernel);
	}

	kmeans = std::make_unique<Kmeans>(nOfPoints, nOfClusters, kernels, winWidth, winHeight);
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



void drawVertex()
{
	renderWindow->draw(&points[0], points.size(), sf::Points);
}
