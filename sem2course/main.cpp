#include "uno_game.h"
#include "Pudge_player.h"
#include "RandomBot.h"
#include "logger.h"
#include "stats.h"
#include <vld.h>
void statisticTest()
{
    UnoGame game;
    Player player1("Vasya"), player2("Kolya");
    RandomBot Bot("Bot");
    game.addPlayer(&player1);
    //game.addPlayer(&player2);
    game.addPlayer(&Bot);
    StatsObserver result = runGames(game, 1000);
    StatsObserver::MV winMV = result.getWinsMV();
    std::cout << "Vasya won in " << winMV.mean[0] * 100 << "% of games" << std::endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    UnoGame game;
    game.setRandomGeneratorSeed(552512);
    Logger logger;
    Player player1("Vasya"), player2("Kolya");
    //RandomBot Bot("Bot");
    game.addPlayer(&player1);
    game.addPlayer(&player2);
    game.addPlayer(&Bot);
    game.addObserver(&logger);
    game.runGame(); 
    //statisticTest();
}


