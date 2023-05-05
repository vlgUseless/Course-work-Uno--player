#include "RandomBot.h"

RandomBot::RandomBot(const std::string& name_): hand(), BotName(name_) {}

std::string RandomBot::name() const { return BotName; }

void RandomBot::handleSetStarted(int gameNumber) {
	hand.clear();
}

void RandomBot::receiveCards(const std::vector<const Card*>& cards) {
	for (auto & card : cards) {
		hand.push_back(card);
	}
}

const Card* RandomBot::playCard() {
	std::vector<const Card*> moves;
	std::vector<const Card*> movesWild4;
	bool canPlayWild4 = true; 

	const Card* curCard = game()->topCard();
	CardColor curColor = game()->currentColor();
	int curValue = curCard->value; 

	for (int i = 0; i < hand.size(); i++) {
		if (hand[i]->value == WildDraw4) {
			movesWild4.push_back(hand[i]);
		}
		else if (hand[i]->color == curColor) {
			canPlayWild4 = false;
			moves.push_back(hand[i]);
		}
		else if (hand[i]->value == curValue or hand[i]->is_wild()) {
			moves.push_back(hand[i]);
		}
		
	}

	srand((unsigned)time(NULL));
	
	if (!moves.empty()) {
		const Card* elem = moves[rand() % moves.size()];
		removeVV(hand, elem);
		return elem;
	}
	else if (!movesWild4.empty() and canPlayWild4) {
		const Card* elem = movesWild4[rand() % movesWild4.size()];
		removeVV(hand, elem);
		return elem;
	}

}

bool RandomBot::drawAdditionalCard(const Card* additionalCard) {
	const Card* curCard = game()->topCard();
	const CardColor curColor = game()->currentColor();
	const int curValue = curCard->value;

	if (rand() % 2 == 0) {
		if ((additionalCard->color == curColor) or (additionalCard->value == curValue)) {
			return true;
		}
	}
	hand.push_back(additionalCard);
	return false;
}
	


CardColor RandomBot::changeColor() {
	int mColor = rand() % 4;
	return (CardColor)mColor;
}


void removeVV(std::vector<const Card*>& arr, const Card* elem) {
	auto it = std::find(arr.begin(), arr.end(), elem);
	if (it != arr.end())
		arr.erase(it);
}