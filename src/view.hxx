#pragma once

#include "model.hxx"
#include "ge211.hxx"
#include <string>

using Color = ge211::Color;

class View
{
public:
    explicit View(Model const&);

    void draw(ge211::Sprite_set& set);

    ge211::Dimensions initial_window_dimensions() const;

    std::string initial_window_title() const;
    Position screen_to_board(Position p) const;
    Position board_to_screen(Position p) const;
    Position paus_pos();
    Position paus_button_pos();

private:
    std::string highscore_string = "high score: "+ std::to_string(0);
    static int const grid_size = 25;

    Model const& model_;
    //board const& board_;

    ge211::Color    boarder_c = {26,30 ,56}, // darkblue
                    snake_c = {124,252,0}, // lawngreen
                    blue_f_c = {30,144,255}, // dodgerblue
                    mouse_c = {169,169,169}, // darkgray
                    red_f_c = {255,0,0}; // red

    ge211::Rectangle_sprite     snake_ {{grid_size-2,grid_size-2}, snake_c},
                                boarder_{{grid_size,grid_size}, boarder_c},
                                blue_f {{grid_size - 2,grid_size-2}, blue_f_c},
                                mouse_f {{grid_size - 2,grid_size-2}, mouse_c},
                                red_f {{grid_size - 2,grid_size-2}, red_f_c};

    ge211::Image_sprite pause_ {"pause.png"};
    ge211::Image_sprite food_type_ {"food_type.png"};
    ge211::Image_sprite pause_button {"pause_button_1.png"};

    ge211::Font g = ge211::Font("sans.ttf",15);
    ge211::Text_sprite::Builder built {ge211::Font("sans.ttf",15)};

    ge211::Text_sprite dead{"woah ur ded", g};
    ge211::Text_sprite highscore {" ",g};




    Position disp_pos(Position p);
    //Position paus_pos();
    //Position paus_button_pos();
};
