#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

const int MAX_BOWLFRAMES = 10;

// Function to calculate score for each frame
vector<int> calculateScores(const vector<int>& bowls, int& finalScore) {
    vector<int> frameScores;
    finalScore = 0;
    int i = 0; // Index in bowls

    for (int frame = 0; frame < MAX_BOWLFRAMES; frame++) {
        if (frame == 9) { // 10th frame
            int frameScore = bowls[i] + bowls[i + 1];
            if (bowls[i] == 10 || frameScore == 10) {
                frameScore += bowls[i + 2];
            }
            frameScores.push_back(frameScore);
            finalScore += frameScore;
            break;
        }

        if (bowls[i] == 10) { // Strike
            int bonus = bowls[i + 1] + bowls[i + 2];
            int frameScore = 10 + bonus;
            frameScores.push_back(frameScore);
            finalScore += frameScore;
            i += 1;
        } else if (bowls[i] + bowls[i + 1] == 10) { // Spare
            int bonus = bowls[i + 2];
            int frameScore = 10 + bonus;
            frameScores.push_back(frameScore);
            finalScore += frameScore;
            i += 2;
        } else { // Open frame
            int frameScore = bowls[i] + bowls[i + 1];
            frameScores.push_back(frameScore);
            finalScore += frameScore;
            i += 2;
        }
    }

    return frameScores;
}

// Display per-frame roll and score
void displayScoreBoard(const vector<int>& bowls, const vector<int>& frameScores) {
    cout << "\n Bowling Scoreboard \n";
    cout << "--------------------------------------------------\n";
    cout << "| Frame | bowls       | Frame Score | Cumulative |\n";
    cout << "--------------------------------------------------\n";

    int i = 0;
    int cumulative = 0;
    for (int frame = 0; frame < frameScores.size(); ++frame) {
        cout << "|   " << setw(2) << frame + 1 << "  | ";

        // Show bowls:
        if (frame < 9) {
            if (bowls[i] == 10) {
                cout << "X    -     ";
                i += 1;
            } else {
                int first = bowls[i];
                int second = bowls[i + 1];
                if (first + second == 10)
                    cout << first << "    /     ";
                else
                    cout << first << "    " << second << "     ";
                i += 2;
            }
        } else {
            // 10th frame: up to 3 bowls
            for (int j = 0; j < 3 && i + j < bowls.size(); ++j) {
                if (bowls[i + j] == 10)
                    cout << "X  ";
                else if (j > 0 && bowls[i + j - 1] + bowls[i + j] == 10)
                    cout << "/  ";
                else
                    cout << bowls[i + j] << "  ";
            }
            i += 3;
        }

        cumulative += frameScores[frame];
        cout << "|     " << setw(3) << frameScores[frame]
             << "     |     " << setw(3) << cumulative << "     |\n";
        cout << "--------------------------------------------------\n";
    }

    cout << "\n Final Score: " << cumulative << " \n";
}

int main() {
    vector<int> bowls;
    int pins;

    cout << " Bowling Game Score Calculator \n";
    cout << "Enter the number of pins knocked down for each roll.\n";
    cout << "(Use 10 for strike, enter all bowls including 10th frame bonus bowls):\n\n";

    // Input bowls
    while (bowls.size() < 21) {
        cout << "Roll " << bowls.size() + 1 << ": ";
        cin >> pins;

        // Basic validation
        if (pins < 0 || pins > 10) {
            cout << "Invalid input. Enter a value between 0 and 10.\n";
            continue;
        }

        bowls.push_back(pins);

        // Handle ending input early if 10th frame completed
        if (bowls.size() >= 12) {
            // Try scoring it
            int dummyTotal;
            vector<int> scores = calculateScores(bowls, dummyTotal);
            if (scores.size() == 10) break;
        }
    }

    int finalScore;
    vector<int> frameScores = calculateScores(bowls, finalScore);

    displayScoreBoard(bowls, frameScores);

    return 0;
}
