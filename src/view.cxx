#include "view.hxx"

using Dimensions = ge211::Dimensions;
using Position   = ge211::Position;
using Color      = ge211::Color;
using Sprite_set = ge211::Sprite_set;

// You can change this or even determine it some other way:
static int const grid_size = 36;


View::View(Model const& model)
        : model_(model)


{}

void View::draw(ge211::Sprite_set &set)
{

    for(unit u : model_.board_().screen)
    {
        Position pos = disp_pos(u.get_pos());
        if (u.is_snake())
        {
            set.add_sprite(snake_,pos);
        } else if (u.is_blue())
        {
            set.add_sprite(blue_f,pos,-1);
        } else if (u.is_red())
        {
            set.add_sprite(red_f,pos,-1);
        } else if (u.is_boundary())
        {
            set.add_sprite(boarder_,board_to_screen(u.get_pos()),-1);
        }else if (u.is_mouse()) {
            set.add_sprite(mouse_f,pos);
        }

    }
    if(model_.pause())
    {
        set.add_sprite(pause_,paus_pos(),1);
    }
    if(model_.manual())
    {
        set.add_sprite(food_type_,paus_pos(),2);
    }
    if(model_.dead()){
        set.add_sprite(dead, {0,0},3);
        highscore_string = "high score: "+ std::to_string(model_.get_score());

    }    set.add_sprite(pause_button,paus_button_pos());


    built.message("score: ").add_message(model_.get_score());

    set.add_sprite(highscore, {0,initial_window_dimensions().height - 20});
    //highscore = built.build();

}
ge211::Position View::paus_pos()
{
    Dimensions dim = initial_window_dimensions();
    int h = dim.height - 512;
    int w = dim.width - 512;
    return {w/2,h/2};
}

ge211::Position View::paus_button_pos()
{
    Dimensions dim = initial_window_dimensions();
    int h = 0;
    int w = dim.width - 50;
    return {w,h};
}

ge211::Position View::disp_pos(Position p)
{
    int x_ = board_to_screen(p).x;
    int y_ = board_to_screen(p).y;
    Position pp{1 + x_, 1 + y_};
    return pp;
}

Dimensions View::initial_window_dimensions() const
{
    return grid_size * model_.board_().dims_;
}

std::string View::initial_window_title() const
{
    return "Snake++";
}
ge211::Position View::screen_to_board(ge211::Position p) const
{

    return {(int) p.x / grid_size, (int) p.y / grid_size};
}


ge211::Position View::board_to_screen(ge211::Position p) const
{
    return { grid_size * p.x,  grid_size * p.y};
}