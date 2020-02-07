#pragma once

#include "Algorythm.hpp"

class Kmeans : public Algorythm
{
private:
	/////////////////////////////////////////////////
	// 
	//		METHODS
	//
	/////////////////////////////////////////////////

	void createEmptyClusters(std::vector<Point>& kernels);

	//-----------------------------------------------
	//		Algorythm
	//

	void recalculateKernels();

public:
	/////////////////////////////////////////////////
	// 
	//		METHODS
	//
	/////////////////////////////////////////////////

	//-----------------------------------------------
	//		Constructors
	//
	
	Kmeans(unsigned nOfItems, std::vector<Point> kernels, unsigned short areaWidth, unsigned short areaHeight);

	//-----------------------------------------------
	//		Algorythm
	//

	void solve();
};
