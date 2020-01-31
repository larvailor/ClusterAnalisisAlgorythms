#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

struct Point
{
	sf::Vector2f pos;
	sf::Uint8 radius;
};

struct Cluster
{
	sf::Vector2f kernel;
	sf::Uint8 kernelRadius;
	std::vector<std::shared_ptr<Point>> m_points;
	sf::Color color;
};

class Kmeans
{
private:
	/////////////////////////////////////////////////
	// 
	//		VARIABLES
	//
	/////////////////////////////////////////////////

	std::shared_ptr<sf::RenderWindow> m_renderWindow;

	std::vector<std::shared_ptr<Point>> m_allPoints;
	std::vector<Cluster> m_clusters;

	/////////////////////////////////////////////////
	// 
	//		METHODS
	//
	/////////////////////////////////////////////////

	void randomizePoints(sf::Uint32& nOfPoints, sf::Uint32& nOfClusters, sf::Vector2u& areaSize);

public:
	/////////////////////////////////////////////////
	// 
	//		METHODS
	//
	/////////////////////////////////////////////////

	//-----------------------------------------------
	//		Constructors
	//
	
	Kmeans(sf::Uint32& nOfOPoints, sf::Uint32& nOfClusters, sf::Vector2u areaSize, std::shared_ptr<sf::RenderWindow>& renderWindow);

	// TMP
	void draw();
};
