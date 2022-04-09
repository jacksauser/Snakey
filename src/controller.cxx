#include "controller.hxx"


Controller::Controller(int width, int height)
        : model_({width, height})
        , view_(model_)
{ }

void Controller::draw(ge211::Sprite_set& sprites)
{
    view_.draw(sprites);
}

ge211::Dimensions Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

std::string Controller::initial_window_title() const
{
    return view_.initial_window_title();
}

void Controller::on_mouse_up(ge211::Mouse_button, ge211::Position p)
{

    if(model_.pause())
    {
        if(model_.manual())
        {
            if(test_rect(manual_back,p))
            {model_.get_manual();}
        } else if (test_rect(manual,p)){
            model_.get_manual();
        } else if (test_rect(resume,p)){
            model_.pause_game();
        } else if (test_rect(restart,p)){
            model_.new_game();
        }

    } else if (test_rect(paus_but,p)){
        model_.pause_game();
    }


}
bool Controller::test_rect(ge211::Rectangle r, Position p)
{
    bool a = p.x <= r.x+r.width;
    bool b = p.x >= r.x;
    bool c = p.y <= r.y+r.height;
    bool d = p.y >= r.y;
    return a&&b&&c&&d;

}

void Controller::on_key(ge211::Key key)
{
    if(key == ge211::Key::code(' '))
    {
        if(model_.dead()){
            model_.new_game();
        }else { model_.pause_game();}
    } else if(key == ge211::Key::code('p'))
    {
        model_.pause_game();
    } else if(key == ge211::Key::code('q'))
    {
        quit();
    } else if(key == ge211::Key::up())
    {
        model_.change_dir({0,-1});
        //model_.board_()[{2,2}]
    } else if(key == ge211::Key::down())
    {
        model_.change_dir({0,1});
    } else if(key == ge211::Key::left())
    {
        model_.change_dir({-1,0});
    } else if(key == ge211::Key::right())
    {
        model_.change_dir({1,0});
    } else if(key == ge211::Key::code('m'))
    {
        model_.get_manual();
    }else if(key == ge211::Key::code('r'))
    {
        model_.new_game();
    }

}

void Controller::on_frame(double dt)
{
    model_.update();
}


