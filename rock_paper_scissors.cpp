#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <map>
#include <iomanip>
using namespace std;

class RPSGame {
private:
    int userScore, compScore, draws, totalGames;
    map<string, int> userChoiceStats;
    const string statsFile = "rps_stats.txt";

    string getChoiceName(int c){
        if(c==1) return "Rock";
        if(c==2) return "Paper";
        return "Scissors";
    }
    int getWinner(int user, int comp){
        if(user==comp) return 0; // draw
        if((user==1 && comp==3) || (user==2 && comp==1) || (user==3 && comp==2)) return 1; // user win
        return 2; // comp win
    }
    void saveStats(){
        ofstream f(statsFile);
        f << "Total Games: " << totalGames << "\n";
        f << "User Wins: " << userScore << "\n";
        f << "Computer Wins: " << compScore << "\n";
        f << "Draws: " << draws << "\n";
        f.close();
    }
    void loadStats(){
        ifstream f(statsFile);
        if(f.is_open()){
            string line;
            cout << "\n--- PREVIOUS STATS LOADED ---\n";
            while(getline(f,line)) cout << line << endl;
            f.close();
        }
    }

public:
    RPSGame(): userScore(0), compScore(0), draws(0), totalGames(0){
        srand(time(0));
        userChoiceStats["Rock"]=0;
        userChoiceStats["Paper"]=0;
        userChoiceStats["Scissors"]=0;
        cout << "====================================\n";
        cout << "  ROCK PAPER SCISSORS - PRO EDITION\n";
        cout << "  CODSOFT INTERNSHIP PROJECT\n";
        cout << "====================================\n";
        loadStats();
    }

    void showRules(){
        cout << "\n--- RULES ---\n";
        cout << "1. Rock crushes Scissors\n";
        cout << "2. Scissors cuts Paper\n";
        cout << "3. Paper covers Rock\n";
        cout << "Best of 5 rounds wins the match!\n";
    }

    void playMatch(){
        int rounds = 5;
        int userMatch=0, compMatch=0;
        cout << "\nStarting Best of " << rounds << " Match!\n";
        for(int i=1; i<=rounds; i++){
            cout << "\n--- Round " << i << " ---\n";
            cout << "Choose: 1.Rock 2.Paper 3.Scissors: ";
            int userChoice; cin >> userChoice;
            if(userChoice<1 || userChoice>3){ cout << "Invalid! Round skipped.\n"; continue; }

            int compChoice = (rand()%3)+1;
            userChoiceStats[getChoiceName(userChoice)]++;
            totalGames++;

            cout << "You: " << getChoiceName(userChoice) << " | Computer: " << getChoiceName(compChoice) << endl;
            
            int result = getWinner(userChoice, compChoice);
            if(result==0){ cout << ">> It's a DRAW!\n"; draws++; }
            else if(result==1){ cout << ">> YOU WIN this round!\n"; userScore++; userMatch++; }
            else { cout << ">> COMPUTER WINS this round!\n"; compScore++; compMatch++; }
        }
        cout << "\n=== MATCH RESULT ===\n";
        cout << "You Won: " << userMatch << " Rounds\n";
        cout << "Computer Won: " << compMatch << " Rounds\n";
        if(userMatch>compMatch) cout << ">>> YOU ARE THE MATCH WINNER! <<<\n";
        else if(compMatch>userMatch) cout << ">>> COMPUTER WINS THE MATCH! <<<\n";
        else cout << ">>> MATCH DRAW! <<<\n";
        saveStats();
    }

    void showAnalytics(){
        cout << "\n--- GAME ANALYTICS ---\n";
        cout << "Total Rounds Played: " << totalGames << endl;
        cout << "Your Total Wins: " << userScore << endl;
        cout << "Computer Wins: " << compScore << endl;
        cout << "Draws: " << draws << endl;
        cout << "Your Favorite Choice:\n";
        for(auto &p: userChoiceStats){
            cout << "  " << p.first << ": " << p.second << " times\n";
        }
        double winRate = totalGames>0 ? (double)userScore/totalGames*100 : 0;
        cout << "Your Win Rate: " << fixed << setprecision(2) << winRate << "%\n";
    }

    void run(){
        int ch;
        do{
            cout << "\n--- MENU ---\n1. Show Rules\n2. Play Match (Best of 5)\n3. View Analytics\n4. Exit\nChoice: ";
            cin >> ch;
            if(ch==1) showRules();
            else if(ch==2) playMatch();
            else if(ch==3) showAnalytics();
            else if(ch==4) cout << "Thanks for playing!\n";
            else cout << "Invalid!\n";
        }while(ch!=4);
    }
};

int main(){
    RPSGame game;
    game.run();
    return 0;
}
