#include "Player.hpp"

Player::Player(string name) 
    : playerName(name), totalDiscovered(4), completionStatus(false) {}

string Player::getName() const { return playerName; }
void Player::setName(string name) { playerName = name; }

int Player::getTotalDiscovered() const { return totalDiscovered; }
void Player::setTotalDiscovered(int count) {
    totalDiscovered = count;
    checkCompletion();
}

double Player::getCompletionPercentage() const {
    return (static_cast<double>(totalDiscovered) / 28.0) * 100.0;
}

bool Player::isCompleted() const { return completionStatus; }

void Player::checkCompletion() {
    if (totalDiscovered >= 28) {
        completionStatus = true;
    }
}