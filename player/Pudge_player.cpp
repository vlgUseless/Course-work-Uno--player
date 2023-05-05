#include "Pudge_player.h"
#include <iostream>
Player::Player(const std::string& name_): hand(), playerName(name_) {}

std::string Player::name() const {
	// Providing a seed value
	srand((unsigned)time(NULL));

	return nameMsgs[rand() % size(nameMsgs)];
}

// � ������ ������� ���� ������� "����".
void Player::handleSetStarted(int gameNumber) {
	hand.clear();
}

/// @brief ����� �������� �� ���� �����.
/// @param cards ������ ����.
void Player::receiveCards(const std::vector<const Card*>& cards) {
	for (auto & card : cards) {
		hand.push_back(card);
	}
}

/// @brief ����� ���������� �����, ������� �� ������� (������� � �����).
/// @return �����, ������� ����� ������� � �����.
const Card* Player::playCard() {
	//�������, �������� � ���� ��������� �� �����, ������� ����� ������� �� ������ ������.
	std::vector<const Card*> moves;
	std::vector<const Card*> movesWild;
	std::vector<const Card*> movesWild4;
	bool canPlayWild4 = true; // ����������, ���������� �� ����������� ������� �����
							  // ���� Wild Draw 4.

	// ���������� ������� ������� ����� ������, � ���� � ��������.
	const Card* curCard = game()->topCard();
	CardColor curColor = game()->currentColor();
	int curValue = curCard->value; 

	// �������� � ������� moves ��������� ����.
	for (int i = 0; i < hand.size(); i++) {
		if (hand[i]->value == WildDraw4) {
			movesWild4.push_back(hand[i]);
		}
		else if (hand[i]->value == Wild) {
			movesWild.push_back(hand[i]);
		}
		else if (hand[i]->color == curColor) {
			canPlayWild4 = false;
			moves.push_back(hand[i]);
		}
		else if (hand[i]->value == curValue) {
			moves.push_back(hand[i]);
		}
	}
	// ������������� �������� seed. ���������� ��� ������� rand().
	srand((unsigned)time(NULL));

	// ���� ���� �����, ����������� �� �������� ��� �� ����� � ������� ������ ������,
	// �� ������ ��.
	if (!moves.empty()) {
		// ��������� ������� �������� ����� �� ������� moves.
		const Card* elem = moves[rand() % moves.size()];
		// ������� ��������� ����� �� ����.
		removeV(hand, elem);

		return elem;
	}
	// ���� ��� ����, ����������� �� �������� ��� �� ����� � ������� ������ ������,
	// �� �������� ������� ����� "�������� ����", ���� ��� ����.
	else if (!movesWild.empty()) {
		// ��������� ������� �������� ����� �� ������� movesWild.
		const Card* elem = movesWild[rand() % movesWild.size()];
		// ������� ��������� ����� �� ����.
		removeV(hand, elem);

		return elem;
	}
	// ���� �� ����� ������� ��� ���������� ����, �������� ������� ����� "Wild Draw 4".
	else if (!movesWild4.empty() and canPlayWild4) {
		// ��������� ������� �������� ����� �� ������� movesWild4.
		const Card* elem = movesWild4[rand() % movesWild4.size()];
		// ������� ��������� ����� �� ����.
		removeV(hand, elem);

		return elem;
	}

}

bool Player::drawAdditionalCard(const Card* additionalCard) {
	// ���������� ������� ������� ����� ������, � ���� � ��������.
	const Card* curCard = game()->topCard();
	const CardColor curColor = game()->currentColor();
	const int curValue = curCard->value;
	
	// ���� ���� ��� �������� �������������� ����� ��������� � ������ ��� ��������� ������� ����� ������,
	// �� ����� � ������.
	if ((additionalCard->color == curColor) or (additionalCard->value == curValue)) {
		return true;
	}
	// � ��������� ������, ��������� ����� � ���� ������.
	hand.push_back(additionalCard);
	return false;
}

// �������, ������������ ����, � ������� � ������ ������ ����� ����.
CardColor Player::mostCardsColor() {
	// ������, �������� ���������� ���� ������������ ����� � ��������������� ������.
	int cardsColor[4]{};

	// ������� ���������� ���� � ������ ������.
	for (int i = 0; i < hand.size(); i++) {
		cardsColor[hand[i]->color] += 1;
	}

	//�������� ����, � ������� �� ���� ������ ����� ����.
	int mColor = -1000;
	for (int i = 0; i < 4; i++) {
		if (cardsColor[i] > mColor) {
			mColor = i;
		}
	}

	return (CardColor)mColor;
}

CardColor Player::changeColor() {
	return mostCardsColor();
}


void Player::handlePlayerWonSet(int playerIndex, int score) {
	// Providing a seed value
	srand((unsigned)time(NULL));

	say(winMsgs[rand() % size(winMsgs)]);
}
void Player::handlePlayerWonGame(int playerIndex, int totalScore) {
	// Providing a seed value
	srand((unsigned)time(NULL));

	say(winMsgs[rand() % size(winMsgs)]);
}

void removeV(std::vector<const Card*>& arr, const Card* elem) {
	auto it = std::find(arr.begin(), arr.end(), elem);
	if (it != arr.end())
		arr.erase(it);
}