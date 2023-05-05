#pragma once
#include "uno_game.h"

const std::string nameMsgs[] = {
    "Pudge",
    "Меня зовут Мясником.",
    "Я — Pudge.",
};

const std::string playCardMsgs[] = {
    "За дело берётся Мясник.",
    "Дело в шляпе!",
    "Так много мяса, так мало времени.",
    "Вы поглядите, сколько сочного мяса вокруг!",
    "Э-э, хорошая идея, слушай.",
    "Кому свежих рёбрышек?",
    "Pudge тебя приголубит!",
    "Познакомимся поближе.",
    "М-м-м-ням-ням-ням-ням.",
    "Накрывай стол, ужин на подходе!"
};

const std::string loseMsgs[] = {
    "Я специально, честно...",
    "Пора садиться на диету.",
    "Ёлки-палки.",
    "Что ж вы, люди, делаете...",
    "Ну не-е-е-ет!"
};

const std::string winMsgs[] = {
    "Будешь красоткой с яблоком во рту!",
    "Фарш не провернуть назад, и мясо из котлет не восстановишь.",
    "После боя настоящий шведский стол.",
    "Никто не против, если я жертвами полакомлюсь?"
};

const std::string reactionMsgs[] = {
    "Спасибо, дружище. Ты тоже аппетитно выглядишь."
};

class Player : public UnoPlayer
{
    std::vector<const Card*> hand;
    std::string playerName;
public:
    Player(const std::string& name_ = "Pudge");

	/// @brief Игрок возвращает свое имя.
    /// @return имя игрока.
    std::string name() const;
    
    /// @brief Игрок получает на руки карты.
    /// @param cards массив карт.
    void receiveCards(const std::vector<const Card*>& cards);

    /// @brief Игрок возвращает карту, которую он сыграет (положит в сброс).
    /// @return карта, которую игрок положит в сброс.
    const Card* playCard();

    /// @brief Если у игрока нет подходящих карт, он тянет дополнительную 
    /// карту и говорит, хочет ли он ее сразу положить или нет.
    /// @param additionalCard дополнительная карта.
    /// @return true, если игрок сразу же кладет эту карту, иначе false.
    bool drawAdditionalCard(const Card * additionalCard);

    /// @brief Если игрок положил "Закажи цвет" или "Возьми четыре", то 
    /// игра запросит у него новый цвет.
    /// @return новый цвет.
    CardColor changeColor();
    CardColor mostCardsColor();


    void handlePlayerWonSet(int playerIndex, int score);
    void handlePlayerWonGame(int playerIndex, int totalScore);

    void handleSetStarted(int gameNumber);

};

void removeV(std::vector<const Card*>& arr, const Card* elem);