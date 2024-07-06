#ifndef READPLAYERSCORE_H
#define  READPLAYERSCORE_H

#include "config.h"

struct PlayerData {
    std::string playerName;
    int mapCount;

    bool operator<(const PlayerData& other) const {
        return mapCount > other.mapCount;
    }
};

void readPlayerScore(std::vector<PlayerData>& players, const std::string& fileName);

#endif //  READPLAYERSCORE_H