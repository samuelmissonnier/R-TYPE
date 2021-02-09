/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-killian.herbreteau
** File description:
** Bob.hpp
*/

#ifndef BOB_HPP_
#define BOB_HPP_

#include "../Enemy.hpp"

class Bob  : public AEnemy {
	public:
		Bob(const Position &pos);
		~Bob(void) = default;
	private:
		static const SpriteSheetRects _spriteSheetRects;
};

extern "C"
{
    AEnemy *getInstance(void);
}

#endif /* BOB_HPP_ */