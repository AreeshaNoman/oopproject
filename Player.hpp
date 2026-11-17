#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

using namespace std;

class Player {
private:
    string playerName;
    int totalDiscovered;
    bool completionStatus;

public:
    Player(string name);

    string getName() const;
    void setName(string name);

    int getTotalDiscovered() const;
    void setTotalDiscovered(int count);

    double getCompletionPercentage() const;
    bool isCompleted() const;
    void checkCompletion();
};

#endif