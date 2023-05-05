#pragma once
#include "uno_game.h"

class RandomBot : public UnoPlayer
{
    std::vector<const Card*> hand;
    std::string BotName;
public:
    RandomBot(const std::string& name_ = "RandomBot");

    std::string name() const;
    
    void receiveCards(const std::vector<const Card*>& cards);

    const Card* playCard();

    bool drawAdditionalCard(const Card * additionalCard);

    CardColor changeColor();

    void handleSetStarted(int gameNumber);
};

void removeVV(std::vector<const Card*>& arr, const Card* elem);