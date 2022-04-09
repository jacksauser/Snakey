#include <iostream>
#include "model.hxx"

using namespace ge211;

unit::unit(ge211::Position pos)
    : pos_(pos)
    , snake_b(false)
    , red_(false)
    , blue_(false)
    , mouse_(false)
    , boundary_(false)
{ }

unit::unit()
    : unit({-1,-1})
{ }

unit::unit(unit const &u)
        : pos_(u.pos_)
        , snake_b(u.snake_b)
        , red_(u.red_)
        , blue_(u.blue_)
        , mouse_(u.mouse_)
        , boundary_(u.boundary_)
{ }


snake::snake(board& b)
    : snake_()
    , game_board(b)
{
    b.get_center().to_snake();
    //unit u = b.get_center();
    snake_.push_front(b.get_center());
}

void snake::grow(Dimensions dir)
{
    Position pos = snake_.front().get_pos();
    unit u{pos + dir};
    game_board[u.get_pos()].is_snake();
    snake_.push_front(u);
}

void snake::move(Dimensions dir)
{
    bool boool = (dir.height == 0 && dir.width == 0);
    if(!boool) {
        Position pos = snake_.front().get_pos();
        unit u{pos + dir};
        //game_board[u.get_pos()].is_snake();
        snake_.push_front(u);
        //game_board[snake_.back().get_pos()].clean();
        snake_.pop_back();
    }
}

unit snake::snake_head()
{
    return snake_.front();
}


board::board(ge211::Dimensions dim)

    : dims_({dim.width + 4, dim.height+4})
    //screen_dims = dim;
    , row_len(dims_.width)
    , column_len(dims_.height)
    , board_pos({0,0,dims_.width,dims_.height})
    , red_on(false)


{
    for(Position pos : board_pos)
    {
        if(on_the_boarder(pos)) {
            unit u{pos};
            u.to_boundary();
            screen.push_back(u);
        }else{
            unit u{pos};
            screen.push_back(u);
        }

    }


}


bool board::on_the_boarder(Position pos)
{
    if(pos.y > 1 && pos.y < column_len - 2)
    {
        if(pos.x > 1 && pos.x < row_len - 2)
        {return false;}
    }
    return true;
}

ge211::Dimensions board::dimensions()
{
    return screen_dims;
}

unit& board::operator[](ge211::Position pos)
{
    for(std::_List_iterator<unit> it = screen.begin();
            it != screen.end(); it++)
    {
        if(it->get_pos() == pos)
        {
            return *it;
        }
    }
    throw Client_logic_error("board[pos]: pos not on board");
}

std::vector<unit> board::get_empties()
{
    std::vector<unit> result;
    for(std::_List_iterator<unit> it = screen.begin();
        it != screen.end(); it++)
    {
        if(it->is_empty())
        {
            result.push_back({*it});
        }
    }
    return result;
}



Position board::add()
{
    std::vector<unit> empties = get_empties();
    std::srand(std::time(nullptr));
    int i = std::rand() % empties.size();

        return empties[i].get_pos();




}


unit& board::get_center()
{
    Position pos {dims_.width / 2, dims_.height / 2};
    for(std::_List_iterator<unit> it = screen.begin();
        it != screen.end(); it++)
    {
        if(it->get_pos() == pos)
        {
            return *it;
        }
    }
    throw Client_logic_error("board::get_center() failed");
}


Model::Model(Dimensions dim)
    : b_(dim)
    , s_(b_)
    , dir_({0,0})
    , level_(0)
    , pause_(false)
    , dead_(false)
    , velo_(.11)
    , score_(0)
    , highscore_(0)
    , eat_(true)
    , manual_(false)
    , dim_(dim)
    , red_t()
    , red_(false)
    , red_pos(Position {0,0})
    , ate(true)
{

}

Model::Model()
    :Model({48,21})
{ }

void Model::update()
{


    if(!pause_ && !dead_) {
        if(red_){
            //red_t.start_time();
            if(red_t.elapsed_time() >= Duration{5})
            {
                b_[red_pos].clean();
                red_= false;
                ate = true;
            }
        }
        Timer t{};
        t.start_time();
        while (t.elapsed_time() < Duration{velo()}) { }
        advance();

    }

}

double Model::velo()
{
    if(score_ % 5 == 0 && eat_)
    {
        level_++;
        velo_-=.01;
        eat_ = false;
    }
    return velo_;
}
int Model::get_highscore() const
{

    return highscore_;
}
int Model::get_score() const
{
    return score_;
}

void Model::new_game()
{
    b_ = board(dim_);
    s_ = snake(b_);
    dir_ = {0,0};
    level_ = 0;
    pause_ = false;
    dead_ = false;
    velo_ = .11;
    highscore_ = score_;
    score_ = 0;
    eat_ = true;
    manual_ = false;
    red_t.reset();
    red_ = false;
    red_pos = Position {0,0};
    ate = true;
}



void Model::advance()
{

    unit s =s_.snake_head();
    Position p = s.get_pos()+dir_;
    unit u = b_[p];
    bool prestart = (dir_.height == 0 && dir_.width == 0);
    food();

    if(u.is_boundary() || u.is_snake() || u.is_red())
    {
        if(!prestart) {
            dead_ = true;
        }
        move_snake();

    } else if (u.is_mouse()) {
        grow_snake();
        score_++;
        ate = true;
    } else if (u.is_blue()){
        velo_+= .01 * (level_/2);
        move_snake();
        ate = true;
        //s_.move(dir_);

    } else {
        move_snake();
       // s_.move(dir_);
    }

}
void Model::move_snake()
{
    Position snake_head = s_.snake_head().get_pos();

    b_[snake_head + dir_].to_snake();
    s_.snake_.push_front({{snake_head + dir_}});
    bool b = b_[snake_head + dir_].is_snake();
    if(snake_head != snake_head +dir_) {
        b_[s_.snake_.back().get_pos()].clean();
    }
    s_.snake_.pop_back();



}

void Model::grow_snake()
{
    Position snake_head = s_.snake_head().get_pos();

    b_[snake_head + dir_].to_snake();
    s_.snake_.push_front({{snake_head + dir_}});
}


void Model::food()
{
    if (ate) {
        std::srand(std::time(nullptr));
        int k = std::rand() % 10;
        if (k < 8) {
            b_[b_.add()].to_mouse();
        } else if (k == 8) {
            b_[b_.add()].to_blue();
        } else if (k == 9) {
            red_pos = b_.add();
            b_[red_pos].to_red();
            red_ = true;
            red_t.reset();
            red_t.start_time();
        }
        ate = false;
    }

}


bool Model::pause() const
{
    return pause_;
}
bool Model::manual() const
{
    return manual_;
}

bool Model::dead() const
{
    return dead_;
}
void Model::change_dir(ge211::geometry::Dimensions dir)
{
    dir_= dir;
}

board const Model::board_() const
{
    return  b_;
}

void Model::pause_game()
{
    pause_ = !pause_;

}
void Model::get_manual()
{
    manual_ = !manual_;
    pause_ = true;
}
/*
std::vector<unit>& Model::get_screen() const
{
    return screen;
}
*/