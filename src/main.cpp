#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <algorithm>

int alphabet_wizardry(char matched_char) {
    if (islower(matched_char)) {
        return matched_char - 'a' + 1;
    } else {
        return matched_char - 'A' + 27;
    }
}

char find_shared_character(std::string line0, std::string line1, std::string line2){
    size_t shortest_string = std::min({line0.size(),line1.size(),line2.size()});
    for (size_t i = 0; i < shortest_string; ++i) {
        char c = line0[i];

        if (line1.find(c) != std::string::npos && line2.find(c) != std::string::npos) {
            // If the character is found in both strings, return its ASCII value
            return c;
        }
    }
    for (size_t i = 0; i < line1.size(); ++i) {
        char c = line1[i];

        // Check if the character is present in the other two strings
        if (line0.find(c) != std::string::npos && line2.find(c) != std::string::npos) {
            // If the character is found in both strings, return it
            return c;
        }
    }

    // If no shared character is found in the first two strings, check the third string
    for (size_t i = 0; i < line2.size(); ++i) {
        char c = line2[i];

        // Check if the character is present in the other two strings
        if (line0.find(c) != std::string::npos && line1.find(c) != std::string::npos) {
            // If the character is found in both strings, return it
            return c;
        }
    }
    return '\0';
}

int char_matcher_one_pass(int border, std::string rucksack){
    for (int i = 0; i < border; i++){
        for(int j = 0; j < border; j++){
            if(rucksack[i] == rucksack[border + j]){
                return alphabet_wizardry(rucksack[i]);
            }
        }
    }
    throw std::runtime_error("No match found");
}

int main(){
    std::ifstream file("input.txt");
    if (file.is_open()) {
        std::string line;
        int priority = 0;
        int priority_part2 = 0;
        int compartment_border;
        std::vector<std::string> lines;
        
        while (std::getline(file, line)){
            lines.push_back(line);
            std::istringstream iss(line);
            compartment_border = line.size()/2;
            priority += char_matcher_one_pass(compartment_border, line);
        }
        std::vector<std::string> groups;
        for (int i = 0; i < lines.size() - 2; i += 3){
            groups.push_back(lines[i]);
            groups.push_back(lines[i+1]);
            groups.push_back(lines[i+2]);
        }
        char shared_char = '\0';
        std::cout<< "group size: "<<groups.size() << ::std::endl;
        for (int i = 0; i < groups.size()-2; i+=3){
            shared_char = find_shared_character(groups[i],groups[i+1],groups[i+2]);
            if (shared_char != '\0'){
                priority_part2 += alphabet_wizardry(shared_char);
            }
        }
        std::cout<< "Priority: "<< priority << std::endl;
        std::cout<< "Priority part 2: "<< priority_part2 << std::endl;
        
        file.close();
    } else {
        throw std::runtime_error("Unable to open file :(");
    }
    return 0;
}