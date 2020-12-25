#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <deque>
#include <set>

int calculate_score(std::deque<int> deck){
    int score = 0;
    for (int x=0; x < deck.size(); x++){
        score += (deck.size()-x)*deck[x];
    }
    return score;
}
int get_score_part1(std::deque<int> p1, std::deque<int> p2){
    while (p1.size() > 0 && p2.size() > 0){
        const int card1 = p1[0];
        const int card2 = p2[0];
        p1.pop_front();
        p2.pop_front();
        
        if(card1 > card2){
            p1.push_back(card1);
            p1.push_back(card2);
        }
        else{
            p2.push_back(card2);
            p2.push_back(card1);
        }
    }
    if(p1.size() > 0){
        return calculate_score(p1);
    }
    else{
        return calculate_score(p2);
    }
}

template<class Iteratable>
std::string deque_to_string(Iteratable iter){
    std::string s = "[";
    for(const auto v : iter){
        s += std::to_string(v) + ",";
    }
    s += "]";
    return s;
}

std::tuple<int, int> get_score_part2(std::deque<int> p1, std::deque<int> p2){
    std::set<std::string> seen_cases;
    
    while (p1.size() > 0 && p2.size() > 0){
        const std::string repr = deque_to_string<std::deque<int>>(p1) + deque_to_string<std::deque<int>>(p2);
        if (seen_cases.count(repr) != 0){
            // Player 1 wins
            return std::tuple<int, int> (calculate_score(p1), 0);
            
        }
        seen_cases.insert(repr);
        
        // Draw the cards to play
        const int card1 = p1[0];
        const int card2 = p2[0];
        p1.pop_front();
        p2.pop_front();
        
        bool p1wins = false;
        if(card1 <= p1.size() && card2 <= p2.size()){
            // get the winner in recursive combat.
            std::tuple<int, int> scores = get_score_part2(std::deque<int>(p1.begin(), p1.begin()+card1), std::deque<int>(p2.begin(),p2.begin()+card2));
            p1wins = std::get<0>(scores) > 0;
        }
        else{
            p1wins = card1 > card2;
        }
        
        // Put the cards on the back of the winning player
        if(p1wins){
            p1.push_back(card1);
            p1.push_back(card2);
        }
        else{
            p2.push_back(card2);
            p2.push_back(card1);
        }
    }
    
    return std::tuple<int, int> (calculate_score(p1), calculate_score(p2));
}
int main(int argc, const char * argv[]) {
    std::ifstream file("/Users/rmeertens/Dropbox/workspace/adventofcode2020/inputs/day22.txt");
    
    std::string line;
    std::deque<int> player1, player2;
    
    int idx = -1;
    while(std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        
        if (line.find("Player") != std::string::npos) {
            idx++;
            continue;
        }
        
        if (idx==0){
            player1.push_back(std::stoi(line));
        }
        else{
            player2.push_back(std::stoi(line));
        }
    }

    std::cout << "Part 1: " << get_score_part1(player1, player2) << std::endl;
    std::tuple<int,int> res = get_score_part2(player1, player2) ;
    std::cout << "Part 2: " << std::get<0>(res) << " " << std::get<1>(res) << std::endl;
    return 0;
}
