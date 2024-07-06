#include "config.h"

void savePlayerScore(const std::string& playerName, int mapCount,
                     const std::string& fileName) {
  std::ofstream outFile(
      fileName, std::ios::binary | std::ios::app);  // open file in append mode

  if (!outFile) {
    // if no file or opening failed, create new file
    outFile.open(fileName, std::ios::binary);
    if (!outFile) {
      std::cerr << "Error opening file for writing!" << std::endl;
      return;
    }
  }

  // write playerName size and playerName
  size_t nameSize = playerName.size();
  outFile.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
  outFile.write(playerName.c_str(), nameSize);

  // write mapCount
  outFile.write(reinterpret_cast<const char*>(&mapCount), sizeof(mapCount));

  // close file
  outFile.close();
}