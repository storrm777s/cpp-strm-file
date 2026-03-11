#include <iostream>
#include <fstream>
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

const std::string EXTENSION = ".strm";

//void print(std::string msg) { std::cout << "//////////////////" << '\n' << msg << '\n'; }

struct Vector5 {
    int x;
    int y;
    int r;
    int g;
    int b;
};

struct varDef {
    //int length;
    std::string data;
};

 struct varDefPixel {
    Vector5 data;
};

struct STRM {
    varDef title;
    int sizex;
    int sizey;

    std::vector<varDefPixel> pixels;
};

STRM CreateTemplate() {
    STRM t;

    return t;
};

std::ifstream getFile(const std::string& filename) {
    std::string name = filename + EXTENSION;

    std::ifstream file(name);
    if (!file.is_open()) {
        std::ofstream create(name);
        create.close();
        file.open(name);
    }

    return file;
};

std::string extractData(std::string sum, std::string id) {
    size_t pos = 0;
    size_t endpos = 0;
    pos = sum.find(id)+id.length();
    if (pos != std::string::npos) {
        endpos = sum.find("]", pos);
        return sum.substr(pos, endpos - pos);
    }
    return std::string("ERROR");
}

void extractPdData(std::string sum, STRM& img) {

    size_t pos;
    pos = sum.find("PD[", 0);
    while ((pos = sum.find("PD[", pos)) != std::string::npos) {
        varDefPixel t;
        t.data.x = stoi(sum.substr(pos+3, sum.find("'", pos) - pos-3));
        pos += sum.find("'", pos) - pos+1;
        t.data.y = stoi(sum.substr(pos, sum.find(":", pos) - pos));
        pos += sum.find(":", pos) - pos+1;
        t.data.r = stoi(sum.substr(pos, sum.find(",", pos) - pos));
        pos += sum.find(",", pos) - pos+1;
        t.data.g = stoi(sum.substr(pos, sum.find(",", pos) - pos));
        pos += sum.find(",", pos) - pos+1;
        t.data.b = stoi(sum.substr(pos, sum.find(",", pos) - pos));
        pos += 3;
        img.pixels.push_back(t);
    }
}

int main() {
    std::ifstream file = getFile("rawdata");

    if (!file.is_open()) {
        printf("File failed to open, return.\n");
        return 0;
    }

    std::string sum = "";
    std::string line = "";

    while (getline(file, line)) {
        sum.append(line + '\n');
    }

    STRM img = CreateTemplate();

    img.title.data = extractData(sum, "title:");
    img.sizex = stoi(extractData(sum, "sizex:"));
    img.sizey = stoi(extractData(sum, "sizey:"));
    // std::cout << img.title.data << '\n';
    // std::cout << img.sizex.data << '\n';
    // std::cout << img.sizey.data << '\n';
    
    img.pixels.reserve(img.sizex * img.sizey);
    extractPdData(sum, img);

    sf::RenderWindow window(sf::VideoMode({static_cast<u_int>(img.sizex), static_cast<u_int>(img.sizey)}), img.title.data, sf::Style::Default);

    window.setPosition({500, 500});

    window.setFramerateLimit(60);

    while (window.isOpen()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape)
        && window.hasFocus()) {
            window.close();
        }

        window.clear(sf::Color::Black);

        for (auto& pixel : img.pixels) {
            sf::VertexArray pixeldrawn(sf::PrimitiveType::Points, 1);
            pixeldrawn[0].position = sf::Vector2f(pixel.data.x, pixel.data.y);
            pixeldrawn[0].color = sf::Color(pixel.data.r, pixel.data.g, pixel.data.b);
            window.draw(pixeldrawn);
        }

        window.display();
    }

    return 0;
};