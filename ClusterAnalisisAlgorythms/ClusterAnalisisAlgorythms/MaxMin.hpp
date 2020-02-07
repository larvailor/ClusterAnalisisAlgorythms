#pragma once

#include "Algorythm.hpp"

class MaxMin : public Algorythm
{
private:
	/////////////////////////////////////////////////
	// 
	//		VARIABLES
	//
	/////////////////////////////////////////////////

	double m_averageDistance;

	/////////////////////////////////////////////////
	// 
	//		METHODS
	//
	/////////////////////////////////////////////////

	//-----------------------------------------------
	//		Algorythm
	//

	void randomizeFirstCluster();
	void recalculateAverageDistance();
	Item* findTheFartestItem(const Cluster* const cluster);

public:
	/////////////////////////////////////////////////
	// 
	//		METHODS
	//
	/////////////////////////////////////////////////

	//-----------------------------------------------
	//		Constructors
	//

	MaxMin(unsigned nOfItems, unsigned short areaWidth, unsigned short areaHeight);

	//-----------------------------------------------
	//		Algorythm
	//

	void solve();
};
