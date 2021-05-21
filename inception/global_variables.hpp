#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iterator>
#include <list>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds


//You have to change this variables for personal use
std::string anton_ip = "anton@192.168.43.57";
std::string path_send_file = "data/user/friends/Anton/new/send/1.jpg";
std::string krik_mem = "PROJECT/Messenger/inception/data/user/friends/Anton/new/reciever/1.jpg";
std::string path_send_file_two = "data/user/friends/Anton/new/send/message.txt";
std::string krik_mem_two = "PROJECT/Messenger/inception/data/user/friends/ravil/new/reciever/message.txt";
//END 

#define path_to_like "../inception/data/image/like.jpg"
#define path_to_font "../inception/data/fonts/19413.ttf"
#define path_to_melody_one "../inception/data/sounds/icq.wav"
#define path_to_background "../inception/data/image/fon_memecria3.jpg"
#define path_to_sound "../inception/data/image/icon_sound.jpg"
#define path_to_mem "../inception/data/image/mem.jpg"
#define path_to_mem2 "../inception/data/image/mem2.jpg"
#define path_to_dante "../inception/data/image/dante.jpg"
#define path_to_send_image "../inception/data/image/send.png"
#define path_to_send_mem_image "../inception/data/image/send_mem.jpeg"
#define path_to_new_background "../inception/data/image/new_background.jpeg"
#define pers_settings_ava "../inception/data/image/pers_settings_ava1.png"
#define pers_settings_name_box "../inception/data/image/pers_settings_name_box.png"
#define pers_settings_password "../inception/data/image/pers_settings_password.png"
#define pers_settings_nickname "../inception/data/image/pers_settings_nickname.png"
#define pers_settings_info "../inception/data/image/pers_settings_info1.png"
#define pers_settings_melody_box "../inception/data/image/pers_settings_melody_box.png"
#define pers_settings_joke1 "../inception/data/image/pers_settings_joke1_1.png"
#define pers_settings_joke2 "../inception/data/image/pers_settings_joke2_1.png"
#define sign_friends "../inception/data/user/list_friend.txt"


char secret_path[] = "data/user/user.txt";
std::string two_secret_path = "data/user/user.txt";
std::string path_message = "data/user/friends";
//эти глобальные переменные необходимы для проигрывания саунда
//issue: add melody in global_variables
sf::Sound ringthone_one;
sf::SoundBuffer melody_one;
sf::Vector2u pos;
static const sf::Color Background_test = sf::Color(103, 154, 205);

short global_personal = 0;                                                      //enter personal_settings
short global_sign = 0;
short global_have = 1;
//check situate system
