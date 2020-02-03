#include <thread>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include "Kmeans.hpp"

//-----------------------------------------------
//		Constants
//

const unsigned short winWidth = 1500;
const unsigned short winHeight = 800;
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

void kmeansThreadFunc();



//-----------------------------------------------
//		Implementations
//

int main()
{	std::srand(unsigned(std::time(0)));
	initKmeans();
	std::thread kmeansThread(kmeansThreadFunc);

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
		
		std::cout << "      FT: " << frameTime.getElapsedTime().asSeconds() << std::endl;
		frameTime.restart().asSeconds();
	}

	kmeansThread.join();

	return 0;
}



void initKmeans()
{
	std::cout << "Enter the number of items: ";
	unsigned nOfItems;
	std::cin >> nOfItems;

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

	kmeans = std::make_unique<Kmeans>(nOfItems, nOfClusters, kernels, winWidth, winHeight);
}



void draw()
{
	auto& allItems = kmeans->getAllItems();

	static sf::CircleShape cs(1);
	cs.setFillColor(sf::Color::Red);

	for (auto& item : allItems)
	{
		cs.setPosition(sf::Vector2f(item.pos.x, item.pos.y));
		renderWindow->draw(cs);
	}
}



void drawVertex()
{
	auto& clusters = kmeans->getAllClusters();

	std::vector<sf::Vertex> items;

	static sf::Color color;
	static sf::CircleShape kernel(8);
	kernel.setOutlineThickness(3);
	kernel.setOutlineColor(sf::Color::White);

	for (auto clusterN = 0; clusterN < clusters.size(); clusterN++)
	{
		switch (clusterN)
		{
		case 0:
			color = sf::Color::Red;
			break;
		case 1:
			color = sf::Color::Green;
			break;
		case 2:
			color = sf::Color::Magenta;
			break;
		case 3:
			color = sf::Color::Yellow;
			break;
		case 4:
			color = sf::Color::Cyan;
			break;
		default:
			std::srand(clusterN);
			color = sf::Color(
				rand() % 255,
				rand() % 255,
				rand() % 255,
				255
			);
		}

		for (auto item : clusters[clusterN].items)
		{
			items.emplace_back(
				sf::Vector2f(item->pos.x, item->pos.y),
				sf::Color(color)
			);
		}

		renderWindow->draw(&items[0], items.size(), sf::Points);


		kernel.setFillColor(sf::Color(color));
		kernel.setPosition(sf::Vector2f(clusters[clusterN].kernel.x, clusters[clusterN].kernel.y));
		renderWindow->draw(kernel);
	}
}



void kmeansThreadFunc()
{
	kmeans->solve();
	std::cout << "SOLVED" << std::endl;
}
