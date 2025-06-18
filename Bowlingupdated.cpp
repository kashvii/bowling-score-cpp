#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

const int MAX_BOWLFRAMES = 10;

class BowlingGame {
private:
    vector<int> bowls;
    vector<int> frameScores;
    int finalScore;

public:
    void inputRolls();
    void calculateScores();
    void displayScoreBoard();
};

void BowlingGame::inputRolls() {
    int pins;
    cout << " Bowling Game Score Calculator \n";
    cout << "Enter the number of pins knocked down for each roll.\n";
    cout << "(Use 10 for strike, enter all bowls including 10th frame bonus bowls):\n\n";

    while (bowls.size() < 21) {
        cout << "Roll " << bowls.size() + 1 << ": ";
        cin >> pins;

        if (pins < 0 || pins > 10) {
            cout << "Invalid input. Enter a value between 0 and 10.\n";
            continue;
        }

        bowls.push_back(pins);

        if (bowls.size() >= 20) {
            calculateScores();
            if (frameScores.size() == 10) break;
        }
    }
}

void BowlingGame::calculateScores() {
    frameScores.clear();
    finalScore = 0;
    int i = 0;

    for (int frame = 0; frame < MAX_BOWLFRAMES; frame++) {
        if (frame == 9) {
            int frameScore = bowls[i] + bowls[i + 1];
            if (bowls[i] == 10 || frameScore == 10) {
                frameScore += bowls[i + 2];
            }
            frameScores.push_back(frameScore);
            finalScore += frameScore;
            break;
        }

        if (bowls[i] == 10) {
            int bonus = bowls[i + 1] + bowls[i + 2];
            int frameScore = 10 + bonus;
            frameScores.push_back(frameScore);
            finalScore += frameScore;
            i += 1;
        } else if (bowls[i] + bowls[i + 1] == 10) {
            int bonus = bowls[i + 2];
            int frameScore = 10 + bonus;
            frameScores.push_back(frameScore);
            finalScore += frameScore;
            i += 2;
        } else {
            int frameScore = bowls[i] + bowls[i + 1];
            frameScores.push_back(frameScore);
            finalScore += frameScore;
            i += 2;
        }
    }
}

void BowlingGame::displayScoreBoard() {
    cout << "\nFrame\tRolls\t\tType\tBonus\tFrame Score\tCumulative\n";

    int i = 0;
    int cumulative = 0;

    for (int frame = 0; frame < MAX_BOWLFRAMES; ++frame) {
        string rolls, type, bonus;
        int frameScore = frameScores[frame];

        if (frame == 9) {
            int first = bowls[i];
            int second = (i + 1 < bowls.size()) ? bowls[i + 1] : 0;
            int third = (i + 2 < bowls.size()) ? bowls[i + 2] : 0;

            rolls = to_string(first);
            if (second > 0) rolls += " + " + to_string(second);
            if (first == 10 || first + second >= 10) rolls += " + " + to_string(third);

            type = "10th Frame";
            bonus = "—";
            i += 3;
        }
        else if (bowls[i] == 10) {
            rolls = "10";
            type = "Strike";
            int b1 = (i + 1 < bowls.size()) ? bowls[i + 1] : 0;
            int b2 = (i + 2 < bowls.size()) ? bowls[i + 2] : 0;
            bonus = "+" + to_string(b1) + " + " + to_string(b2);
            i += 1;
        }
        else {
            int first = bowls[i];
            int second = (i + 1 < bowls.size()) ? bowls[i + 1] : 0;
            rolls = to_string(first) + " + " + to_string(second);

            if (first + second == 10) {
                type = "Spare";
                int b = (i + 2 < bowls.size()) ? bowls[i + 2] : 0;
                bonus = "+" + to_string(b);
            } else {
                type = "Open";
                bonus = "—";
            }
            i += 2;
        }

        cumulative += frameScore;
        cout << frame + 1 << "\t" << rolls
             << ((rolls.length() < 7) ? "\t\t" : "\t")
             << type << "\t" << bonus
             << "\t" << frameScore << "\t\t" << cumulative << "\n";
    }

    cout << "\nFinal Score: " << cumulative << "\n";
}

int main() {
    BowlingGame game;
    game.inputRolls();
    game.calculateScores();
    game.displayScoreBoard();
    return 0;
}
