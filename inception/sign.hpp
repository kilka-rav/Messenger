#pragma once

#include "global_variables.hpp"
#include <fstream>
#include <iostream>
#include "textbox.hpp"
#include "send.hpp"
#define print(s) std::cout << s << std::endl;



void open_telegramm(std::string s);


void my_open() {
    sf::Font font;
    font.loadFromFile(path_to_font);
    system("python3 walk.py");
    std::string line;
    std::vector<std::string> friends;
    std::vector<screen::Icons> friends_icons;
    std::ifstream in(sign_friends);
    if ( in.is_open() ) {
        while (getline(in, line)) {
            friends.push_back(line);
        }
    }
    for(int i = 0; i < friends.size(); ++i) {
        friends_icons.push_back(screen::Icons(pers_settings_ava, screen::Point(i * 250, 0)));
    }
    screen::Background window(1240, "MEMECRIA", 740);
    while (window.is_open()) {
        window.draw_on_window(Background_test);
        sf::Event event;
        while (window.Get_window().pollEvent(event)) {
            window.handler_button();
            if (event.type == sf::Event::Closed) {
                window.Get_window().close();
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i position_mouse = sf::Mouse::getPosition(window.Get_window());
                for(int i = 0; i < friends_icons.size(); ++i) {
                    if (friends_icons[i].click(position_mouse, window) == true) {
                        //window.Get_window().close();
                        open_telegramm(friends[i]);
                    }
               }
            }
        }
        for(int i = 0; i < friends_icons.size(); ++i) {
            friends_icons[i].draw_object(window.Get_window());
            sf::Text text(friends[i], font);
            text.setFont(font);
            text.setCharacterSize(30);
            text.setStyle(sf::Text::Bold);
            text.setFillColor(sf::Color::Black);
            text.setPosition(50 + 250 * i, 200);
            window.Get_window().draw(text);
        }
        window.display();
    }
}



class Textbox_t {
    private:
        const sf::Font* font;
        sf::RectangleShape box;
        sf::Text text;
        sf::String text_s;
        bool textChanged;
    public:
        Textbox_t() = default;
        Textbox_t(sf::Text& suggestion);
        void draw(sf::RenderWindow& window);
        std::string get_text();
        void update(sf::Event& event);
};

Textbox_t::Textbox_t(sf::Text& suggestion) {
    sf::FloatRect bounds(suggestion.getGlobalBounds());
    box.setSize({bounds.width, bounds.height});
    box.setFillColor(sf::Color::White);
    sf::Vector2f origin(box.getSize().x / 2, box.getSize().y / 2);
    box.setOrigin(origin);
    sf::Vector2f position(suggestion.getPosition().x, suggestion.getPosition().y + 2 * origin.y);
    box.setPosition(position);

    font = suggestion.getFont();
    text.setFillColor(sf::Color::Black);
    unsigned int default_char_size = static_cast<unsigned int>(suggestion.getCharacterSize() * 0.7);
    text.setCharacterSize(default_char_size);
    text.setOrigin({0, origin.y});
    text.setPosition({bounds.left, position.y});
}

void Textbox_t::draw(sf::RenderWindow& window) {
    text.setFont(*font);
    text.setString(text_s);
    float text_width = text.getLocalBounds().width;
    float box_width = box.getLocalBounds().width;
    float factor = (text_width >= box_width) ? (0.94 * box_width / text_width) : 1;
    text.setScale(factor, factor);
    window.draw(box);
    window.draw(text);
}

std::string Textbox_t::get_text() {
    return text.getString().toAnsiString();
}

void Textbox_t::update(sf::Event& event) {
    switch ( event.text.unicode ) {
        case 0x8://Backspace
            if ( !text_s.isEmpty() ) {
                text_s.erase(text_s.getSize()-1) ;
                break;
            }
        default :
            text_s += static_cast<wchar_t>(event.text.unicode) ;
    }
}


