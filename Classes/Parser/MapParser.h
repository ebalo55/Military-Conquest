//
// Created by ebalo on 16/04/20.
//

#ifndef MILITARYCONQUEST_MAPPARSER_H
#define MILITARYCONQUEST_MAPPARSER_H

#include <string>
#include <fstream>

class MapParser {
public:
    static int *parse(std::string file_name, int size) {
        int index = 0,
            result[size];
        std::string line;

        std::fstream handle(file_name, std::fstream::in);
        if(handle.is_open()) {
            while(handle.good()) {
                getline(handle, line);
                if(line.length() > 0 && line.c_str()[0] != '#') {
                    int ch_value;
                    for(char ch : line) {
                        ch_value = ch - '0';
                        if(ch_value <= 9) {
                            result[index++] = ch_value;
                        }
                    }
                }
            }
        }

    }
};

#endif //MILITARYCONQUEST_MAPPARSER_H
