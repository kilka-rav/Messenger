/*
#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iterator>


#define path_to_melody_one "data/sounds/sp-cheers.wav"
#define path_to_background "data/image/fon_memecria3.jpg"
#define path_to_sound "data/image/icon_sound.jpg"

//эти глобальные переменные необходимы для проигрывания саунда
//issue: add melody in global_variables //closed
sf::Sound ringthone_one;
sf::SoundBuffer melody_one;
sf::Vector2u pos;
*/

#pragma once

#include "global_variables.hpp"

namespace screen {
    class Background;
}


namespace screen {       // Everything required for screen operation is stored here 
    class Point {                                                                               // Class for storing information about a single 2D point
    private:
        double x, y;                                                                        // Coordinates
    public:
        Point(double _x, double _y) : x(_x), y(_y) {}                                       // Constructor
        Point() : x(0), y(0) {}                                                             // Another constructor
        sf::Vector2u getPoint();

        float getX() const;

        float getY() const;

        ~Point() {
            std::cout << "delete Point\n";
        }
    };                                                                                          //

    class Icons {                                                                               // Everything required for operations with images is stored here
    public:
        std::string path_to_image;                                                          // Path to the file containing image
        double height, width;                                                               // Image's height and width in pixels
        Point vertex;                                                                       // This point represents the upper left corner of the image
    public:                                                                                 //
        Icons(std::string path);                                                            // 3 different constructors
        Icons(std::string path, Point _vertex);                                             //
        Icons(std::string path, Point _vertex, double _height, double _width) : path_to_image(path), vertex(_vertex),
                                                                                height(_height), width(_width) {}

        void draw_object(sf::RenderWindow &wind); //add func //added
        bool click(sf::Vector2i position_mouse, Background &wind); //
        void display_text(sf::Event &event, sf::String player_input, sf::Text player_text);
        float Get_main_x();

        float Get_main_y();

        ~Icons() {
            std::cout << "delete Icons\n";
        }
    };

    class Button {                                                                              // Everything required for operations with buttons is stored here
    private:                                                                                //
        std::vector<Icons> Buttons;                                                         // Single vector contains information about all buttons
    public:                                                                                 //
        Button(Icons _icon);                                                                // 2 constructors
        Button();                                                                           //
        void insert(Icons icon);

        void draw_objects(sf::RenderWindow &wind);

        ~Button() {
            std::cout << "delete Button\n";
        }
    };                                                                                          //
    
    class Background {                                                                          // Class used for operations with background
    private:                                                                                //
        sf::RenderWindow window;                                                          // Reference: https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1RenderWindow.php
    public:
        void play_sound(); // Different functions used for interaction with the active window
        //void my_clear();
    private:
        sf::Vector2u Begin_size;
        float kx;
        float ky;
    public:                                                                                 //
        Background(int height, int width) : window(sf::VideoMode(height, width), "MEMECRIA"), kx(1), ky(1),
                                            Begin_size(sf::Vector2u(height, width)) {}

        Background(int height, std::string name, int width) : window(sf::VideoMode(height, width), name), kx(1), ky(1),
                                                              Begin_size(sf::Vector2u(height, width)) {}
        void draw_on_window(sf::Text args, std::string str);
        void draw_on_window(const char path_to_image[]);                                    //
        void draw_on_window(const char path_to_image[], int x, int y);                      //
        void draw_on_window(sf::Color colour);
        void draw_on_window(std::string str, sf::Font font);

        void draw_on_window(std::string text, int pixel_size, sf::Vector2f position);//
        void handler_button_start();                                                              //
        void handler_button();

        bool is_open();                                                               //
        void display();                                                                     //
        void enter_button_start(sf::Vector2i vec);                                                //
        void my_clear();

        sf::RenderWindow &Get_window();

        float Get_kx() const;

        float Get_ky() const;

        //void close_window();
        ~Background() {
            std::cout << "delete Background\n";
        }
    };

    sf::Vector2u Point::getPoint() {
        return sf::Vector2u(x, y);
    }

    float Point::getX() const {
        return x;
    }

    float Point::getY() const {
        return y;
    }

    Icons::Icons(std::string path, Point _vertex) {
        sf::Texture image;
        image.loadFromFile(path);
        sf::Vector2u pos = image.getSize();
        path_to_image = path;
        std::cout << path_to_image << "  92\n";
        vertex = _vertex;
        height = pos.y;
        width = pos.x;
    }

    Icons::Icons(std::string path) {
        Point p(0, 0);
        //std::cout << "99 " << path << std::endl; //WORK
        sf::Texture image;
        image.loadFromFile(path);
        sf::Vector2u pos = image.getSize();
        path_to_image = path;
        //std::cout << path_to_image << "  106\n"; //WORK
        vertex = p;
        height = pos.y;
        width = pos.x;
    }

    float Icons::Get_main_x() {
        sf::Vector2u p = vertex.getPoint();
        return p.x;
    }

    float Icons::Get_main_y() {
        sf::Vector2u p = vertex.getPoint();
        return p.y;
    }

    bool Icons::click(sf::Vector2i position_mouse, screen::Background &window) {
        //if you click on Icons -> return true -> action_one
        //else return false ->non_action
        float X = position_mouse.x;
        float Y = position_mouse.y;
        float kx = window.Get_kx();
        float ky = window.Get_ky();
        float main_x = static_cast<float>(vertex.getX());
        float main_y = static_cast<float>(vertex.getY());
        if ( (X > main_x * kx) & (X < (main_x + width) * kx) & (Y > main_y * ky) & (Y < (main_y + height) * ky) ) {
            return true;
        }
        else if ( (X < main_x * kx) | (X > (main_x + width) * kx) | (Y < main_y * ky) | (Y > (main_y + height) * ky) ) {
            return false;
        }
        return false;
    }

