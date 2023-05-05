#include "Pudge_player.h"
#include <iostream>
Player::Player(const std::string& name_): hand(), playerName(name_) {}

std::string Player::name() const {
	// Providing a seed value
	srand((unsigned)time(NULL));

	return nameMsgs[rand() % size(nameMsgs)];
}

// В начале каждого сета очищаем "руку".
void Player::handleSetStarted(int gameNumber) {
	hand.clear();
}

/// @brief Игрок получает на руки карты.
/// @param cards массив карт.
void Player::receiveCards(const std::vector<const Card*>& cards) {
	for (auto & card : cards) {
		hand.push_back(card);
	}
}

/// @brief Игрок возвращает карту, которую он сыграет (положит в сброс).
/// @return карта, которую игрок положит в сброс.
const Card* Player::playCard() {
	//Массивы, хранящие в себе указатели на карты, которые можно сыграть на данный момент.
	std::vector<const Card*> moves;
	std::vector<const Card*> movesWild;
	std::vector<const Card*> movesWild4;
	bool canPlayWild4 = true; // Переменная, отвечающая за возможность сыграть карту
							  // типа Wild Draw 4.

	// Определяем текущую верхнюю карту сброса, её цвет и значение.
	const Card* curCard = game()->topCard();
	CardColor curColor = game()->currentColor();
	int curValue = curCard->value; 

	// Добавили в массивы moves возможные ходы.
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
	// Устанавливаем значение seed. Необходимо для функции rand().
	srand((unsigned)time(NULL));

	// Если есть карты, совпадающие по значению или по цвету с верхней картой сброса,
	// то играем их.
	if (!moves.empty()) {
		// Случайным образом выбираем карту из массива moves.
		const Card* elem = moves[rand() % moves.size()];
		// Удаляем сыгранную карту из руки.
		removeV(hand, elem);

		return elem;
	}
	// Если нет карт, совпадающих по значению или по цвету с верхней картой сброса,
	// то пытаемся сыграть карту "Заказать цвет", если она есть.
	else if (!movesWild.empty()) {
		// Случайным образом выбираем карту из массива movesWild.
		const Card* elem = movesWild[rand() % movesWild.size()];
		// Удаляем сыгранную карту из руки.
		removeV(hand, elem);

		return elem;
	}
	// Если до этого момента нет подходящих карт, пытаемся сыграть карту "Wild Draw 4".
	else if (!movesWild4.empty() and canPlayWild4) {
		// Случайным образом выбираем карту из массива movesWild4.
		const Card* elem = movesWild4[rand() % movesWild4.size()];
		// Удаляем сыгранную карту из руки.
		removeV(hand, elem);

		return elem;
	}

}

bool Player::drawAdditionalCard(const Card* additionalCard) {
	// Определяем текущую верхнюю карту сброса, её цвет и значение.
	const Card* curCard = game()->topCard();
	const CardColor curColor = game()->currentColor();
	const int curValue = curCard->value;
	
	// Если цвет или значение дополнительной карты совпадает с цветом или значением верхней карты сброса,
	// то сразу её играем.
	if ((additionalCard->color == curColor) or (additionalCard->value == curValue)) {
		return true;
	}
	// В противном случае, добавляем карту в руку Игрока.
	hand.push_back(additionalCard);
	return false;
}

// Функция, определяющая цвет, с которым у Игрока больше всего карт.
CardColor Player::mostCardsColor() {
	// Массив, хранящий количество карт определённого цвета в соответствующей ячейке.
	int cardsColor[4]{};

	// Считаем количество карт с каждым цветом.
	for (int i = 0; i < hand.size(); i++) {
		cardsColor[hand[i]->color] += 1;
	}

	//Выбираем цвет, с которым на руке больше всего карт.
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