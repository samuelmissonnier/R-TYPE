/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-killian.herbreteau
** File description:
** EndGame.hpp
*/

#ifndef END_GAME_HPP_
#define END_GAME_HPP_

#include "../Interface.hpp"
#include <map>

class EndGame : public AInterface {
	public:
		EndGame(void);
		~EndGame(void) = default;
	public:
		virtual size_t handleUserEvent(const std::vector<std::shared_ptr<IUserEvent>> &userEvents);
    	
		void setScoreEndGame(const std::string &endScoreGame);
		
		static std::shared_ptr<IInterface> getInstance(void)
        {
            return std::shared_ptr<IInterface>(new EndGame);
        };
	private:
		size_t _nextLoopInterface;
		const std::vector<std::shared_ptr<IEntity>> _backgrounds;
		const RGBAColor _defaultTextColor;
		std::vector<std::shared_ptr<Text>> _texts;
};

#endif /* END_GAME_HPP_ */