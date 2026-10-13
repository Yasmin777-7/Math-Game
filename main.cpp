#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

enum enDifficultyLevel { Easy = 1, Med = 2, Hard = 3, MixLevel = 4 };
enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5 };
enum enAnswers { RightAnswer = 1, WrongAnswer = 2 };

struct stGamesRoundInfo {
    short NumberOfRounds = 0;
    short RightAnswers = 0;
    short WrongAnswers = 0;
    enOperationType OpType;
    enDifficultyLevel CurrentLevel;
};

string Tabs(short NumberOfTabs) {
    string t = "";
    for (int i = 1; i <= NumberOfTabs; i++) {
        t += "\t";
    }
    return t;
}

int RandomNumber(int From, int To) {
    return rand() % (To - From + 1) + From;
}

short HowManyQuestion() {
    short GameRounds = 1;
    do {
        cout << "How Many Rounds 1 to 10 ? \n";
        cin >> GameRounds;
    } while (GameRounds < 1 || GameRounds > 10);

    return GameRounds;
}

enDifficultyLevel LevelQuestion() {
    short Level = 1;
    cout << "Enter Questions Level [1]Easy [2]Med [3]Hard [4]Mix? ";
    cin >> Level;
    return (enDifficultyLevel)Level;
}

enOperationType OpTypeQuestion() {
    short OpType = 1;
    cout << "Enter Operation Type [1]Add, [2]Sub, [3]Mul, [4]Div, [5]Mix? ";
    cin >> OpType;
    return (enOperationType)OpType;
}

enOperationType GetRandomOperationType() {
    return (enOperationType)RandomNumber(1, 4);
}

int GetNumberForLevel(enDifficultyLevel Level) {
    if (Level == enDifficultyLevel::MixLevel) {
        Level = (enDifficultyLevel)RandomNumber(1, 3);
    }

    switch (Level) {
    case enDifficultyLevel::Easy: return RandomNumber(1, 10);
    case enDifficultyLevel::Med:  return RandomNumber(10, 50);
    case enDifficultyLevel::Hard: return RandomNumber(50, 100);
    default: return RandomNumber(1, 10);
    }
}

int CalculateSimple(int Number1, int Number2, enOperationType OpType) {
    switch (OpType) {
    case enOperationType::Add: return Number1 + Number2;
    case enOperationType::Sub: return Number1 - Number2;
    case enOperationType::Mul: return Number1 * Number2;
    case enOperationType::Div: return (Number2 != 0) ? Number1 / Number2 : 1;
    default: return Number1 + Number2;
    }
}

char GetOpSymbol(enOperationType OpType) {
    switch (OpType) {
    case enOperationType::Add: return '+';
    case enOperationType::Sub: return '-';
    case enOperationType::Mul: return '*';
    case enOperationType::Div: return '/';
    default: return '+';
    }
}

bool AskAndCheckQuestion(enDifficultyLevel Level, enOperationType OpType) {
    if (OpType == enOperationType::MixOp) {
        OpType = GetRandomOperationType();
    }

    int Number1 = GetNumberForLevel(Level);
    int Number2 = GetNumberForLevel(Level);

    int CorrectAnswer = CalculateSimple(Number1, Number2, OpType);

    cout << "\n" << Number1 << "\n";
    cout << Number2 << " " << GetOpSymbol(OpType) << "\n";
    cout << "---------\n";

    int UserAnswer;
    cin >> UserAnswer;

    if (UserAnswer == CorrectAnswer) {
        cout << "Right Answer :-)\n";
        system("color 2F");
        return true;
    }
    else {
        cout << "Wrong Answer :-(\n";
        cout << "The right answer is : " << CorrectAnswer << "\n";
        system("color 4F");
        cout << "\a";
        return false;
    }
}

void ShowGameOverScreen(stGamesRoundInfo RoundInfo) {
    cout << "\n-------------------------------------------------------\n\n";
    if (RoundInfo.RightAnswers >= RoundInfo.WrongAnswers) {
        cout << Tabs(2) << "Final Results is PASS :-)\n";
        system("color 2F");
    }
    else {
        cout << Tabs(2) << "Final Results is FAIL :-(\n";
        system("color 4F");
        cout << "\a";
    }
    cout << "\n-------------------------------------------------------\n\n";
}

stGamesRoundInfo PlayGame(short HowManyRounds) {
    stGamesRoundInfo RoundInfo;
    RoundInfo.NumberOfRounds = HowManyRounds;
    RoundInfo.CurrentLevel = LevelQuestion();
    RoundInfo.OpType = OpTypeQuestion();

    for (int i = 1; i <= HowManyRounds; i++) {
        cout << "\nQuestion [" << i << "/" << HowManyRounds << "]\n";
        if (AskAndCheckQuestion(RoundInfo.CurrentLevel, RoundInfo.OpType)) {
            RoundInfo.RightAnswers++;
        }
        else {
            RoundInfo.WrongAnswers++;
        }
    }
    return RoundInfo;
}

void ShowFinalGameResults(stGamesRoundInfo RoundInfo) {
    cout << "Number of Questions    :" << RoundInfo.NumberOfRounds << endl;
    cout << "Questions Level        :" << RoundInfo.CurrentLevel << endl;
    cout << "OpType                 :" << RoundInfo.OpType << endl;
    cout << "Number of Right Answers:" << RoundInfo.RightAnswers << endl;
    cout << "Number of Wrong Answers:" << RoundInfo.WrongAnswers << endl;
    cout << "\n-------------------------------------------------------\n\n";
}

void ResetScreen() { 
    system("color 0F");
    system("cls");
  
}

void StartGame() {
    char PlayAgain = 'Y';
    do {
        ResetScreen();
        stGamesRoundInfo GameResults = PlayGame(HowManyQuestion());
        ShowGameOverScreen(GameResults);
        ShowFinalGameResults(GameResults);

        cout << endl << Tabs(2) << "Do you want to play again? (Y/N): ";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main() {
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}
