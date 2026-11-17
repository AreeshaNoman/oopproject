#ifndef RECIPEBOOK_HPP
#define RECIPEBOOK_HPP
#include <string>
#include <vector>
#include <utility>
using namespace std;

struct Recipe {
    string elem1;
    string elem2;
    string result;
};

class RecipeBook {
private:
    vector<Recipe> recipes;

public:
    RecipeBook();
    void addRecipe(string e1, string e2, string res);
    string findCombination(string e1, string e2) const;
};
#endif