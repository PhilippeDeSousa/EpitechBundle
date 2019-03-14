/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** main
*/

#include "Graphic.hpp"
#include "Errors.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <SFML/Audio.hpp>

Graphic::Graphic()
{}

/// Best trick ever.
/// it is optimized by the compiler so it's not dirty
void ignore(void)
{
	return;
}

void Graphic::setSprite(sf::Texture texture, int x, int y, sf::RenderWindow &win)
{
	sf::Sprite sprite;

	sprite.setTexture(texture);
	sprite.setPosition(x, y);
	sprite.setScale(SCALE_SPRITE, SCALE_SPRITE);
	win.draw(sprite);
}

void Graphic::setRsrcSprite(sf::Texture texture, int x, int y, sf::RenderWindow &win)
{
	sf::Sprite sprite;

	sprite.setTexture(texture);
	sprite.setPosition(x, y);
	sprite.setScale(SCALE_RSRC_SPRITE, SCALE_RSRC_SPRITE);
	win.draw(sprite);
}

void Graphic::setBackground(sf::RenderWindow &win)
{
	sf::Sprite sprite;

	sprite.setTexture(t_background);
	sprite.setScale(2, 2);
	win.draw(sprite);
	sprite.setPosition(0, 716);
	win.draw(sprite);
}

void Graphic::setRessources(sf::RenderWindow &win, map_t map, int x, int y)
{
	map.f > 0 ? setRsrcSprite(t_food, x + TILE_SIZE / 3, y +
		TILE_SIZE / 3, win) : ignore();
	map.l > 0 ? setRsrcSprite(t_linemate, x, y, win) : ignore();
	map.s > 0 ? setRsrcSprite(t_sibur, x + TILE_SIZE / 2, y, win)
		: ignore();
	map.d > 0 ? setRsrcSprite(t_deraumere, x, y + TILE_SIZE / 3, win)
		: ignore();
	map.p > 0 ? setRsrcSprite(t_phiras, x + TILE_SIZE / 2, y + TILE_SIZE
		/ 3, win) : ignore();
	map.t > 0 ? setRsrcSprite(t_thystame, x, y + TILE_SIZE / 1.5, win)
		: ignore();
	map.m > 0 ? setRsrcSprite(t_mendiane, x + TILE_SIZE / 2, y + TILE_SIZE
		/ 1.5, win) : ignore();
}

void Graphic::displayMap(sf::RenderWindow &win, std::vector<std::vector<map_t> > map)
{
	setBackground(win);
	for (int x = 0; x < map_w + 2; x++)
		setSprite(t_wall, x * TILE_SIZE - cam_x, 0 - cam_y, win);
	for (int y = 0; y < map_h; y++) {
		setSprite(t_wall, - cam_x, (y + 1) * TILE_SIZE - cam_y, win);
		for (int x = 0; x < map_w; x++) {
			setSprite(t_grass, (x + 1) * TILE_SIZE -cam_x,
				(y + 1) * TILE_SIZE - cam_y, win);
			if (map[y][x].players != 0) {
				setSprite(t_robot, (1 + x) * TILE_SIZE - cam_x,
				(1 + y) * TILE_SIZE - cam_y, win);
			}
			setRessources(win, map[x][y], (x + 1) * TILE_SIZE -
			cam_x, (y + 1) * TILE_SIZE - cam_y);
			}
		setSprite(t_wall, (map_w + 1) * TILE_SIZE - cam_x, (y + 1)
			* TILE_SIZE - cam_y, win);
	}
	for (int x = 0; x < map_w + 2; x++)
		setSprite(t_wall, x * TILE_SIZE - cam_x, (map_h + 1) * TILE_SIZE - cam_y, win);
}

void Graphic::setTexture(void)
{
	sf::Sprite _sprite;

	if (!t_grass.loadFromFile("./graphic/assets/dirt.jpg"))
		return ;
	if (!t_wall.loadFromFile("./graphic/assets/wall.jpg"))
		return ;
	if (!t_food.loadFromFile("./graphic/assets/food.png"))
		return ;
	if (!t_linemate.loadFromFile("./graphic/assets/blue2.png"))
		return ;
	if (!t_deraumere.loadFromFile("./graphic/assets/deraumere.png"))
		return ;
	if (!t_mendiane.loadFromFile("./graphic/assets/mendiane.png"))
		return ;
	if (!t_phiras.loadFromFile("./graphic/assets/phiras.png"))
		return ;
	if (!t_sibur.loadFromFile("./graphic/assets/sibur.png"))
		return ;
	if (!t_thystame.loadFromFile("./graphic/assets/thystame.png"))
		return ;
	if (!t_robot.loadFromFile("./graphic/assets/robot.png"))
		return ;
	if (!t_background.loadFromFile("./graphic/assets/background2.png"))
		return ;
}

void Graphic::readMap(zappy::Client *cl, sf::RenderWindow &win)
{
	std::string buf;

	dprintf(cl->GetServerfd(), "get_map\n");
	buf = cl->ReadLine();
	map_w = atoi(strtok(const_cast<char*>(buf.c_str()), " "));
	map_h = atoi(strtok(NULL, " "));
	std::vector<std::vector<map_t> > map(map_h);
	for (int y = 0; y < map_h; y++) {
        	map[y] = std::vector<map_t>(map_w);
		for (int x = 0; x < map_w; x++) {
			buf = cl->ReadLine();
			map[y].push_back(map_t ());
			map[y][x].f = atoi(strtok(const_cast<char*>(buf.c_str()), " "));
			map[y][x].l = atoi(strtok(NULL, " "));
			map[y][x].d = atoi(strtok(NULL, " "));
			map[y][x].s = atoi(strtok(NULL, " "));
			map[y][x].m = atoi(strtok(NULL, " "));
			map[y][x].p = atoi(strtok(NULL, " "));
			map[y][x].t = atoi(strtok(NULL, " "));
			map[y][x].players = atoi(strtok(NULL, " "));
			std::cout << "- " << buf << '\n';
		}
	}
	displayMap(win, map);
}

void Graphic::simpleAddX(int val)
{
	cam_x += val;
}

void Graphic::simpleAddY(int val)
{
	cam_y += val;
}

void Graphic::movingCam(void)
{
	sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ? simpleAddX(-CAM_SPEED)
	 : ignore();
	sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ? simpleAddX(CAM_SPEED)
	 : ignore();
	sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ? simpleAddY(CAM_SPEED)
	 : ignore();
	sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ? simpleAddY(-CAM_SPEED)
	 : ignore();
}


void Graphic::gameLoop(zappy::Client *cl)
{
	sf::RenderWindow win(sf::VideoMode(w_WIDTH, w_HEIGHT), "Zappy");

	cam_x = 0;
	cam_y = 0;
	setTexture();
	while (win.isOpen()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			break ;
		movingCam();
		win.clear();
		readMap(cl, win);
		win.display();
	}
	win.close();
}

int main(int ac, char **av)
{
	sf::SoundBuffer buffer;

	try {
                if (!buffer.loadFromFile("./graphic/assets/music.ogg"))
                        throw(Exceptions("Can't play the music\n"));
                sf::Sound sound;

                sound.setBuffer(buffer);
                sound.setPlayingOffset(sf::seconds(6));
                sound.setLoop(true);
                sound.play();
		zappy::Client Cl(ac, av);
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return (84);
	}
	return (0);
}
