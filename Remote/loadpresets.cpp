#include "loadpresets.h"
#include <fstream>
#include <QDir>

LoadPresets::LoadPresets()
{
    qDebug() << "reading from" << QDir::currentPath().toStdString() + "/presets.dat" << "...";
    std::ifstream save(QDir::currentPath().toStdString() + "/presets.dat");
    if (!save) {
        all_cards.emplace_back();
        all_cards.emplace_back();
        all_cards.emplace_back();
        all_cards.emplace_back();
        return;
    }
    std::string line;
    std::getline(save, line);
    std::vector<size_t> counts;
    for (char *at = line.data(); *at; ) {
        char *end = at;
        counts.emplace_back(std::strtoul(at, &end, 10));
        if (at == end) break;
        at = end;
    }
    for (size_t i_preset = 0; i_preset < counts.size(); ++i_preset) {
        all_cards.emplace_back();
        for (size_t i_card = 0; i_card < counts[i_preset]; ++i_card) {
            std::getline(save, line);
            char *at = line.data();
            int gesture = strtoul(at, &at, 10);
            int action = strtoul(at, &at, 10);
            all_cards[i_preset].emplace_back(Card::data{ gesture, action });
        }
    }
    save.close();
}

LoadPresets::~LoadPresets()
{
    std::ofstream save(QDir::currentPath().toStdString() + "/presets.dat", std::ofstream::trunc);
    for (const auto &preset : all_cards) {
        save << preset.size() << ' ';
    }
    save << '\n';
    for (const auto &preset : all_cards) {
        for (const auto &card : preset) {
            save << card.gesture << ' ' << card.action << '\n';
        }
    }
    save.close();
}

const std::vector<Card::data> &LoadPresets::view(size_t preset)
{
    return all_cards[preset];
}
