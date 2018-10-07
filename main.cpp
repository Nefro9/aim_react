#include <iostream>
#include "SFML\Graphics.hpp"
#include "Game.h"
#include "Target.h"

using namespace std;
using namespace sf;

namespace {
    const int windowWidth = 800;
    const int windowHeight = 600;

    const float targetSpawnTime = 60;
}

Font font;

Text createStartText();
Text createInfoText();
Text createScoreText();
Text createEndText();
Text createRetryText();
bool isHitText(Vector2i Position, Text text);

int main()
{
    if (!font.loadFromFile("resources/sansation.ttf"))
        return EXIT_FAILURE;

	RenderWindow window(VideoMode(windowWidth, windowHeight), "AimReact 0.1");
	window.setFramerateLimit(60);


    int spawnTimer = 0;
    float spawnTime = targetSpawnTime; // Spawn every 1s

    char str[1024];

    vector<Target> targets;

    Game game;
    Text startText = createStartText();
    Text infoText  = createInfoText();
    Text score     = createScoreText();
    Text endText   = createEndText();
    Text retryText = createRetryText();

    while (window.isOpen())
	{
		Vector2i position = Mouse::getPosition(window);
        Event event;


		while (window.pollEvent(event))
		{
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                if(game.getStatus() == game.statusIdle)
                {
                    if (isHitText(position, startText))
                    {
                        game.start();
                    }
                }

                if(game.getStatus() == game.statusStart) {

                     for(int i = 0; i < targets.size(); i++) {

                        if(targets[i].isHit(position))
                        {
                            targets.erase(targets.begin() + i);
                            game.addScore(10);
                        } else {
                            game.removeScore(5);
                        }
                    }
                }

                if(game.getStatus() == game.statusStop)
                {
                    if (isHitText(position, retryText)) {
                        game.start();
                    }
                }
            }

			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();



        if(targets.size() > 3 && game.getStatus() == game.statusStart)
        {
            spawnTime = targetSpawnTime;
            targets.clear();
            game.stop();
        }

		if(game.getStatus() == game.statusIdle)
        {
            if (isHitText(position, startText)) {
                startText.setFillColor(Color::Yellow);
            } else {
                startText.setFillColor(Color::White);
            }

            window.draw(startText);
            window.draw(infoText);
		}


		if(game.getStatus() == game.statusStart) {

            if (spawnTimer < spawnTime)
            {
                spawnTimer++;
            }

            if (spawnTimer >= spawnTime)
            {
                spawnTime -= (spawnTime * spawnTime + spawnTime) / 2000;
                targets.push_back(Target(window.getSize()));
                spawnTimer = 0;
            }


            for(int i = 0; i < targets.size(); i++) {
               targets[i].increase();
               targets[i].draw(window);
            }

            game.increaseTime();

            if(game.getTime() % 10 == 0) {
                game.addScore(1);
            }


            sprintf(str, "Score:  %i ", game.getScore());
            score.setString(str);

           window.draw(score);
		}


		if(game.getStatus() == game.statusStop)
		{
            if (isHitText(position, retryText)) {
                retryText.setFillColor(Color::Yellow);
            } else {
                retryText.setFillColor(Color::White);
            }

            retryText.setPosition((windowWidth-retryText.getLocalBounds().width)/2, (windowHeight-retryText.getLocalBounds().height)/2 - 30);

            sprintf(str, "Your score:  %i ", game.getScore());
            endText.setString(str);
            endText.setPosition((windowWidth-endText.getLocalBounds().width)/2, (windowHeight-endText.getLocalBounds().height)/2 - 100);

            window.draw(endText);
            window.draw(retryText);
		}


		window.display();
	}

    return 0;
}

bool isHitText(Vector2i position, Text text)
{
    if(position.x >= text.getPosition().x
    && position.x <= (text.getPosition().x + text.getLocalBounds().width)
    && position.y >= text.getPosition().y
    && position.y <= (text.getPosition().y + text.getLocalBounds().height))
    {
        return true;
    } else {
        return false;
    }
}


Text createStartText()
{
    Text text;
    text.setFont(font);
    text.setCharacterSize(32);
    text.setFillColor(Color::White);
    text.setOutlineThickness(2.0f);
    text.setString("Start");

    text.setPosition((windowWidth-text.getLocalBounds().width)/2, (windowHeight-text.getLocalBounds().height)/2 - 100);

    return text;
}

Text createInfoText()
{
    Text text;
    text.setFont(font);
    text.setCharacterSize(15);
    text.setFillColor(Color::White);
    text.setString("Increase your aim and reaction\n\n\n+10 points for target\n-5 points for missed target");

    text.setPosition((windowWidth-text.getLocalBounds().width)/2, (windowHeight-text.getLocalBounds().height)/2 + 20);

    return text;
}


Text createScoreText()
{
    Text text;
    text.setFont(font);
    text.setCharacterSize(15);
    text.setFillColor(Color::White);
    text.setOutlineThickness(2.0f);
    text.setPosition(710, 15);

    return text;
}

Text createRetryText()
{
    Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(Color::White);
    text.setOutlineThickness(2.0f);
    text.setPosition((windowWidth-text.getLocalBounds().width)/2, (windowHeight-text.getLocalBounds().height)/2 - 30);

    text.setString("Retry?");

    return text;
}

Text createEndText()
{
    Text text;
    text.setFont(font);
    text.setCharacterSize(32);
    text.setFillColor(Color::White);
    text.setOutlineThickness(2.0f);
    text.setPosition((windowWidth-text.getLocalBounds().width)/2, (windowHeight-text.getLocalBounds().height)/2 - 100);
    return text;
}
