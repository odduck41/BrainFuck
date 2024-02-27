#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <stack>
#include <queue>

int i = 0;
std::vector<char> line(300000, 0);
std::vector<char> commands;

bool parse(const std::string& program) {
    std::map<char, bool> allowed = {
        {'>', true},
        {'<', true},
        {'+', true},
        {'-', true},
        {'.', true},
        {',', true},
        {'[', true},
        {']', true},
    };

    for (auto& command: program) {
        if (allowed[command]) {
            commands.emplace_back(command);
        } else if (command != ' ' && command != '\r'
            && command != '\n' && command != '\t') {
            std::cerr << "Yes, it's BrainFuck! But what the shit are you doing?\n"
            << "Not allowed shit: " << command;
            return false;
        }
    }
    return true;
}

bool run() {
    std::stack<unsigned long long> circles;
    bool crcflg = true;
    for (auto command = 0ull; command < commands.size();) {
        if (crcflg && commands[command] == '>') {
            if (++i == commands.size()) {
                std::cerr << "Fuck you! The memory limit is " << line.size() << "!";
                return false;
            }
        } else if (crcflg && commands[command] == '<') {
            if (--i == -1) {
                std::cerr << "Fuck you! You try to reach the -1 memory cell. Are you idiot?\n"
                << "Or you just learn Python? The same things!";
                return false;
            }
        } else if (crcflg && commands[command] == '+') {
            if (line[i] == 127) {
                std::cerr
                << "You are fucking idiot! You try to set the cell value equal to 128!";
                return false;
            }
            ++line[i];
        } else if (crcflg && commands[command] == '-') {
            if (line[i] == 0) {
                std::cerr
                << "You are fucking idiot! You try to set the cell value equal to -1!";
                return false;
            }
            --line[i];
        } else if (crcflg && commands[command] == '.') {
            putchar(line[i]);
        } else if (crcflg && commands[command] == ',') {
            line[i] = static_cast<char>(getchar());
        } else if (commands[command] == '[') {
            circles.push(command);
            if (line[i] == 0) {
                crcflg = false;
            }
        } else if (commands[command] == ']') {
            if (circles.empty()) {
                std::cerr
                << "You are fucking idiot! You forgot start the circle...";
                return false;
            }
            if (line[i] != 0) {
                command = circles.top();
            } else {
                circles.pop();
            }
        }
        ++command;
    }
    if (!circles.empty()) {
        std::cerr
                << "You are fucking idiot! You forgot finish the circle...";
        return false;
    }
    return true;
}


int main(int argc, const char** argv) {
    std::ifstream is(argv[1]);
    std::string program;
    while (!is.eof()) {
        std::string ln;
        std::getline(is, ln);
        program += ln;
    }
    if (!parse(program)) {
        return 41;
    }
    if (!run()) {
        return 41;
    }
    return 0;
}