void sign_reg() {
    int i = 0;
    screen::Background sign(1240, "SIGN", 700);
    std::vector<std::string> strings;
Label:    
    sf::Font font;
    bool isEnter = true;
    font.loadFromFile(path_to_font);
    sf::Text suggestion;
    suggestion.setFont(font);
    suggestion.setFillColor(sf::Color::Black);
    suggestion.setStyle(sf::Text::Bold);
    suggestion.setCharacterSize(60);
    suggestion.setOrigin(suggestion.getLocalBounds().width / 2, suggestion.getLocalBounds().height);
    float v_padding = suggestion.getLocalBounds().height;
    suggestion.setPosition(100, 100);
    Textbox_t textbox(suggestion);
    while (sign.is_open() && isEnter) {
        sf::Event event;
        while(sign.Get_window().pollEvent(event)) {
            switch(event.type) {
                case sf::Event::Closed:
                    sign.Get_window().close();
                    break;
                case sf::Event::KeyPressed:
                    if ( event.key.code == sf::Keyboard::Escape )
                        isEnter = false;
                        break;
                    case sf::Event::TextEntered:
                        switch (event.text.unicode) {
                            case 0xD:
                                std::cout << "ENTER 29\n";
                                if ( i < 6 ) {
                                    ++i;
                                    strings.push_back(textbox.get_text());
                                    goto Label;
                                }
                                else {
                                    break;
                                }
                            default:
                                textbox.update(event);
                        }
            }
        }
        sign.draw_on_window(Background_test);
        if ( i == 0 )
            sign.draw_on_window("Enter Name", 30, sf::Vector2f(100, 100));
        if ( i == 1 )
            sign.draw_on_window("Enter info", 30, sf::Vector2f(100, 100));
        if ( i == 2 ) 
            sign.draw_on_window("Enter nickname", 30, sf::Vector2f(100, 100));
        if ( i == 3 ) 
            sign.draw_on_window("Enter path to ava", 30, sf::Vector2f(100, 100));
        if ( i == 4 )
            sign.draw_on_window("Enter password", 30, sf::Vector2f(100, 100));
        if ( i == 5 )
            sign.draw_on_window("Enter path_to_melody", 30, sf::Vector2f(100, 100));
        if ( i == 6 ) 
            break;
        sign.Get_window().draw(suggestion);
        sf::Text text(textbox.get_text(), font);
        text.setFont(font);
        text.setCharacterSize(30);
        text.setStyle(sf::Text::Bold);
        text.setFillColor(sf::Color::Black);
        sign.Get_window().draw(text); //add method in class Background
        sign.Get_window().draw(suggestion);
        textbox.draw(sign.Get_window());
        sign.display();
    }
    sign.my_clear();
    User data(strings[0], strings[1], strings[2], strings[3], strings[4], strings[5]);
    data.write(secret_path);
    for(int i = 0; i < strings.size(); ++i) {
        std::cout << strings[i] << " ";
    }
    std::cout << std::endl;
    my_open();
}

/*
void sign_reg() {
    std::ofstream File;
    std::string s1, s2, s3, s4, s5, s6;
    screen::Background sign(1240, "SIGN", 700);
    sf::Font font;
    font.loadFromFile(path_to_font);
    sf::Text text("", font);
    text.setFont(font);
    text.setCharacterSize(30);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::Black);
    Textbox_t textbox(text);
    global_sign = 1;
    while (sign.is_open()) {
        sign.display();
        sign.handler_button();
        sf::Event event;
        while(sign.Get_window().pollEvent(event)) {
            switch(event.type) {
                case sf::Event::Closed:
                    sign.my_clear();
                    break;
                case sf::Event::KeyPressed:
                    if ( event.key.code == sf::Keyboard::Escape )
                        break;
                    case sf::Event::TextEntered:
                        switch (event.text.unicode) {
                            case 0xD:
                                std::cout << "ENTER 29\n";
                                //next_str
                                break;
                            default:
                                textbox.update(event);
                        }
            }
        }
    }
}
*/
/*

        sign.draw_on_window(Background_test);
        sign.display();
        sign.handler_button();
        if ( !AnalyseWait_Text_User (sign.Get_window(), s1, user_text))
            break;
        sign.draw_on_window(user_text.for_draw(), user_text.get_text());
    }
}
*/

