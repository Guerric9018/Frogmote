#ifndef LOADPRESETS_H
#define LOADPRESETS_H

#include <vector>
#include "card.h"

class LoadPresets
{
public:
    LoadPresets();
    ~LoadPresets();

    std::vector<Card::data> &view(size_t preset);

private:
    std::vector<std::vector<Card::data>> all_cards;
};

#endif // LOADPRESETS_H
