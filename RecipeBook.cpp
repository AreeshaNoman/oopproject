#include "RecipeBook.hpp"

RecipeBook::RecipeBook() {
    addRecipe("Water", "Fire", "Steam");
    addRecipe("Earth", "Water", "Mud");
    addRecipe("Earth", "Fire", "Lava");
    addRecipe("Earth", "Air", "Dust");
    addRecipe("Fire", "Air", "Energy");
    addRecipe("Air", "Water", "Rain");
    addRecipe("Lava", "Water", "Stone");
    addRecipe("Mud", "Fire", "Clay");
    addRecipe("Rain", "Earth", "Plant");
    addRecipe("Clay", "Fire", "Brick");
    addRecipe("Stone", "Fire", "Metal");
    addRecipe("Dust", "Stone", "Sand");
    addRecipe("Sand", "Fire", "Glass");
    addRecipe("Steam", "Air", "Cloud");
}

void RecipeBook::addRecipe(string e1, string e2, string res) {
    recipes.push_back({e1, e2, res});
}

string RecipeBook::findCombination(string e1, string e2) const {
    for (const auto& r : recipes) {
        // Order of selection does not matter
        if ((r.elem1 == e1 && r.elem2 == e2) || (r.elem1 == e2 && r.elem2 == e1)) {
            return r.result;
        }
    }
    return ""; // No valid recipe found
}