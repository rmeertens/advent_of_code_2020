#include <iostream>
#include <vector>
#include <fstream>
#include <string>

int main(int argc, const char * argv[]) {
    std::vector<int> integers;
    
    std::string line;
    std::ifstream myfile("/Users/rmeertens/Dropbox/workspace/adventofcode2020/inputs/day01.txt");
    if (myfile.is_open())
    {
      while ( getline (myfile,line) )
      {

          integers.push_back(stoi(line));
      }
      myfile.close();
    }
    
    for(auto a : integers){
        for(auto b : integers){
            if(a+b == 2020){
                std::cout << "Part 1:" << a*b << std::endl;
            }
        }
    }
    
    for(auto a : integers){
        for(auto b : integers){
            for(auto c : integers){
                if(a+b+c == 2020){
                    std::cout << "Part 2:" << a*b*c << std::endl;
                }
            }
        }
    }
    return 0;
}

