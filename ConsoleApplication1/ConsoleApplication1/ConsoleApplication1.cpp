#include <iostream>
using namespace std;

enum enGameChoice { Stone = 1, Paper = 2 , Scissors = 3};
enum enWinner { Player1 = 1 , Computer = 2 , Draw = 3};

struct stRoundInfo
{
    short RoundNumber = 0;
    enGameChoice Player1Choice;
    enGameChoice ComputerChoice;
    enWinner Winner;
    string WinnerName;
};
struct stGameResults
{
    short GameRounds = 0;
    short Player1WinTimes = 0;
    short Computer2WinTime = 0;
    short DrawTime = 0;
    enWinner GameWinner;
    string WinnerName = "";
};

int RandomNumber(int From, int To)
{
    //Function to generate a random number
    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}
enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
    if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
    {
        return enWinner::Draw;
    }
    switch (RoundInfo.Player1Choice)
    {
    case enGameChoice::Stone:
        if (RoundInfo.ComputerChoice == enGameChoice::Paper)
        {
            return enWinner::Computer;
        }
        break;
    case enGameChoice::Paper:
        if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
        {
            return enWinner::Computer;
        }
        break;
    case enGameChoice::Scissors:
        if (RoundInfo.ComputerChoice == enGameChoice::Stone)
        {
            return enWinner::Computer;
        }
        break;
    }
    //if you reach here then plyer1 is the winner
    return enWinner::Player1;
}
enGameChoice ReadPlayer1Choice()
{
    short Choice = 0; 
    do
    {
        cout << "\nEnter Your Choice:\n [1] Stone \n [2] Paper \n [3] Scissors \n>> ";
        cin >> Choice;
    } while (Choice < 1 || Choice>3);
    
    return enGameChoice(Choice);
}
enGameChoice GetComputerChoice()
{
    return (enGameChoice)RandomNumber(1, 3);
}
string ChoiceName(enGameChoice Choice)
{
    string arrGameChoice[3] = { "Stone","Paper","Scissors" };
   
    return arrGameChoice[Choice - 1];
}

void PrintRoundResult(stRoundInfo RoundInfo)
{
    cout << "\n_______  Round [" << RoundInfo.RoundNumber << "]  _______\n";
    cout << " Player 1 Chose: " << ChoiceName(RoundInfo.Player1Choice) << "\n";
    cout << " Computer Chose: " << ChoiceName(RoundInfo.ComputerChoice) << "\n";
    cout << " Winner: " << RoundInfo.WinnerName << "\n";
    cout << "________________________________________________\n" << endl;


}

enWinner WhoWonTheGame(short Player1, short Computer)
{
    if (Player1 > Computer)
    {
        return enWinner::Player1;
    }
    else if (Computer > Player1)
    {
        return enWinner::Computer;
    }
    else
        return enWinner::Draw;
}
string WinnerName(enWinner Winner)
{
    string arrWinnerName[3] = { "Player1","Computer","No Winner" };
    return arrWinnerName[Winner - 1];
}
stGameResults FillGameResults(short GameRounds, short Player1WinerTimes, short ComputerWinTimes, short DrawTime)
{
    stGameResults GameResults;

    GameResults.GameRounds = GameRounds;
    GameResults.Player1WinTimes = Player1WinerTimes;
    GameResults.Computer2WinTime = ComputerWinTimes;
    GameResults.DrawTime = DrawTime;
    GameResults.GameWinner = WhoWonTheGame(Player1WinerTimes, ComputerWinTimes);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);

    return GameResults;
}


stGameResults PlayGame(short HowManyRounds)
{
    stRoundInfo RoundInfo;
    short Player1WinTime = 0, ComputerWinTime = 0, DrawTime = 0;

    for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
    {
        cout << "\nRound [" << GameRound << "] - Let’s see who wins!\n";
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.Player1Choice = ReadPlayer1Choice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        if (RoundInfo.Winner == enWinner::Player1)
            Player1WinTime++;
        else if (RoundInfo.Winner == enWinner::Computer)
            ComputerWinTime++;

        else DrawTime++;

        PrintRoundResult(RoundInfo);
    }
    return FillGameResults(HowManyRounds, Player1WinTime, ComputerWinTime, DrawTime);
}

void SetWinnerScreenColor(enWinner Winner)
{
    switch (Winner)
    {
    case enWinner::Player1:
        system("color 2F");
        break;

    case enWinner::Computer:
        system("color 4F");
        cout << "\a";
        break;
    case enWinner::Draw:
        system("color 6F");
        break;
    }
}

void ShowFinalGameResult(stGameResults GameResult)
{
    cout << "\n\t\t=============================================\n";
    cout << "\t\t                 [Game Results]           \n";
    cout << "\t\t=============================================\n\n";

    cout << "\t\t Total Rounds Played : " << GameResult.GameRounds << "\n";
    cout << "\t\t Player Wins         : " << GameResult.Player1WinTimes << "\n";
    cout << "\t\t Computer Wins       : " << GameResult.Computer2WinTime << "\n";
    cout << "\t\t Draws               : " << GameResult.DrawTime << "\n";
    cout << "\t\t Final Winner        : " << GameResult.WinnerName << "\n";

    cout << "\n\t\t=============================================\n";

    SetWinnerScreenColor(GameResult.GameWinner);
}

void ShowGameOverScreen()
{
    cout << "\t\t"<<"===============================================\n";
    cout << "\t\t"<<"              G A M E  O V E R              \n";
    cout << "\t\t"<<"===============================================\n\n";

}
void ShowGameStartScreen() {
    cout << "\n\n";
    cout << "\t\t=============================================\n";
    cout << "\t\t|                                           |\n";
    cout << "\t\t|       Welcome to Rock-Paper-Scissors!     |\n";
    cout << "\t\t|                                           |\n";
    cout << "\t\t=============================================\n\n";
    cout << "\t\t       Are you ready to take the challenge?\n";
    cout << "\t\t             May the best player win! \n";
    cout << "\n";
    cout << "\t\t=============================================\n";
    cout << "\t\t|              Let the game begin!          |\n";
    cout << "\t\t=============================================\n";
    cout << "\n\n";
}


short ReadHowMayRounds()
{
    short choice = 0;
    ShowGameStartScreen();
    do
    {
      
       cout << "Choose how many rounds you want to play [ 1 - 10 ]: ";
        cin >> choice;
    } while (choice < 1 || choice > 10);
   
    return choice;
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

void StartGame()
{
    char PlayAgain = 'y';
    do
    {
        ResetScreen();
        stGameResults GameResults = PlayGame(ReadHowMayRounds());
        ShowGameOverScreen();
        ShowFinalGameResult(GameResults);
        cout << "\n\n\t\tDo you want to play again? y/n ";
        cin >> PlayAgain;

    } while (PlayAgain == 'y' || PlayAgain == 'Y');
}


int main()
{
    
     srand((unsigned)time(NULL));

     StartGame();

     return 0;
}

