#include <thread>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include "Kmeans.hpp"
#include "MaxMin.hpp"

//-----------------------------------------------
//		Constants
//

const unsigned short winWidth = 1500;
const unsigned short winHeight = 800;

//-----------------------------------------------
//		Global variables
//

// Drawing

std::unique_ptr<sf::RenderWindow> renderWindow;


// Algorythms

std::vector<Item> m_allItems;
std::vector<Cluster> m_clusters;
std::vector<Cluster> m_clustersCopyForDraw;

std::mutex m_mutex;

std::unique_ptr<Algorythm> algorythm;



//-----------------------------------------------
//		Forward declarations
//

void processStartMenu();

void initKmeans();
void initMaxMin();

void drawVertex();

void algorythmThreadFunc();



//-----------------------------------------------
//		Implementations
//

int main()
{	
	processStartMenu();

	std::srand(unsigned(std::time(0)));
	std::thread algorythmThread(algorythmThreadFunc);

	renderWindow = std::make_unique<sf::RenderWindow>(sf::VideoMode(winWidth, winHeight), "MaxMin", sf::Style::Titlebar | sf::Style::Close);
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
		
		drawVertex();
		
		renderWindow->display();
		
		//std::cout << "      FT: " << frameTime.getElapsedTime().asSeconds() << std::endl;
		frameTime.restart().asSeconds();
	}

	algorythmThread.join();

	return 0;
}



void processStartMenu()
{
	bool bCorrectInput;
	do
	{
		bCorrectInput = true;

		std::cout << "What type of algorythm do you want to use: " << std::endl;
		std::cout << "1. Kmeans" << std::endl;
		std::cout << "2. MaxMin" << std::endl;
		std::cout << "           Your choice: ";

		char choice;
		std::cin >> choice;
		switch (choice)
		{
		case '1':
			std::cout << "Your choice is Kmeans!" << std::endl << std::endl << std::endl;
			initKmeans();
			break;
		case '2':
			std::cout << "Your choice is MaxMin!" << std::endl << std::endl << std::endl;
			initMaxMin();
			break;
		default:
			std::cout << "Your input is uncorrect! Try again!" << std::endl << std::endl << std::endl;
			bCorrectInput = false;
		}
	} while (!bCorrectInput);
}



void initKmeans()
{
	std::cout << "Enter the number of items: ";
	unsigned nOfItems;
	std::cin >> nOfItems;

	std::cout << "Enter the number of clusters: ";
	unsigned nOfClusters;
	std::cin >> nOfClusters;

	std::vector<Point> kernels;
	Point kernel;
	for (auto clusterN = 0; clusterN < nOfClusters; clusterN++)
	{
		std::cout << "Enter kernel " << clusterN + 1 << " position [xpos ypox] in [" << winWidth << ", " << winHeight << "]" << std::endl;
		std::cin >> kernel.x >> kernel.y;
		kernels.push_back(kernel);
	}

	algorythm = std::make_unique<Kmeans>(nOfItems, kernels, winWidth, winHeight);
}



void initMaxMin()
{
	std::cout << "Enter the number of items: ";
	unsigned nOfItems;
	std::cin >> nOfItems;


	algorythm = std::make_unique<MaxMin>(nOfItems, winWidth, winHeight);
}



void drawVertex()
{
	auto clusters = algorythm->getAllClusters();

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

		for (auto& item : clusters[clusterN].items)
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



void algorythmThreadFunc()
{
	algorythm->solve();
	std::cout << "SOLVED" << std::endl;
}
