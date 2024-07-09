#include "config.h"

void readPlayerScore(std::vector<PlayerData>& players,
                     const std::string& fileName) {
  std::ifstream inFile(fileName, std::ios::binary);
  if (!inFile) {
    std::cerr << "Error opening file for reading!" << std::endl;
    return;
  }

  while (inFile.peek() != EOF) {
    PlayerData playerData;

    // read playerName size and playerName from bin file
    size_t nameSize;
    inFile.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));

    playerData.playerName.resize(nameSize);
    inFile.read(&playerData.playerName[0], nameSize);

    // read mapCount from bin file
    inFile.read(reinterpret_cast<char*>(&playerData.mapCount),
                sizeof(playerData.mapCount));

    players.push_back(playerData);
  }

  inFile.close();
}