/*
resource: https://www.youtube.com/watch?v=Y37-gB83HKE
back tracking algo.

 */

#include "config.h"

void mapRandomizer(int worldMap[][mapHeight]) {
  // init map with walls (1)
  for (int y = 0; y < mapHeight; ++y) {
    for (int x = 0; x < mapWidth; ++x) {
      worldMap[x][y] = 1;
    }
  }

  //int visitedTiles = 0;

  std::stack<std::pair<int, int>> vtStack;

  // init algorithm with the first tile (0, 0) aka player start origin
  vtStack.push(std::make_pair(0, 0));
  worldMap[0][0] = 0;

  srand(time(0));  // seed for random number generator

  std::pair<int, int> lastVisitedTile(0, 0);

  while (!vtStack.empty()) {
    std::vector<int> neighbors;

    int x = vtStack.top().first;
    int y = vtStack.top().second;

    // check north neighbor
    if (y > 1 && worldMap[x][y - 2] == 1) neighbors.push_back(0);
    // check east neighbor
    if (x < mapWidth - 2 && worldMap[x + 2][y] == 1) neighbors.push_back(1);
    // check south neighbor
    if (y < mapHeight - 2 && worldMap[x][y + 2] == 1) neighbors.push_back(2);
    // check west neighbor
    if (x > 1 && worldMap[x - 2][y] == 1) neighbors.push_back(3);

    // check for available neighbors
    if (!neighbors.empty()) {
      // randomly choose a neighbor
      int nextTileDirection = neighbors[rand() % neighbors.size()];

      switch (nextTileDirection) {
        case 0:  // north
          worldMap[x][y - 1] = 0;
          worldMap[x][y - 2] = 0;
          vtStack.push(std::make_pair(x, y - 2));
          lastVisitedTile = std::make_pair(x, y - 2);
          break;
        case 1:  // east
          worldMap[x + 1][y] = 0;
          worldMap[x + 2][y] = 0;
          vtStack.push(std::make_pair(x + 2, y));
          lastVisitedTile = std::make_pair(x + 2, y);
          break;
        case 2:  // south
          worldMap[x][y + 1] = 0;
          worldMap[x][y + 2] = 0;
          vtStack.push(std::make_pair(x, y + 2));
          lastVisitedTile = std::make_pair(x, y + 2);
          break;
        case 3:  // west
          worldMap[x - 1][y] = 0;
          worldMap[x - 2][y] = 0;
          vtStack.push(std::make_pair(x - 2, y));
          lastVisitedTile = std::make_pair(x - 2, y);
          break;
      }  
      //++visitedTiles;
    } else {
      // if no neighbors, backtrack
      vtStack.pop();
    }
  }

  // mark the end as exit tile (ensure always an exit)
  worldMap[lastVisitedTile.first][lastVisitedTile.second] = 2;
}
