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
    bowls.clear();
    int pins;
    int frame = 0;

    cout << " Bowling Game Score Calculator \n";
    cout << "Enter number of pins knocked down for each roll (0-10).\n";
    cout << "Note: Strike (10) skips second roll in frames 1–9.\n\n";

    while (frame < MAX_BOWLFRAMES) {
        cout << "Frame " << frame + 1 << ", Roll 1: ";
        if (!(cin >> pins) || pins < 0 || pins > 10) {
            cout << "Invalid input. Enter a number between 0 and 10.\n";
            cin.clear();               // Clear error flags
            cin.ignore(10000, '\n');   // Discard invalid input
            continue;
        }

        bowls.push_back(pins);

        // If strike and not in 10th frame
        if (pins == 10 && frame < 9) {
            cout << "Strike!\n";
            ++frame;
            continue;
        }

        // Ask for second roll
        cout << "Frame " << frame + 1 << ", Roll 2: ";
        int secondRoll;
        if (!(cin >> secondRoll) || secondRoll < 0 || secondRoll > 10) {
            cout << "Invalid input. Enter a number between 0 and 10.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            bowls.pop_back();  // Remove first roll, re-enter both
            continue;
        }

        if (pins + secondRoll > 10 && frame < 9) {
            cout << "Invalid frame total. Roll 1 + Roll 2 > 10.\n";
            bowls.pop_back();  // Remove first roll
            continue;
        }

        bowls.push_back(secondRoll);

        ++frame;
    }

    // For 10th frame bonus rolls
    int extraRolls = 0;
    int last = bowls.size() - 2;
    if (bowls[last] == 10 || bowls[last] + bowls[last + 1] == 10)
        extraRolls = (bowls[last] == 10) ? 2 : 1;

    for (int i = 0; i < extraRolls; ++i) {
        cout << "Bonus Roll " << i + 1 << ": ";
        if (!(cin >> pins) || pins < 0 || pins > 10) {
            cout << "Invalid bonus roll.\n";
            cin.clear(); cin.ignore(10000, '\n'); --i;
            continue;
        }
        bowls.push_back(pins);
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
