/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-killian.herbreteau
** File description:
** Sorbet.hpp
*/

#ifndef SORBET_HPP_
#define SORBET_HPP_

#include "../Enemy.hpp"

class Sorbet : public AEnemy {
	public:
		Sorbet(const Position &pos);
		~Sorbet(void) = default;
	private:
		static const SpriteSheetRects _spriteSheetRects;
};

extern "C"
{
    AEnemy *getInstance(void);
}

#endif /* SORBET_HPP_ */