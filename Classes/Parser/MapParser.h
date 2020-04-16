//
// Created by ebalo on 16/04/20.
//

#ifndef MILITARYCONQUEST_MAPPARSER_H
#define MILITARYCONQUEST_MAPPARSER_H

#include <memory>
#include <string>
#include <fstream>

class MapParser {
private:
    static void data_parser(const std::string &line, int *result, int &index, int size) {
        if (line.length() > 0 && line.c_str()[0] != '#') {
            int ch_value;
            for (char ch : line) {
                ch_value = ch - '0';
                if (ch_value >= 0 && ch_value <= 9 && index < size) {
                    result[index++] = ch_value;
                }
            }
        }
    }

public:
    static int *parse(const std::string &file_name, int size) {
        int index = 0,
                *result = new int[size];
        std::string line;

        std::fstream handle(file_name, std::fstream::in);
        if (handle.is_open()) {
            while (handle.good()) {
                getline(handle, line);
                data_parser(line, result, index, size);
            }
        }

        if (index < size) {
            delete[] result;
            throw std::runtime_error("Malformed map file read, required " + std::to_string(size) + " indices but " +
                                     std::to_string(index) + " given.");
        }
        return result;
    }

    static std::vector<int *> parseVariation(const std::string &file_name, int size) {
        int index = 0,
                *result = new int[size];
        std::vector<int *> packet;
        std::string line;
        bool variation_encountered = false,
                new_variation = false;

        std::fstream handle(file_name, std::fstream::in);
        if (handle.is_open()) {
            while (handle.good()) {
                if (new_variation) {
                    result = new int[size];
                    new_variation = false;
                }

                getline(handle, line);

                // Switch to parse only the variation
                if (!variation_encountered && line == "--VARIATION--") {
                    variation_encountered = true;
                    continue;
                }

                if (variation_encountered) {
                    data_parser(line, result, index, size);
                }

                if (index == size) {
                    packet.push_back(result);
                    new_variation = true;
                    index = 0;
                }
            }
        }

        if (packet.size() == 0 && index < size) {
            delete[] result;
            throw std::runtime_error(
                    "Malformed map variation read, required " + std::to_string(size) + " indices but " +
                    std::to_string(index) + " given.\nNo variation loaded.");
        } else if (index < size) {
            delete[] result;
            if (index != 0) {
                std::cerr << "Malformed map variation found (required " << size << " indices but " << index
                          << " given), " <<
                          "but variation vector is not empty, continuing with already parsed variations." << std::endl;
            }
        }
        return packet;
    }
};

#endif //MILITARYCONQUEST_MAPPARSER_H
