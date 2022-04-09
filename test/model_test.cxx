#include "model.hxx"
#include <catch.hxx>
#include <ge211.hxx>

struct test_access
{
    Model& model ;


    int& score()
    { return model.score_ ; }

    //snakePart& sPart()
    //{ return model.head_ ; }
   // field& field()
    //{return model.f_; }
    int& lvl()
    { return model.level_;}





};

// Checks that the high score starts at 0
// and when score is greater than high score
// high score gets updated
TEST_CASE("High score")
{
    Model m;

    CHECK( m.get_highscore() == 0 );

    test_access t{m};
    t.score() = 1;
    CHECK(m.get_highscore() == 1);

}

// Checks that the snakePart head_
// is initialized with no pointer to the
// next part
TEST_CASE("Initial snake length")
{
    Model m;
    test_access t{m};
    //CHECK(t.sPart().next == NULL);
}

TEST_CASE("Unit number check")
{
   // int n;
   // unit u(n);
    //CHECK(u.get_num() == n);
}

// Checks is the new food location
// is within the empties vector
TEST_CASE("New food type")
{
    Model m;
    test_access t{m};
    bool check = false;
    //for(unit u : t.field().get_empties())
   // {
    //    if(u.get_num() == m.new_food()){
   //         check = true;
   //         CHECK(check);
   //         return;
   //     }
   // }
    //CHECK(check);
}

// Checks if level increase after
// a score of 5
TEST_CASE("Level check")
{
    


}

