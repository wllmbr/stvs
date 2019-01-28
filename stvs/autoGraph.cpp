#include "autoGraph.h"


autoGraph::autoGraph()
{

}

void autoGraph::configure(uint16_t xs, uint16_t ys, uint16_t xp, uint16_t yp) {
	xSize = xs;
	ySize = ys;
	xPos = xp;
	yPos = yp;

	/* Make dummy Minor arrays just to make buildGraph happy */

	xMinors = new sf::RectangleShape[1];
	yMinors = new sf::RectangleShape[1];

	dataPointIndex = 0;
	numDataPoints = 0;

	buildGraph();

	xMinData = 0;
	xMaxData = 0;
	yMinData = 0;
	yMaxData = 0;
}


void autoGraph::buildGraph(void) {
	/* Build Colors */
	sf::Color axisColor(138, 150, 170);
	sf::Color gridColor(68, 77, 91);

	/* Construct Axis */
	xAxis.setSize(sf::Vector2f((float)xSize, (float)AXIS_LINE_WIDTH));
	xAxis.setPosition((float)xPos, (float)yPos);
	xAxis.setFillColor(axisColor);

	yAxis.setSize(sf::Vector2f((float)AXIS_LINE_WIDTH, (float)ySize));
	yAxis.setPosition((float)xPos, (float)yPos - ySize);
	yAxis.setFillColor(axisColor);

	/* Calculate number of minors */
	xNumMinors = (uint16_t)(xSize / MINOR_DISTANCE);
	yNumMinors = (uint16_t)(ySize / MINOR_DISTANCE);

	/* Delete the old Minors array */
	delete[] xMinors;
	delete[] yMinors;

	/* Make new Minors array */
	xMinors = new sf::RectangleShape[xNumMinors];
	yMinors = new sf::RectangleShape[yNumMinors];

	/* Build the lines */
	uint16_t i;
	for (i = 0; i < xNumMinors; i++) {
		xMinors[i].setSize(sf::Vector2f((float)MINOR_LINE_WIDTH, (float)ySize));
		xMinors[i].setPosition(
			(float)(xPos + ((i + 1) * MINOR_DISTANCE)),
			(float)(yPos - ySize)
		);
		xMinors[i].setFillColor(gridColor);
	}

	for (i = 0; i < yNumMinors; i++) {
		yMinors[i].setSize(sf::Vector2f((float)xSize, (float)MINOR_LINE_WIDTH));
		yMinors[i].setPosition(
			(float)xPos,
			(float)(yPos - ((i + 1) * MINOR_DISTANCE))
		);
		yMinors[i].setFillColor(gridColor);
	}

	dataPointColor.r = 8;
	dataPointColor.g = 82;
	dataPointColor.b = 201;


	dpSize.x = DATA_POINT_SIZE;
	dpSize.y = DATA_POINT_SIZE;

	for (i = 0; i < MAX_DATA_POINTS; i++) {
		dataPoints[i].setSize(dpSize);
		dataPoints[i].setFillColor(dataPointColor);
	}


}

autoGraph::~autoGraph() {

}

void autoGraph::draw(sf::RenderWindow &wd) {


	uint16_t i;
	for (i = 0; i < xNumMinors; i++) {
		wd.draw(xMinors[i]);
	}
	for (i = 0; i < yNumMinors; i++) {
		wd.draw(yMinors[i]);
	}

	double localxScale = xScale;
	double localyScale = yScale;

	double xOffset = (double)xPos - ((double)xMinData * (double)localxScale);
	double yOffset = (double)yPos - ((double)yMinData * (double)localyScale);

	for (i = 0; i < numDataPoints; i++) {

		//double xTrueLoc = xOffset + (dataLocations[i][0] * localxScale);
		//double yTrueLoc = xOffset - (dataLocations[i][1] * localxScale);

		double xTrueLoc = (double)xPos + ((dataLocations[i][0] - xMinData) * xScale);
		double yTrueLoc = (double)yPos - ((dataLocations[i][1] - yMinData) * yScale);

		dataPoints[i].setPosition(xTrueLoc, yTrueLoc);
		wd.draw(dataPoints[i]);

	}

	wd.draw(xAxis);
	wd.draw(yAxis);


}

void autoGraph::addDataPoint(double xd, double yd) {

	dataLocations[dataPointIndex][0] = xd;
	dataLocations[dataPointIndex][1] = yd;

	dataPointIndex++;
	if (dataPointIndex > MAX_DATA_POINTS) {
		dataPointIndex = 0;
	}

	numDataPoints++;
	if (numDataPoints >= MAX_DATA_POINTS) {
		numDataPoints = MAX_DATA_POINTS - 1;
	}

	/* Re-adjust min max values */

	xMaxData = std::numeric_limits<double>::lowest();
	xMinData = std::numeric_limits<double>::max();
	yMaxData = std::numeric_limits<double>::lowest();
	yMinData = std::numeric_limits<double>::max();

	uint16_t i;
	for (i = 0; i < numDataPoints; i++) {
		double xt = dataLocations[i][0];
		double yt = dataLocations[i][1];
		if (xt < xMinData) {
			xMinData = xt;
		}
		if (xt > xMaxData) {
			xMaxData = xt;
		}
		if (yt < yMinData) {
			yMinData = yt;
		}
		if (yt > yMaxData) {
			yMaxData = yt;
		}

	}


	xScale = xSize / (xMaxData - xMinData);
	yScale = ySize / (yMaxData - yMinData);


}