#pragma once
#include "uno_game.h"

const std::string nameMsgs[] = {
    "Pudge",
    "���� ����� ��������.",
    "� � Pudge.",
};

const std::string playCardMsgs[] = {
    "�� ���� ������ ������.",
    "���� � �����!",
    "��� ����� ����, ��� ���� �������.",
    "�� ���������, ������� ������� ���� ������!",
    "�-�, ������� ����, ������.",
    "���� ������ �������?",
    "Pudge ���� ����������!",
    "������������ �������.",
    "�-�-�-���-���-���-���.",
    "�������� ����, ���� �� �������!"
};

const std::string loseMsgs[] = {
    "� ����������, ������...",
    "���� �������� �� �����.",
    "����-�����.",
    "��� � ��, ����, �������...",
    "�� ��-�-�-��!"
};

const std::string winMsgs[] = {
    "������ ��������� � ������� �� ���!",
    "���� �� ���������� �����, � ���� �� ������ �� ������������.",
    "����� ��� ��������� �������� ����.",
    "����� �� ������, ���� � �������� �����������?"
};

const std::string reactionMsgs[] = {
    "�������, �������. �� ���� ��������� ���������."
};

class Player : public UnoPlayer
{
    std::vector<const Card*> hand;
    std::string playerName;
public:
    Player(const std::string& name_ = "Pudge");

	/// @brief ����� ���������� ���� ���.
    /// @return ��� ������.
    std::string name() const;
    
    /// @brief ����� �������� �� ���� �����.
    /// @param cards ������ ����.
    void receiveCards(const std::vector<const Card*>& cards);

    /// @brief ����� ���������� �����, ������� �� ������� (������� � �����).
    /// @return �����, ������� ����� ������� � �����.
    const Card* playCard();

    /// @brief ���� � ������ ��� ���������� ����, �� ����� �������������� 
    /// ����� � �������, ����� �� �� �� ����� �������� ��� ���.
    /// @param additionalCard �������������� �����.
    /// @return true, ���� ����� ����� �� ������ ��� �����, ����� false.
    bool drawAdditionalCard(const Card * additionalCard);

    /// @brief ���� ����� ������� "������ ����" ��� "������ ������", �� 
    /// ���� �������� � ���� ����� ����.
    /// @return ����� ����.
    CardColor changeColor();
    CardColor mostCardsColor();


    void handlePlayerWonSet(int playerIndex, int score);
    void handlePlayerWonGame(int playerIndex, int totalScore);

    void handleSetStarted(int gameNumber);

};

void removeV(std::vector<const Card*>& arr, const Card* elem);