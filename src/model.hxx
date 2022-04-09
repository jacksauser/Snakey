#pragma once

#include <ge211.hxx>
#include <vector>
#include <list>
#include <ctime>

using Dimensions = ge211::Dimensions;
using Position = ge211::Position;
//
// Model constants
//
const ge211::Dimensions dot_size{};



//created a unit of the playing field
struct unit
{;

private:


    ge211::Position pos_;


    bool snake_b;
    //food types
    bool red_;
    bool blue_;
    bool mouse_;


    bool boundary_;

public:
    unit(ge211::Position pos);
    unit();
    unit(unit const& u);
    // makes snake true
    void to_snake()
    {snake_b = true;}
    // makes red true
    void to_red()
    {red_=true;}
    // makes blue true
    void to_blue()
    {blue_ = true;}
    // makes boundary true
    void to_boundary()
    {boundary_=!boundary_;}
    // makes mouse true
    void to_mouse()
    {mouse_ = true;}
    // makes unit into nothing
    void clean()
    {snake_b = false;
        red_ = false;
        blue_ = false;
        mouse_ = false;
        boundary_ = false;}
    // returns true is unit is empty
    bool is_empty()
    {return !snake_b && !red_ && !blue_ && !boundary_ && !mouse_;}
    // returns true is unit is mouse
    bool is_snake()
    {return snake_b;}
    // returns true is unit is mouse
    bool is_red()
    {return red_;}
    // returns true is unit is mouse
    bool is_blue()
    {return blue_;}
    // returns true is unit is mouse
    bool is_mouse()
    {return mouse_;}
    //returns true if unit is boundary
    bool is_boundary()
    {return boundary_;}

    //gets units number
    Position get_pos()
    {return pos_;}


    friend struct test_access;
};




// Vector of units that make up the
// game window
struct board
{
    Dimensions dims_;
    ge211::Rectangle board_pos;
private:

    //number of units per row
    int row_len;
    //number of units per column
    int column_len;
    Dimensions screen_dims;

    bool red_on;

public:
    explicit board(ge211::Dimensions dim);

    bool on_the_boarder(Position pos);

    ge211::Dimensions dimensions();

    std::list<unit> screen;
    // returns vector of units that are empty
    std::vector<unit> get_empties();

    // returns the unit in the called direction direction



    Position add();



    // returns the center unit
    unit& get_center();


    unit& operator[](ge211::Position pos);



};

// where the snake is and it's direction
// and a link to the next part

struct snake
{

    //unit the snake part is in
    std::list<unit> snake_;
    board game_board;

    //reference to next part
    //snakePart* next;
    //reference to prev part
    //snakePart* prev;
    Dimensions dir_;


    //int nextDir();

    //creates a new snakePart
    snake(board& b);

    // increase snake length
    void grow(Dimensions dir);
    unit snake_head();

    friend struct test_access;
    void move(Dimensions dir);
};

class Model
{



    board b_;
    snake s_;
    Dimensions dir_;
    Dimensions dim_;
    ge211::Timer red_t;
    Position red_pos;
    double velo_;
    int level_;
    int score_;
    int highscore_;
    bool pause_;
    bool manual_;
    bool dead_;
    bool red_;
    bool eat_;
    bool ate;

public:
    // returns current score
    int get_score() const;
    // updates and returns high score
    int get_highscore() const;
    // pauses the game, goes to pause screen
    void pause_game();
    // opens the manual screen
    void get_manual();

    // updates the game
    void update();

    // creates the model
    Model();

    Model(Dimensions dim);
    board const board_() const;
    void change_dir(Dimensions dir);
    bool manual() const ;
    bool pause() const ;

    void new_game();
    bool dead() const;
private:
    // creates the screen displayed


    friend struct test_access;

    void advance();
    double velo();


    void food();
    void move_snake();

    void grow_snake();
};


