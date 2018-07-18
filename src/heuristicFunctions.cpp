#include "heuristicFunctions.hpp"
#include <iostream>

int	hammiltonDistance(const uint8_t *map, const uint8_t *finishMap, uint8_t mapSize) {
	int inversions = 0;

	for (int i = 0; i < mapSize; i++) {
		if (map[i] != finishMap[i])
			inversions++;
	}
	return (inversions);
}

int	manhattanDistance(const uint8_t *map, const uint8_t *finishMap, uint8_t mapSize) {
	int	price = 0;
	uint8_t	x1, x2, y1, y2, xres, yres;

	for (int i = 0; i < mapSize; i++) {
		if (map[i]) {
			x2 = (map[i] - 1) % State::size;
			y2 = (map[i] - 1) / State::size;

			x1 = (finishMap[i] - 1) % State::size;
			y1 = (finishMap[i] - 1) / State::size;

			if ((int8_t)(xres = x1 - x2) < 0)
				xres *= -1;

			if ((int8_t)(yres = y1 - y2) < 0)
				yres *= -1;

			price += xres + yres;
		}
	}

	return (price);
}
