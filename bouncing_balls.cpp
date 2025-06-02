// A child is playing with a ball on the nth floor of a tall building. The height of this floor above ground level, h, is known.

// He drops the ball out of the window. The ball bounces (for example), to two-thirds of its height (a bounce of 0.66).

// His mother looks out of a window 1.5 meters from the ground.

// How many times will the mother see the ball pass in front of her window (including when it's falling and bouncing)?

// Three conditions must be met for a valid experiment:
// Float parameter "h" in meters must be greater than 0
// Float parameter "bounce" must be greater than 0 and less than 1
// Float parameter "window" must be less than h.
// If all three conditions above are fulfilled, return a positive integer, otherwise return -1.

// Note:
// The ball can only be seen if the height of the rebounding ball is strictly greater than the window parameter.

// Examples:
// - h = 3, bounce = 0.66, window = 1.5, result is 3

// - h = 3, bounce = 1, window = 1.5, result is -1 

// (Condition 2) not fulfilled).

/*
Problem: 
    A ball is being dropped from a building. Given a floor level, a bounce factgor, and a window height, we have to calculate how many times the ball will pass by the window height level, both on the bounce up and return back down.

    Inputs: 
        Height: positive integer representing floor level
        Bounce factor: positive float representing how much of the drop height the ball will bounce back upwards on each bounce given the previous falling height
        window: positive float representing location of the window
    
    conditions:
        height: must be > 0
        bounce: > 0 and < 1
        window: must be < height
    If conditions are not met for input parameters, return -1

    Edge cases:
        If conditions for valid experiment are met, every experiment has at least 1 valid pass by the window from the original drop of the ball. If due to the bounce factor it doesn't reach the window height, return 1. 

    I believe saying "strictly greater than the window parameter" means that it has to be > and not >=

Examples:
    Height of 3, bounce of 0.66, window of 1.5 is a result of 3 
        3 x 0.66 = 1.98 = 2 passes by window
        * 1 pass due to initial drop

Data Structures: 
    - should just require a while loop and no containers

Algorithm: 

    - verify experiment conditions on input arguments
        - if not valid, return -1
    - DEFINE pass_by counter for final return
    - DEFINE bounce_height variable to be computed each loop
    - DEFINE while loop until bounce_height is less than or equal to (since the bounce has to be strictly greater than the window height) window height
        - calculate and update bounce height
        - increment pass_by counter
*/

#include <iostream>

using namespace std;

class BouncingBall
{
    public:
        static int bouncingBall(double h, double bounce, double window)
        {
            if (h < 0 || bounce <= 0 || bounce >= 1 || window >= h) 
            {
                return -1;
            }
            int pass_by_counter {1}; // Initialize at 1 for initial drop
            while (h > window)
            {
                h = (h * bounce);
                // Only increment if new calculated bounce is higher
                if (h > window) pass_by_counter += 2;
            }
            return pass_by_counter;
        }
};

int main(int argc, char const *argv[])
{
    std::cout << BouncingBall::bouncingBall(3, 0.66, 1.5);
    return 0;
}
