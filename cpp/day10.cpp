#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <map>

int main(int argc, const char * argv[]) {
    std::ifstream file("/Users/rmeertens/Dropbox/workspace/adventofcode2020/inputs/day10.txt");
    std::vector<int> numbers(std::istream_iterator<uint64_t>(file), {});
    
    std::sort(numbers.begin(), numbers.end());
    numbers.insert(numbers.begin(), 0);
    numbers.push_back(numbers[numbers.size()-1]+3);
    
    std::vector<int>differences;
    
    for(size_t x = 1; x < numbers.size(); x++){
        differences.push_back(numbers[x]-numbers[x-1]);
    }
    std::cout << "Part 1: " << std::count_if(differences.begin(), differences.end(), [](int x){return x==1;})*std::count_if(differences.begin(), differences.end(), [](int x){return x==3;}) << std::endl;
    
    // Part 2
    int last_3 = -1;
    std::vector<uint64_t> to_reduce;
    for(size_t i=0; i < differences.size(); i++)
    {
        if (differences[i]==3){
            to_reduce.push_back(i - last_3 -1);
            last_3 = i;
        }
    }
    
    std::map<int, int> multiplier_map = {
        { 0, 1 },
        { 1, 1 },
        { 2, 2 },
        { 3, 4 },
        { 4, 7 },
    };
    
    std::for_each(to_reduce.begin(), to_reduce.end(), [multiplier_map](auto& x){
        x = multiplier_map.at(x);
    });
    
    std::cout << "Part 2: " << std::reduce(to_reduce.begin(), to_reduce.end(), 1UL, std::multiplies<>()) << std::endl;
    
    
    return 0;
}
