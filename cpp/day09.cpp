#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>

bool is_valid_xmas(std::vector<uint64_t> numbers, size_t start, size_t end){
    for (size_t x = start; x < end; x++){
        for( size_t y = x+1; y < end; y++){
            if (numbers[x]+numbers[y] == numbers[end]){
                return true;
            }
        }
    }
    return false;
}

int main(int argc, const char * argv[]) {
    std::ifstream file("/Users/rmeertens/Dropbox/workspace/adventofcode2020/inputs/day09.txt");
    std::vector<uint64_t> numbers(std::istream_iterator<uint64_t>(file), {});
    
    size_t answer_part1 = 0;
    size_t preamble = 25;
    for(size_t start = preamble; start < numbers.size(); start++ ){
        if(!is_valid_xmas(numbers, start-preamble, start)){
            std::cout << "Part 1: " << numbers[start] << std::endl;
            answer_part1 = numbers[start];
        }
    }
    
    for (preamble=2; preamble < 100; preamble++){
        for(size_t x = preamble; x < numbers.size(); x++){
            std::vector<uint64_t>::iterator start =numbers.begin()+(x-preamble);
            std::vector<uint64_t>::iterator end =numbers.begin()+x;
            if(std::accumulate(start,end, decltype(numbers)::value_type(0)) == answer_part1){
                std::cout << "Part 2: " << *std::min_element(start, end)+*std::max_element(start, end) << std::endl;
            }
        }
    }
    
    return 0;
}
