#include "player.hpp"

#include <cmath>

Player::Player() :
    graphic_(),
    gun_(*this)
{ }

void
Player::update(sf::Time elapsed)
{
    float dt = elapsed.asSeconds();
    float dx = 0.f;
    float dy = 0.f;

    if (is_moving.left && !is_moving.right) {
        dx = -get_velocity().x * dt;
    } else if (is_moving.right && !is_moving.left) {
        dx = get_velocity().x * dt;
    }

    if (is_moving.up && !is_moving.down) {
        dy = -get_velocity().y * dt;
    } else if (is_moving.down && !is_moving.up) {
        dy = get_velocity().y * dt;
    }

    move({dx, dy});

    gun_.update(elapsed);
}

const sf::Drawable&
Player::render()
{
    graphic_.setSize(get_dimensions());
    graphic_.setOrigin(get_extents());
    graphic_.setPosition(get_position());
    graphic_.setFillColor(sf::Color::Black);
    return graphic_;
}

void
Player::start_move(Direction direction)
{
    is_moving.set(true, direction);
}

void
Player::stop_move(Direction direction)
{
    is_moving.set(false, direction);
}

void
Player::MovementDirections::set(bool is_moving, Direction direction)
{
    switch (direction) {

    case Direction::UP:
        up = is_moving;
        break;

    case Direction::LEFT:
        left = is_moving;
        break;

    case Direction::DOWN:
        down = is_moving;
        break;

    case Direction::RIGHT:
        right = is_moving;
        break;

    default:
        break;
    }
}
