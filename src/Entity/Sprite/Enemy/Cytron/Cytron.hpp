/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-killian.herbreteau
** File description:
** Cytron.hpp
*/

#ifndef CYTRON_HPP_
#define CYTRON_HPP_

#include "../Enemy.hpp"

class Cytron : public AEnemy {
	public:
		Cytron(const Position &pos);
		~Cytron(void) = default;
	private:
		static const SpriteSheetRects _spriteSheetRects;
};

extern "C"
{
    AEnemy *getInstance(void);
}

#endif /* CYTRON_HPP_ */