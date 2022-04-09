#pragma once

#include "model.hxx"
#include "view.hxx"

using Rectangle = ge211::Rectangle;

// The main game class for Snake++.
class Controller : public ge211::Abstract_game
{
public:
    explicit Controller(int width, int height);

protected:
    void draw(ge211::Sprite_set&) override;
    ge211::Dimensions initial_window_dimensions() const override;
    std::string initial_window_title() const override;
    void on_mouse_up(ge211::Mouse_button, ge211::Position) override;
    void on_key(ge211::Key key) override ;
    void on_frame(double dt) override;
private:
    Model            model_;
    View             view_;

    Rectangle manual_back = Rectangle::from_top_left(view_
            .paus_pos()
            .down_right_by
            ({161,404}),
            {104,53});
    Rectangle resume = Rectangle::from_top_left(view_
            .paus_pos()
            .down_right_by
            ({53,107}),
            {406,65});

    Rectangle manual = Rectangle::from_top_left(view_
            .paus_pos()
            .down_right_by
            ({54,209}),
            {406,65});

    Rectangle restart = Rectangle::from_top_left(view_
            .paus_pos()
            .down_right_by
            ({54,314}),
            {406,65});

    Rectangle paus_but = Rectangle::from_top_left(view_
            .paus_button_pos()
            .down_right_by
            ({0,0}),
            {120,120});

    bool test_rect(Rectangle r, Position p);
};