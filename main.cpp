#include <iostream>
#include <string>
#include <map>
#include <memory>

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

class CardCounter
{
private:
  double runningCount;
  double decksRemaining;
  int cardsDealt;
  std::map<std::string, int> cardValues;

public:
  CardCounter(int totalDecks) : runningCount(0), decksRemaining(totalDecks) {
    cardValues = {
        {"2", 1}, {"3", 1}, {"4", 1}, {"5", 1}, {"6", 1},
        {"7", 0}, {"8", 0}, {"9", 0},
        {"t", -1}, {"j", -1}, {"q", -1}, {"k", -1}, {"a", -1}
    };
  }

  void updateDecksRemaining(int cardsDealt) {
    decksRemaining -= static_cast<double>(cardsDealt) / 52.0;
  }

  void updateCount(const std::string& card) {
    if(cardValues.find(card) != cardValues.end()) {
      runningCount += cardValues[card];
      cardsDealt++;
      updateDecksRemaining(1);
    }
    else {
      std::cout << "Invalid card entered. Try again.\n";
    }
  }

  double getRunningCount() const {
    return runningCount;
  }

  double getTrueCount() const {
    return static_cast<double>(runningCount) / decksRemaining;
  }

  double getDecksRemaining() const {
    return decksRemaining;
  }
};

bool isRunning{true};

int amountOfDecks{};

std::string currentInput{};

std::shared_ptr<CardCounter> cardCounter{nullptr};

void DisplayHelpScreen();
void DisplayDeckCount();
void SetDeckCount();

void Render();
void Input();
void Update();

void ParseInput(std::string inputStr);

int main()
{
  while(isRunning) {
    Render();
    Input();
    Update();
  }
}

void Render() {
  system("cls");
  std::cout << "Mandible's Blackjack Card Counter CLI\n"
    << "Type '/help' or '?' for a list of commands." << std::endl;
  if (cardCounter == nullptr) {
    std::cout << "[Deck Count Not Set]" << std::endl;
  } else {
    std::cout << "Running Count: " << cardCounter->getRunningCount() << std::endl;
    std::cout << "True Count: " << cardCounter->getTrueCount() << std::endl;
    std::cout << "Decks Remaining: " << cardCounter->getDecksRemaining() << std::endl;

  }
}

void Input() {
  std::getline(std::cin, currentInput);
}

void Update() {
  ParseInput(currentInput);
}

void ParseInput(std::string inputStr) {
  system("cls");
  if(inputStr.empty()) {
    return;
  } else {
    if(inputStr.size() == 1) {
      if(cardCounter == nullptr && inputStr[0] != '?') {
        system("cls");
        std::cout << "Deck count not set, pleaset set it to enter a card.\n" << std::endl;
        system("pause");
        return;
      }
      switch(std::tolower(inputStr[0])) {
      case '?':
        DisplayHelpScreen();
        break;
      case '/':
        std::cout << "NO COMMAND ENTERED." << std::endl;
        system("pause");
        break;
      case 'a':
        cardCounter->updateCount("a");
        break;
      case '2':
        cardCounter->updateCount("2");
        break;
      case '3':
        cardCounter->updateCount("3");
        break;
      case '4':
        cardCounter->updateCount("4");
        break;
      case '5':
        cardCounter->updateCount("5");
        break;
      case '6':
        cardCounter->updateCount("6");
        break;
      case '7':
        cardCounter->updateCount("7");
        break;
      case '8':
        cardCounter->updateCount("8");
        break;
      case '9':
        cardCounter->updateCount("9");
        break;
      case 't':
        cardCounter->updateCount("t");
        break;
      case 'j':
        cardCounter->updateCount("j");
        break;
      case 'q':
        cardCounter->updateCount("q");
        break;
      case 'k':
        cardCounter->updateCount("k");
        break;
      default:
        break;
      }
    }
    else {
      if(inputStr[0] == '/') {
        std::string subStr{inputStr.substr(1)};
        if (subStr == "help") {
          DisplayHelpScreen();
        } 
        else if (subStr == "getdeckcount") {
          DisplayDeckCount();
        }
        else if (subStr == "setdeckcount") {
          SetDeckCount();
          Sleep(10);
        }
      }
    }
  }
}

void DisplayHelpScreen() {
  system("cls");
  std::cout << "Help Screen\n"
    << "'/help' or '?' - Displays this screen.\n"
    << "'/getdeckcount' - Shows the current deck amount that has been set.\n"
    << "'/setdeckcount' - Sets the amount of decks you are playing with.\n"
    << "\t(MUST BE SET BEFORE STARTING!!!)\n";
  std::cout << std::endl;
  system("pause");
}

void DisplayDeckCount() {
  system("cls");
  std::cout << "Currently set Deck Count: " << amountOfDecks << '\n' << std::endl;
  system("pause");
}

void SetDeckCount() {
  system("cls");
  std::cout << "Enter an Integer: ";
  std::cin >> amountOfDecks;
  std::cout << "Deck Count set to: " << amountOfDecks << '\n' << std::endl;
  std::cin.clear();
  if(cardCounter == nullptr) {
    cardCounter = std::make_shared<CardCounter>(amountOfDecks);
  } else {
    cardCounter.reset();
    cardCounter = std::make_shared<CardCounter>(amountOfDecks);
  }
  system("pause");
}