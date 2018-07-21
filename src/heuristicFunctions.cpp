#include "heuristicFunctions.hpp"
#include "State.hpp"
#include <iostream>
#include <functional>

auto findIndexInMap = [](uint8_t value, const uint8_t *map, uint8_t mapSize) {
	for (int i = 0; i < mapSize; i++)
		if (map[i] == value)
			return (i);
	return (-1);
};

int	nMaxSwap(const uint8_t *map, const uint8_t *finishMap, uint8_t mapSize) {

	int retVal = 0;

	// check if solved
	if (misplacedTiles(map, finishMap, mapSize) == 0)
		return (0);

	int i0 = findIndexInMap(0, map, mapSize);
	int x0 = i0 % State::size;
	int y0 = i0 / State::size;
	int index = x0 * 3 + y0;

	if (index == 9) {
		for (int i = 0; i < 9; i++) {
			int tj = findIndexInMap(i, map, mapSize);
			int ti = (tj % mapSize) * 3 + (tj / mapSize);

			if (ti != i) {
				
			}

		}
	}
	else {

	}


	return (0);
}

int	misplacedTiles(const uint8_t *map, const uint8_t *finishMap, uint8_t mapSize) {
	int inversions = 0;

	for (int i = 0; i < mapSize; i++) {
		if (map[i] != finishMap[i])
			inversions++;
	}
	return (inversions);
}

int	manhattanDistance(const uint8_t *map, const uint8_t *finishMap, uint8_t mapSize) {
	int	price = 0;
	uint8_t	x1, x2, y1, y2, xres, yres, j;

	// auto findIndexInMap = [](uint8_t value, const uint8_t *finishMap, uint8_t mapSize) {
	// 	for (int i = 0; i < mapSize; i++)
	// 		if (finishMap[i] == value)
	// 			return (i);
	// 	return (-1);
	// };

	for (int i = 0; i < mapSize; i++) {
		if (map[i]) {
			x1 = i % State::size;
			y1 = i / State::size;

			j = findIndexInMap(map[i], finishMap, mapSize);

			x2 = j % State::size;
			y2 = j / State::size;

			if ((int8_t)(xres = x1 - x2) < 0)
				xres *= -1;

			if ((int8_t)(yres = y1 - y2) < 0)
				yres *= -1;

			price += xres + yres;
		}
	}

	return (price);
}

static int linearConflicts(const uint8_t *map, const uint8_t *finishMap, uint8_t mapSize) {
	uint8_t	linearConflicts = 0;

	// conflicts in rows
	for (int row = 0; row < State::size; row++) {
		for (int x1 = row * State::size; x1 < row + State::size; x1++) {
			for (int x2 = x1 + 1; x2 < row + State::size; x2++) {
				if (map[x1] != finishMap[x1] && map[x2] != finishMap[x2] &&
					(map[x1] == finishMap[x2] && map[x2] == finishMap[x1]))
							linearConflicts++;
			}
		}
	}

	// conflicts in columns
	for (int col = 0; col < State::size; col++) {
		for (int y1 = col; y1 < col + State::size * (State::size - 1); y1 += State::size) {
			for (int y2 = col + State::size; y2 < col + State::size * (State::size - 1); y2 += State::size) {
				if (map[y1] != finishMap[y1] && map[y2] != finishMap[y2] &&
					(map[y1] == finishMap[y2] && map[y2] == finishMap[y1]))
							linearConflicts++;
			}
		}
	}

	return (linearConflicts);
}

int	MDplusLinearConflicts(const uint8_t *map, const uint8_t *finishMap, uint8_t mapSize) {
	return (manhattanDistance(map, finishMap, mapSize) + linearConflicts(map, finishMap, mapSize));
}

int	MTplusLinearConflicts(const uint8_t *map, const uint8_t *finishMap, uint8_t mapSize) {
	return (misplacedTiles(map, finishMap, mapSize) + linearConflicts(map, finishMap, mapSize));
}
