#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <stdint.h>
#include <stdio.h>
#include <limits>

#define AXIS_LINE_WIDTH		3
#define MINOR_LINE_WIDTH	1
#define MINOR_DISTANCE		100
#define MAX_DATA_POINTS		2048
#define DATA_POINT_SIZE		1

class autoGraph{
public:
	~autoGraph();
	autoGraph();
	void configure(uint16_t xs, uint16_t ys, uint16_t xp, uint16_t yp);
	void draw(sf::RenderWindow &wd);
	void addDataPoint(double xd, double yd);

private:
	uint16_t xSize;
	uint16_t ySize;

	/* Position is the bottom left corner of the graph */
	uint16_t xPos;
	uint16_t yPos;

	sf::RectangleShape xAxis;
	sf::RectangleShape yAxis;

	sf::RectangleShape *xMinors;
	sf::RectangleShape *yMinors;
	uint16_t xNumMinors;
	uint16_t yNumMinors;

	void buildGraph(void);
	uint16_t dataPointIndex;
	uint16_t numDataPoints;
	sf::RectangleShape dataPoints[MAX_DATA_POINTS];
	double dataLocations[MAX_DATA_POINTS][2];
	double xMaxData;
	double xMinData;
	double yMaxData;
	double yMinData;

	sf::Color dataPointColor;
	double xScale;
	double yScale;
	sf::Vector2f dpSize;

};