/*
void sign_reg() {
    std::ofstream File;
    std::vector<std::string> info_user;
    int num_strings = 6;
    std::string s1, s2, s3, s4, s5, s6;
    std::cout << "ENTER_NAME\n";
    std::cin >> s1;
    std::cout << "ENTER_INFO\n";
    std::cin >> s2; 
    std::cout << "ENTER_NICKNAME\n";
    std::cin >> s3;
    std::cout << "ENTER_PATH_TO_AVA\n";
    std::cin >> s4;
    std::cout << "ENTER_PASSWORD\n";
    std::cin >> s5;
    std::cout << "ENTER_PATH_TO_MELODY\n";
    std::cin >> s6; 
    User data(s1, s2, s3, s4, s5, s6);
    data.write(secret_path);
    //my_open();                    OPEN MAIN WINDOW
    sf::Font font;
    font.loadFromFile(path_to_font);
    screen::Background sign(1240, "SIGN", 700);
    global_sign = 1;
    while (sign.is_open()) {
        sign.display();
        sign.draw_on_window(Background_test);
        sign.handler_button();
    }

}
*/


void sign_enter() {
    std::string s1, s2, buffer;
    screen::Background sign(1240, "SIGN", 700);
    User personal;
    personal.read(secret_path);
    s2 = personal.get_password();
    sf::Font font;
    bool isEnter = true;
    font.loadFromFile(path_to_font);
    sf::Text suggestion;
    suggestion.setFont(font);
    suggestion.setFillColor(sf::Color::Black);
    suggestion.setStyle(sf::Text::Bold);
    suggestion.setCharacterSize(60);
    suggestion.setOrigin(suggestion.getLocalBounds().width / 2, suggestion.getLocalBounds().height);
    float v_padding = suggestion.getLocalBounds().height;
    suggestion.setPosition(100, 100);
    Textbox_t textbox(suggestion);
    while (sign.is_open() && isEnter) {
        sf::Event event;
        while(sign.Get_window().pollEvent(event)) {
            switch(event.type) {
                case sf::Event::Closed:
                    sign.Get_window().close();
                    break;
                case sf::Event::KeyPressed:
                    if ( event.key.code == sf::Keyboard::Escape )
                        isEnter = false;
                        break;
                    case sf::Event::TextEntered:
                        switch (event.text.unicode) {
                            case 0xD:
                                std::cout << "ENTER 29\n";
                                isEnter = false;
                            default:
                                textbox.update(event);
                        }
                    }
        }
        sign.draw_on_window(Background_test);
        sign.draw_on_window("Enter PASSWORD", 30, sf::Vector2f(100, 100));
        sign.Get_window().draw(suggestion);
        sf::Text text(textbox.get_text(), font);
        text.setFont(font);
        text.setCharacterSize(30);
        text.setStyle(sf::Text::Bold);
        text.setFillColor(sf::Color::Black);
        //ign.Get_window().draw(text); //add method in class Background
        sign.Get_window().draw(suggestion);
        textbox.draw(sign.Get_window());
        sign.display();
    }
    sign.my_clear();
    s1 = textbox.get_text();
    s1.pop_back();
    if ( s1 == s2 ) {
        std::cout << "PASSWORD OK\n";
        my_open();
    }
    else {
        std::cout << "ERROR IN PASSWORD\n" << s1 << std::endl << s2 << "SIZE get_pass " << s1.length() << std::endl;
    }
}



