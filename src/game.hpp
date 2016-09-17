#pragma once

#include <vector>
#include <memory>

#include "entity.hpp"
/* #include "player.hpp" */

class Game
{
public:
    using Entities = std::vector<std::unique_ptr<Entity>>;

    Game(const Game&)           = delete;
    void operator=(const Game&) = delete;

    static Game& instance();

    inline const Entities& entities() const { return entities_; }
    inline Entities& entity_collection() { return entities_; }

    /* Player* add_player(); */
    /* inline Player* get_player() { return player_; }; */

private:
    Game() = default;

    Entities entities_;
    /* Player* player_; */
};
