#include <SFML/Graphics.hpp>
#include "autoGraph.h"
#include <cmath>
#include <stdlib.h>
#include <windows.h>

#define NUM_GRAPHS	12
#define ROW_LEN		4


autoGraph graphs[NUM_GRAPHS];

int main()
{
	sf::RenderWindow window(sf::VideoMode(1366, 768), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	//autoGraph firstGraph(1260, 740, 16, 750, window);


	uint8_t i;
	for (i = 0; i < NUM_GRAPHS; i++) {
		graphs[i].configure(300, 200, (i % ROW_LEN) * 325, ((i / ROW_LEN) + 1) * 225);
	}

	sf::Clock clock;
	double fps  =0;

	sf::Text fps_counter;
	sf::Font font;
	if (!font.loadFromFile("C:\\Windows\\Fonts\\COUR.ttf")) {
		printf("Failed to load font\n");
	}

	fps_counter.setFont(font);

	uint64_t t = 0;

	sf::Time time;

	while (window.isOpen())
	{
		
		clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		for (i = 0; i < NUM_GRAPHS; i++) {
			graphs[i].addDataPoint((double)t, (double)(t % 256));
			graphs[i].draw(window);
		}

		t++;

		

		//window.display();

		/* Framerate Limiter */
		while (1) {
			time = clock.getElapsedTime();
			double timeSinceLastFrame = time.asSeconds();
			if (timeSinceLastFrame > ( 1 / 60.01)) {
				break;
			}
		}

		time = clock.getElapsedTime();
		fps = 1.0 / time.asSeconds();

		fps_counter.setString(std::to_string(fps));

		window.draw(fps_counter);
		window.display();

	}

	return 0;
}