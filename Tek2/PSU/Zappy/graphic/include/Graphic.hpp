/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** graphic
*/

#ifndef GRAPHIC_HPP_
#define GRAPHIC_HPP_

#include <list>
#include <regex>
#include <iostream>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "Client.hpp"

# define w_HEIGHT 1080
# define w_WIDTH 1080

# define BASE_X 100
# define BASE_Y 100
# define TILE_SIZE 135
# define SCALE_SPRITE 0.6
# define SCALE_RSRC_SPRITE 0.3
# define CAM_SPEED 50

typedef struct	map_s
{
	int	l;
	int	d;
	int	s;
	int	m;
	int	p;
	int	t;
	int	f;
	int	players;
}		map_t;

class Graphic {
public:
	Graphic();
	~Graphic();
	void setTexture(void);
	void movingCam(void);
	void simpleAddX(int val);
	void simpleAddY(int val);
	void gameLoop(zappy::Client *cl);
	void displayMap(sf::RenderWindow &win, std::vector<std::vector<map_t> > map);
	void readMap(zappy::Client *cl, sf::RenderWindow &win);
	void setSprite(sf::Texture texture, int x, int y, sf::RenderWindow &win);
	void setRsrcSprite(sf::Texture texture, int x, int y, sf::RenderWindow &win);
	void setRessources(sf::RenderWindow &win, map_t map, int x, int y);
	void setBackground(sf::RenderWindow &win);
private:
	// sf::RenderWindow &win;
	// std::vector<std::vector<map_t>> map;
	std::vector<sf::Sprite> sprite;
	sf::Texture t_grass;
	sf::Texture t_wall;
	sf::Texture t_robot;
	sf::Texture t_food;
	sf::Texture t_linemate;
	sf::Texture t_deraumere;
	sf::Texture t_mendiane;
	sf::Texture t_phiras;
	sf::Texture t_sibur;
	sf::Texture t_thystame;
	sf::Texture t_background;
	int map_h;
	int map_w;
	int cam_x = 0;
	int cam_y = 0;
};

#endif /* graphic_HPP_ */
