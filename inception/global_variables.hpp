#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iterator>
#include <list>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

#define path_to_font "data/fonts/19413.ttf"
#define path_to_melody_one "data/sounds/sp-cheers.wav"
#define path_to_background "data/image/fon_memecria3.jpg"
#define path_to_sound "data/image/icon_sound.jpg"
#define path_to_mem "data/image/mem.jpg"
#define path_to_mem2 "data/image/mem2.jpg"
#define path_to_dante "data/image/dante.jpg"
#define path_to_new_background "data/image/new_background.jpeg"

//эти глобальные переменные необходимы для проигрывания саунда
//issue: add melody in global_variables
sf::Sound ringthone_one;
sf::SoundBuffer melody_one;
sf::Vector2u pos;
static const sf::Color Background_test = sf::Color(103, 154, 205);

short global_personal = 0;                                                      //enter personal_settings
short global_sign = 1;                                                          //check situate system
