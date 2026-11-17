#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Inventory {
private:
    vector<string> unlockedElements;

public:
    Inventory();
    
    void unlockElement(const string& elementName);
    bool hasElement(const string& elementName) const;
    const vector<string>& getUnlockedElements() const;
    void setUnlockedElements(const vector<string>& elements);
    int getUnlockedCount() const;
};

#endif