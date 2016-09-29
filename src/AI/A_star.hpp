#pragma once

#include <SFML/System/Vector2.hpp>
#include <vector>
#include <queue>
#include <unordered_map>

/** \brief Using www.redblobgames.com/pathfinding/a-star/implementation.html */
class AStar
{
public:

    /** \brief A Tile is either passable or not. */
    struct Tile
    {
        bool passable;

        inline bool operator==(const Tile tile) const
        {
            return passable == tile.passable;
        }

        inline bool operator!=(const Tile& tile) const
        {
            return !(*this == tile);
        }
    };

    /** \brief 2D vector of tiles, [y_vector][x_vector]. */
    using TileMap = std::vector<std::vector<Tile>>;

    AStar()                 = delete;
    AStar(const AStar&)     = delete;
    AStar operator=(const AStar&) = delete;

    /** \brief Vector of locations to navigate a TileMap. */
    using Path = std::vector<sf::Vector2i>;

    struct Result
    {
        bool has_path; ///< true iff AStar::run() found a path through the map.
        Path path;     ///< vector of location indices to traverse the map
    };

    /** \brief Runs the AStar algorithm.
     *
     * \note The entity this is being run for should not set the tiles underneath itself to
     * impassable, or the algo will fail on its first iteration.
     *
     * \param[in] start TL (ie. min) corner of entity start position (Tile coordinates).
     * \param[in] end TL (ie. min) corner of entity end position {Tile coordinates}.
     * \param[in] dimensions <dx, dy> dimensions of the entity.
     * \param[in] map Tile map of the traversable area.
     *
     * \return Best path from start to end in the map.*/
    static Result run(const sf::Vector2i& start, const sf::Vector2i& end,
                      const sf::Vector2i& dimensions, const TileMap& map);

private:

    struct Hash
    {
        size_t operator()(const sf::Vector2i& value) const
        {
            std::string tmp = std::to_string(value.x) + "," + std::to_string(value.y);
            return std::hash<std::string>()(tmp);
        }
    };

    /// Key == location, Value == cost function result for that tile
    using CostMap = std::unordered_map<sf::Vector2i, float, Hash>;

    /// Key == location, Value == which location comes before it in the traversal
    using FromMap = std::unordered_map<sf::Vector2i, sf::Vector2i, Hash>;

    /// <cost, location> element pair
    using PQElement = std::pair<float, sf::Vector2i>;

    struct PQElementComp
    {
        bool operator()(const PQElement& a, const PQElement& b) const { return a.first < b.first; }
    };

    /// Priority Queue for sorting the visited locations by their cost
    using PQ = std::priority_queue<PQElement, std::vector<PQElement>, PQElementComp>;
};
