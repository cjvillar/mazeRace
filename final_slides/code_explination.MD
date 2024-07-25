
```cpp
void mapRandomizer(int worldMap[][mapHeight]) {
```
- This function, `mapRandomizer`, takes a 2D array `worldMap` as input, which represents the game world map. The array has fixed height `mapHeight`.

```cpp
  // init map with walls (1)
  for (int y = 0; y < mapHeight; ++y) {
    for (int x = 0; x < mapWidth; ++x) {
      worldMap[x][y] = 1;
    }
  }
```
- This nested `for` loop initializes every tile in the map to `1`, representing walls. It iterates over every position in the map and sets it to `1`.

```cpp
  std::stack<std::pair<int, int>> vtStack;
```
- Declares a stack named `vtStack` to keep track of visited tiles. Each element is a pair of integers representing the coordinates `(x, y)` of a tile.

```cpp
  // init algorithm with the first tile (0, 0) aka player start origin
  vtStack.push(std::make_pair(0, 0));
  worldMap[0][0] = 0;
```
- Pushes the initial tile `(0, 0)` onto the stack and sets its value in `worldMap` to `0`, indicating it’s a path or an open space.

```cpp
  srand(time(0));  // seed for random number generator
```
- Seeds the random number generator with the current time, ensuring different sequences of random numbers in each execution.

```cpp
  std::pair<int, int> lastVisitedTile(0, 0);
```
- Declares a pair to keep track of the last visited tile, initially set to `(0, 0)`.

```cpp
  while (!vtStack.empty()) {
```
- Starts a loop that continues until the stack is empty.

```cpp
    std::vector<int> neighbors;

    int x = vtStack.top().first;
    int y = vtStack.top().second;
```
- Creates a vector `neighbors` to store available neighboring directions. Gets the coordinates of the tile on top of the stack.

```cpp
    // check north neighbor
    if (y > 1 && worldMap[x][y - 2] == 1) neighbors.push_back(0);
    // check east neighbor
    if (x < mapWidth - 2 && worldMap[x + 2][y] == 1) neighbors.push_back(1);
    // check south neighbor
    if (y < mapHeight - 2 && worldMap[x][y + 2] == 1) neighbors.push_back(2);
    // check west neighbor
    if (x > 1 && worldMap[x - 2][y] == 1) neighbors.push_back(3);
```
- Checks each of the four possible directions (north, east, south, west) to see if they are valid (i.e., within bounds and contain a wall). If a direction is valid, it adds the corresponding direction number to the `neighbors` vector (0 = north, 1 = east, 2 = south, 3 = west).

```cpp
    // check for available neighbors
    if (!neighbors.empty()) {
      // randomly choose a neighbor
      int nextTileDirection = neighbors[rand() % neighbors.size()];
```
- If there are available neighbors, it selects one at random from the `neighbors` vector.

```cpp
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
```
- Depending on the direction chosen, it marks the path to the neighbor by setting the appropriate tiles to `0` (indicating they are paths). It then pushes the new tile onto the stack and updates `lastVisitedTile`.

```cpp
    } else {
      // if no neighbors, backtrack
      vtStack.pop();
    }
  }
```
- If there are no available neighbors, it backtracks by popping the top tile from the stack.

```cpp
  // mark the end as exit tile (ensure always an exit)
  worldMap[lastVisitedTile.first][lastVisitedTile.second] = 2;
```
- Once the stack is empty, it marks the last visited tile as the exit tile by setting its value to `2`.

This algorithm effectively generates a random maze by using a depth-first search (DFS) approach with backtracking, ensuring there is always a path from the start to the end.

The algorithm is designed to leave some walls behind because it only carves out paths in specific locations and leaves the rest as walls. Here are the key factors that ensure walls are left behind:

1. **Initial Wall Setup**: The entire map is initially filled with walls (`1`):
   ```cpp
   for (int y = 0; y < mapHeight; ++y) {
     for (int x = 0; x < mapWidth; ++x) {
       worldMap[x][y] = 1;
     }
   }
   ```

2. **Path Carving**: Paths are carved by setting specific tiles to `0`. The algorithm carves out a path by jumping over one tile at a time, creating a corridor of width one and leaving walls between paths:
   ```cpp
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
   ```

3. **Movement Constraints**: The algorithm moves in increments of 2 cells and only carves out the path cells and their immediate neighbors. For example, when moving north:
   ```cpp
   worldMap[x][y - 1] = 0;
   worldMap[x][y - 2] = 0;
   vtStack.push(std::make_pair(x, y - 2));
   ```
   This ensures that the cells between the paths remain walls.

4. **Neighbor Check**: The neighbor check ensures that the algorithm does not carve out walls indiscriminately. It only considers neighbors that are two steps away and checks if they are still walls before carving:
   ```cpp
   // check north neighbor
   if (y > 1 && worldMap[x][y - 2] == 1) neighbors.push_back(0);
   // check east neighbor
   if (x < mapWidth - 2 && worldMap[x + 2][y] == 1) neighbors.push_back(1);
   // check south neighbor
   if (y < mapHeight - 2 && worldMap[x][y + 2] == 1) neighbors.push_back(2);
   // check west neighbor
   if (x > 1 && worldMap[x - 2][y] == 1) neighbors.push_back(3);
   ```

By carving paths in increments of 2 cells and only updating the specific path cells and their immediate neighbors, the algorithm ensures that walls are left behind. This process creates a maze-like structure with paths and walls rather than clearing out all walls.