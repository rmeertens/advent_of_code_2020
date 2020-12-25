#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

struct PasswordLine
{
    int min_count;
    int max_count;
    char letter;
    std::string password;
};
std::istream& operator>>(std::istream& in, PasswordLine& pwdline)
{
    char dummy;
    in >> pwdline.min_count >> dummy >> pwdline.max_count >> pwdline.letter >> dummy >> pwdline.password;
    return in;
}

int main(int argc, const char * argv[]) {
    std::vector<int> integers;
    
    std::string line;
    std::ifstream file("/Users/rmeertens/Dropbox/workspace/adventofcode2020/inputs/day02.txt");
    
    std::vector<PasswordLine> passwords;
    PasswordLine l;
    
    if (file.is_open())
       {
         while ( getline (file,line) )
         {

             std::stringstream ss{line};
             ss >> l;
             passwords.push_back(l);
         }
         file.close();
       }
    

    size_t num_valid = std::count_if(passwords.begin(), passwords.end(), [](PasswordLine p){
        size_t count = std::count(p.password.begin(), p.password.end(), p.letter);
        return count >= p.min_count && count <= p.max_count;
    });
    
    std::cout << "Num valid part 1:" << num_valid << std::endl;

    num_valid = std::count_if(passwords.begin(), passwords.end(), [](PasswordLine p){
        int num_cor = 0;
        if (p.password[p.min_count-1] == p.letter)
            num_cor++;
        if (p.password[p.max_count-1] == p.letter)
            num_cor++;
        return num_cor == 1;
    });
    
    std::cout << "Num valid part 2:" << num_valid << std::endl;
    
    return 0;
}