void open_telegramm(std::string name) {
    sf::Font font;
    User personal;
    personal.read(secret_path);
    std::string name_str = personal.name + ": ";
   
    //std::vector<std::string> strings;
    //strings.push_back(name_str);
    font.loadFromFile(path_to_font);
    int A = 100, B = 100;
    std::string s3;
    int count2 = 0;
    int count = 0;
    std::vector<std::string> strings;
    //strings.push_back(name_str);
    sf::Text suggestion;
    suggestion.setFont(font);
    suggestion.setFillColor(sf::Color::Black);    
    suggestion.setStyle(sf::Text::Bold);
    suggestion.setCharacterSize(60);
    
    std::string s1, s2;
   // suggestion.setOrigin(suggestion.getLocalBounds().width / 2, suggestion.getLocalBounds().height);
    float v_padding = suggestion.getLocalBounds().height;
    
    suggestion.setPosition(A, B);
    
    screen::Background window(1240, name, 740);
    screen::Icons send(path_to_send_image, screen::Point(1080, 600));
    screen::Icons send_mem(path_to_send_mem_image, screen::Point(1000, 500));
    int flag = 0;
    int flag_two = 0;
    suggestion.setPosition(A, 200);    
    Textbox_t textbox(suggestion);
    bool isEnter = true; 
    while (window.is_open() && isEnter ) {
	    window.draw_on_window(Background_test);
        send.draw_object(window.Get_window());
        send_mem.draw_object(window.Get_window());
        sf::Event event;
        while (window.Get_window().pollEvent(event))  {
            if (event.type == sf::Event::Closed ) {
                window.Get_window().close();
                break;
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    sf::Vector2i position_mouse = sf::Mouse::getPosition(window.Get_window());
                    if ( ( send.click(position_mouse, window) == true ) && (flag == 0) ) {
                    //message
                        std::cout << "flag = 1\n";
                        flag = 1;
                    }
                    else if ( (send.click(position_mouse, window) == true ) && (flag == 1) ) {
                        flag = 0;
                        std::cout << "flag = 0\n";
                        std::cout << "check: 415 "<< strings[0];
                        write_file_send(strings, name);
                        //send_friend_SSH
                    }
                    else if ( (send_mem.click(position_mouse, window) == true) && ( flag_two == 0 )) {
                        flag = 1;
                        flag_two = 1;
                    }
                    else if ( (send_mem.click(position_mouse, window) == true) && ( flag_two == 2 ) ) {
                        write_mem_send(strings[strings.size() - 1], name);
                        //send_friend_SSH
                    }
            }
            if ( flag == 1 ) {
                switch(event.type) {
                    case sf::Event::Closed:
                        window.Get_window().close();
                        break;
                    case sf::Event::KeyPressed:
                        if ( event.key.code == sf::Keyboard::Escape )
                            isEnter = false;
                            break;
                    case sf::Event::TextEntered:
                        switch (event.text.unicode) {
                            case 0xD:
                                std::cout << "ENTER 29\n";
                                if ( flag_two == 1 ) {
                                    flag_two = 2;
                                }
                                
                                strings.push_back(name_str + textbox.get_text());
                                print("check");
                                std::cout << strings[0] << std::endl;
                            default:
                                textbox.update(event);
                        }
                    }



            }
        
            
            
        
            

        }
        window.Get_window().draw(suggestion);
        if ( flag == 2 ) {
            B += 30;
            s1 = name_str;
            flag = 0;
            count = textbox.get_text().length();
        }

        else {
            s1 = "TYPE: " + textbox.get_text();
        }
       
        for(int i = 0; i < strings.size(); ++i) {
            window.draw_on_window(strings[i], 30, sf::Vector2f(0, 30 + (i)* 30)); 
            //std::cout << "size = " << strings.size() << std::endl;
        }
        
        sf::Text text(s1, font);
        //window.draw_on_window(s1, 30, sf::Vector2f(0, B));
        text.setFont(font);
        text.setCharacterSize(30);
        text.setStyle(sf::Text::Bold);
        text.setFillColor(sf::Color::Black);
        window.Get_window().draw(text);
        window.Get_window().draw(suggestion);
        textbox.draw(window.Get_window());
        window.display();
    }
    /*
    for(int i = 0; i != strings.size(); ++i) {
        std::cout << strings[i];

    }
    */
    window.my_clear();
}