    void Button::insert(Icons icon) {
        Buttons.push_back(icon);
    }

    void Icons::draw_object(sf::RenderWindow &wind) {
        sf::Texture image;
        image.loadFromFile(path_to_image);
        sf::Sprite sprite_image;
        sprite_image.setTexture(image);
        sprite_image.setPosition(vertex.getPoint().x, vertex.getPoint().y);
        wind.draw(sprite_image);
    }

    void Icons::display_text(sf::Event &event, sf::String player_input, sf::Text player_text) {
        if(event.type == sf::Event::TextEntered){
            if(event.text.unicode < 128){
                player_input += event.text.unicode;
                player_text.setString(player_input);
            }
        }
    }


    Button::Button() {
        Icons _icon = {0};
        Buttons.push_back(_icon);
    }

    Button::Button(Icons _icon) {
        Buttons.push_back(_icon);
    }

    void Button::draw_objects(sf::RenderWindow &window) { //add func
        for (Icons It : Buttons) {
            It.draw_object(window);
            std::cout << It.path_to_image << std::endl;;
        }
    }

    sf::RenderWindow &Background::Get_window() { //add func
        sf::RenderWindow &wind = window;
        return wind;
    }
    
    void Background::draw_on_window(std::string str, sf::Font font) {
        str = "\t\t" + str;
        sf::Text text(str, font);
        text.setFont(font);
        text.setCharacterSize(30);
        text.setStyle(sf::Text::Bold);
        text.setFillColor(sf::Color::Black);
    }

    void Background::draw_on_window(sf::Text text, std::string str) {
        window.clear();
        //sf::Text text(str, font);
        //text.setFont(font);
        //text.setCharacterSize(30);
        //text.setStyle(sf::Text::Bold);
        //text.setFillColor(sf::Color::Black);
        window.draw(text);
        window.display();
    }

    void Background::draw_on_window(const char path_to_image[]) {
        sf::Texture image;
        image.loadFromFile(path_to_image);
        sf::Sprite sprite_image;
        sprite_image.setTexture(image);
        sprite_image.setPosition(0, 0);
        window.draw(sprite_image);
    }

    void Background::draw_on_window(const char path_to_image[], int x, int y) {
        sf::Texture image;
        image.loadFromFile(path_to_image);
        sf::Sprite sprite_image;
        sprite_image.setTexture(image);
        sprite_image.setPosition(x, y);
        window.draw(sprite_image);
    }

    void Background::draw_on_window(sf::Color colour) {
        window.clear(colour);
    }

    void Background::draw_on_window(std::string text, int pixel_size, sf::Vector2f position) {
        sf::Text title;
        sf::Font font;
        font.loadFromFile(path_to_font);
        title.setFont(font);
        title.setString(text);
        title.setFillColor(sf::Color::Black);
        title.setCharacterSize(pixel_size);
        title.setPosition(position);
        title.setStyle(sf::Text::Bold);
        window.draw(title);
        //window.display();
    }

    void Background::my_clear() {
        window.clear();
        window.close();
        window.display();
    }

    float Background::Get_kx() const {
        return kx;
    }

    float Background::Get_ky() const {
        return ky;
    }

    void Background::handler_button() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            //                                                  Issue:add Key_pressed for func
        }
    }


    void Background::handler_button_start() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                play_sound();
            } else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                //std::cout << "LEFT CLICK" << std::endl;
                sf::Vector2i position_mouse = sf::Mouse::getPosition(window);
                //std::cout << position_mouse.x << "= x\n" << position_mouse.y << "= y\n" << std::endl;
                enter_button_start(position_mouse);
            }
        }
    }

    bool Background::is_open() {
        //sf::Vector2u posic = window.getSize();
        pos = window.getSize();
        kx = pos.x / (static_cast<float> (Begin_size.x));
        ky = pos.y / (static_cast<float> (Begin_size.y));
        /*if ( ( kx != 1 ) & ( ky != 1 ) ) {                //TEST
            std::cout << "kx " << kx << "\nBegin_size x " << Begin_size.x << "\npos x " << pos.x << std::endl;
            std::cout << "ky " << ky << "\nBegin_size y " << Begin_size.y << "\npos y " << pos.y << std::endl;
        }
        */
        return window.isOpen();
    }

    void Background::display() {
        window.display();
    }

    /*
    //эти глобальные переменные необходимы для проигрывания саунда
    //issue: add melody in global_variables
    sf::Sound ringthone_one;
    sf::SoundBuffer melody_one;
    */
    void Background::play_sound() {
        if (!melody_one.loadFromFile(path_to_melody_one)) {
            std::cout << "ERROR. Melody_one isn't detected\n" << std::endl;
        }
        ringthone_one.setBuffer(melody_one);
        ringthone_one.play();
    }

/*
    sf::RenderWindow Background::getWindow() {
        return &window;
    }
*/
    void Background::enter_button_start(sf::Vector2i position) {
        float X = position.x;
        float Y = position.y;
        //add kx, ky in methods
        float kx = pos.x / 1240.0;
        float ky = pos.y / 800.0;
        //std::cout << kx << " = kx\n" << ky << " = ky\n";
        if ((X > 345 * kx) & (Y > 70 * ky) & (X < 965 * kx) & (Y < 175 * ky)) {
            std::cout << "SIGN IN/SIGN UP\n";
            global_sign = 1;                                                                    //add BT
        } 
        else if ((X > 340 * kx) & (Y > 210 * ky) & (X < 975 * kx) & (Y < 285 * ky)) {
            std::cout << "PERSONAL SETTINGS\n";
            global_personal = 1;
            //std::cout << global_personal << std::endl;
        }

    }
}

