#include "Element.hpp"

Element::Element(int id, string name, string cat, string desc, bool discovered)
    : elementId(id), elementName(name), category(cat), description(desc), discoveryStatus(discovered) {}

int Element::getId() const { return elementId; }
string Element::getName() const { return elementName; }
string Element::getCategory() const { return category; }
string Element::getDescription() const { return description; }
bool Element::isDiscovered() const { return discoveryStatus; }
void Element::setDiscovered(bool status) { discoveryStatus = status; }

// BasicElement Implementation
BasicElement::BasicElement(int id, string name, string cat, string desc, bool available)
    : Element(id, name, cat, desc, available), startingAvailability(available) {}

void BasicElement::displayInfo() const {
    cout << "[Basic Element] " << elementName << " (" << category << ")" << endl;
}

bool BasicElement::isStarting() const { return startingAvailability; }

// CraftedElement Implementation
CraftedElement::CraftedElement(int id, string name, string cat, string desc, string requirement)
    : Element(id, name, cat, desc, false), discoveryRequirement(requirement) {}

void CraftedElement::displayInfo() const {
    cout << "[Crafted Element] " << elementName << " (" << category << ") - Requires: " << discoveryRequirement << endl;
}

string CraftedElement::getRequirement() const { return discoveryRequirement; }