/*


void sign() {
    std::ofstream File;
    std::vector<std::string> info_user;
    sf::Font font;
    font.loadFromFile(path_to_font);

    int i = 0, counter = 0;

    std::vector<sf::Vector2f> positions;
    positions.reserve(6);
    for (int j = 0; j < 6; ++j) {
        positions.emplace_back(sf::Vector2f(350, 50 + 50 * j));
        info_user.emplace_back("");
    }
    Textbox_t textbox_input(font, 45, false, positions[0], 15);
    bool flag = false;

    screen::Background sign(1240, "SIGN", 700);
    while (sign.is_open()) {
        sign.display();
        sign.handler_button();
        sign.draw_on_window(Background_test);
        sign.draw_on_window("Name:", 45, sf::Vector2f(50, 50));
        sign.draw_on_window("Information:", 45, sf::Vector2f(50, 100));
        sign.draw_on_window("Nickname:", 45, sf::Vector2f(50, 150));
        sign.draw_on_window("Avatar:", 45, sf::Vector2f(50, 200));
        sign.draw_on_window("Password:", 45, sf::Vector2f(50, 250));
        sign.draw_on_window("Melody:", 45, sf::Vector2f(50, 300));

        sf::Event event;

        // TODO: add click icons
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
            textbox_input.setSelected(true);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            if (counter < 6 && !textbox_input.check_symbols() && !textbox_input.getText().empty()) {
                counter++;
                textbox_input.setSelected(false);
                info_user[i] = textbox_input.getText();
                textbox_input.erase_text();
                i++;
                textbox_input.setPosition(positions[i]);
                textbox_input.setSelected(true);
                sign.Get_window().display();
                continue;
            } else if (counter == 6) {
                textbox_input.setSelected(false);
                flag = true;
            }
        }

        while (sign.Get_window().pollEvent(event)) {
            switch (event.type) {
                case sf::Event::TextEntered:
                    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                        textbox_input.type_text(event);
                        std::cout << textbox_input.getText() << std::endl;
                    }
            }
        }
        textbox_input.draw(sign.Get_window());
        sign.draw_on_window(info_user[0], 45, sf::Vector2f(350, 50));
        sign.draw_on_window(info_user[1], 45, sf::Vector2f(350, 100));
        sign.draw_on_window(info_user[2], 45, sf::Vector2f(350, 150));
        sign.draw_on_window(info_user[3], 45, sf::Vector2f(350, 200));
        sign.draw_on_window(info_user[4], 45, sf::Vector2f(350, 250));
        sign.draw_on_window(info_user[5], 45, sf::Vector2f(350, 300));
        sign.Get_window().display();
        if (flag)
            break;

        //}
        *
        std::cout << "Enter name\n";
        std::cin >> s1;
        std::cout << " Enter information\n";
        std::cin >> s2;
        std::cout << " Enter nickname\n";
        std::cin >> s3;
        std::cout << " Enter avatar\n";
        std::cin >> s4;
        std::cout << " Enter password\n";
        std::cin >> s5;
        std::cout << "Enter melody\n";
        std::cin >> s6;
        a = 1;
    }

    User personal(info_user[0], info_user[1], info_user[2], info_user[3], info_user[4], info_user[5]);
    personal.write(two_secret_path);
    global_sign = 0;

}
*/
/*
void sign() {
    std::ofstream File(secret_path);
    sf::Font font;
    font.loadFromFile(path_to_font);
    int i = 0, counter = 0;
    screen::Background sign(1240, "SIGN", 700);
    sign.draw_on_window(Background_test);
    screen::Icons next_icon(pers_settings_info, screen::Point(50,50));       // add picture
    screen::Icons buffer(pers_settings_info, screen::Point(300, 300)); // add picture
    next_icon.draw_object(sign.Get_window());
    buffer.draw_object(sign.Get_window());
    std::string s1, s2, s3, s4, s5, s6;
    print(120);
    sign.display();
    while ( sign.is_open() ) {
        //sign.display();
        //print(124);
        //sign.handler_button();
        if ( counter == 0 ) {
            Textbox_t textbox_input(font, 25, false, sf::Vector2f(100, 100), 15);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i position_mouse = sf::Mouse::getPosition(sign.Get_window());
                print(130);
                while ( next_icon.click(position_mouse, sign) != true ) {
                //Textbox_t texbox_input(font, 25, false, sf::Vector2f(100, 100), 15);
                    sf::Event event;
                    position_mouse = sf::Mouse::getPosition(sign.Get_window());
                    //std::cout << "X = " << position_mouse.x << "Y " << position_mouse.y << std::endl;
                    sign.handler_button();
                    //print(136);
                    sign.display();
                    if ( buffer.click(position_mouse, sign) == true ) {
                        while( buffer.click(position_mouse, sign) != false ) {
                            textbox_input.setSelected(true); //start to enter
                            position_mouse = sf::Mouse::getPosition(sign.Get_window());
                            print(142);
                            while ( sign.Get_window().pollEvent(event) ) {
                                if ( sf::Event::TextEntered ) {
                                    textbox_input.type_text(event);
                                    print(146);
                                    sign.handler_button();
                                    sign.display();
                                }
                            }   
                            std::cout << textbox_input.getText() << " : TEXT 137 __LINE\n";
                            s1 = textbox_input.getText();
                        }   
                    }
                }
                counter++;
            }
        }
    }
}
                        //ENTER STRING
*/

