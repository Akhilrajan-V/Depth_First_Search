#include "../include/mouse/mouse.h"  
#include "../include/api/api.h"  
#include "../include/util/util.h"
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>

void rwa2::Mouse::display_walls() {
    for (int x = 0; x < m_maze_width; x += 1) {
        for (int y = 0; y < m_maze_height; y += 1) {
            if (m_maze.at(x).at(y).is_wall(direction::NORTH)) {
                //display this wall in the simulator
                API::setWall(x, y, 'n');
            }
                
            if (m_maze.at(x).at(y).is_wall(direction::EAST)) {
                //display this wall in the simulator
                API::setWall(x, y, 'e');
            }
                
            if (m_maze.at(x).at(y).is_wall(direction::SOUTH)) {
                //display this wall in the simulator
                API::setWall(x, y, 's');
            }
                
            if (m_maze.at(x).at(y).is_wall(direction::WEST)) {
                //display this wall in the simulator
                API::setWall(x, y, 'w');
            }
            //display the number of walls surrounding the current node
            API::setText(x, y, std::to_string(m_maze.at(x).at(y).compute_number_of_walls()));
        }
    }
}

bool rwa2::Mouse::search_maze(std::vector<int> n, std::vector<int> g) {
    
    
    // If node is not goal node and stack is empty, node is pushed into stack.
    // If node is equal to goal node, search_maze() returns true
    if ((n.at(0) != g.at(0)) || (n.at(1) != g.at(1)))
    {
        if(s.empty())
        {
            s.push(n);
        }
    } 
    else {
        return true;
    }

    // If node is not already visited, we push it to the visited list
    if (std::find(v.begin(), v.end(), n) == v.end()){
        v.push_back(n);
    }
    

    // Check if the next node in a particular direction is valid, 
    // whether it is not already visited and whether there is a wall which obstructs motion in the direction
    // If next nodes in all directions are invalid, backtrack
    // Direction Preference Order in DFS: NORTH, EAST, SOUTH, WEST
    if(((n.at(1) + 1 < m_maze_height) && (std::find(v.begin(), v.end(),std::vector<int> {n.at(0), n.at(1)+1}) == v.end())) && !(m_maze[n.at(0)][n.at(1)].is_wall(direction::NORTH)))
    {
        /* Checking NORTH */
        n.at(1) += 1;
        s.push(n);
        
    }
    else if(((n.at(0)+1 < m_maze_width) && (std::find(v.begin(), v.end(),std::vector<int> {n.at(0)+1, n.at(1)}) == v.end())) && !(m_maze[n.at(0)][n.at(1)].is_wall(direction::EAST)))
    {
        /* Checking EAST */
        n.at(0) += 1;
        s.push(n);
        
    }
    else if(((n.at(1)-1 >= 0) && (std::find(v.begin(), v.end(),std::vector<int> {n.at(0), n.at(1)-1}) == v.end())) && !(m_maze[n.at(0)][n.at(1)].is_wall(direction::SOUTH)))
    {
        /* Checking SOUTH */
        n.at(1) -= 1;
        s.push(n);
        
    }
    else if(((n.at(0)-1 >= 0) && (std::find(v.begin(), v.end(),std::vector<int> {n.at(0) - 1, n.at(1)}) == v.end())) && !(m_maze[n.at(0)][n.at(1)].is_wall(direction::WEST)))
    {
        /* Checking WEST */
        n.at(0) -= 1;
        s.push(n);
        
    }
    else{
        /* No valid nodes - Backtracking */
        if(!(s.empty()))
        {
            s.pop();
        } else{
            return false;
        }
    }

    if(!(s.empty()))
    {
        n = s.top();
        
        return search_maze(n, g);
    } else {
        return false;
    }


    
}


void rwa2::Mouse::move_forward()
{
    API::moveForward();
}

void rwa2::Mouse::turn_left()
{
    API::turnLeft();
}

void rwa2::Mouse::turn_right()
{
    API::turnRight();
}


void rwa2::Mouse::check_walls(){
    // Based on m_direction, checks and updates walls in front, left and right of the robot 
    if(m_direction == direction::NORTH)
    {
        m_maze.at(m_x).at(m_y).set_wall(direction::NORTH, API::wallFront());   
        m_maze.at(m_x).at(m_y).set_wall(direction::WEST, API::wallLeft());
        m_maze.at(m_x).at(m_y).set_wall(direction::EAST, API::wallRight());
    }
    else if(m_direction == direction::EAST)
    {
        m_maze.at(m_x).at(m_y).set_wall(direction::EAST, API::wallFront());   
        m_maze.at(m_x).at(m_y).set_wall(direction::NORTH, API::wallLeft());
        m_maze.at(m_x).at(m_y).set_wall(direction::SOUTH, API::wallRight());
    }
    else if(m_direction == direction::SOUTH)
    {
        m_maze.at(m_x).at(m_y).set_wall(direction::SOUTH, API::wallFront());   
        m_maze.at(m_x).at(m_y).set_wall(direction::EAST, API::wallLeft());
        m_maze.at(m_x).at(m_y).set_wall(direction::WEST, API::wallRight());
    }
    else if(m_direction == direction::WEST)
    {
        m_maze.at(m_x).at(m_y).set_wall(direction::WEST, API::wallFront());   
        m_maze.at(m_x).at(m_y).set_wall(direction::SOUTH, API::wallLeft());
        m_maze.at(m_x).at(m_y).set_wall(direction::NORTH, API::wallRight());
    }
    else
    {
        std::cout << "Try Again. Invalid Direction" << '\n';
    }
    
}

void rwa2::Mouse::update_api_walls(){
    // Updates walls in API if there is a wall in the corresponding directions
    // in the m_maze of the mouse class 
    std::array<int,4> directions{direction::NORTH, direction::EAST, direction::SOUTH, direction::WEST};
    std::array<char, 4> dir{'n', 'e', 's', 'w'};
    for(int i : directions){
        if(m_maze.at(m_x).at(m_y).is_wall(i))
        {
            API::setWall(m_x, m_y, dir[i]);
        }
    }
}


void rwa2::Mouse::move_mouse(std::vector<std::vector<int>> path)
{
    for(int i=0; i<path.size() - 1; i++)
    {
        check_walls(); //Checking and Updating walls in m_maze
        update_api_walls(); //Updating walls in API
        if (m_direction == direction::NORTH)
        {
            // Case 1: Robot facing NORTH

            // If next node is in NORTH and there is no wall encountered in the direction, 
            // move the mouse forward and update m_x, m_y accordingly

            // If next node is in EAST and there is no wall encountered in the direction, 
            // turn the mouse right and move forward and update m_x, m_y accordingly

            // If next node is in SOUTH and there is no wall encountered in the direction, 
            // turn the mouse right twice (to face in opposite direction to current direction)
            // and move forward and update m_x, m_y accordingly

            // If next node is in WEST and there is no wall encountered in the direction, 
            // turn the mouse left and move forward  and update m_x, m_y accordingly

            // If there is a wall in the direction of next node, break the loop thus stopping the robot  
            if((path.at(i+1).at(1) == path.at(i).at(1) + 1) && !(m_maze.at(m_x).at(m_y).is_wall(direction::NORTH)))
            {
                move_forward();
                m_y += 1;
                m_direction = direction::NORTH;
            }
            else if((path.at(i+1).at(0) == path.at(i).at(0) + 1) && !(m_maze.at(m_x).at(m_y).is_wall(direction::EAST)))
            {
                turn_right();
                move_forward();
                m_x += 1;
                m_direction = direction::EAST;
            }
            else if((path.at(i+1).at(1) == path.at(i).at(1) - 1) && !(m_maze.at(m_x).at(m_y).is_wall(direction::SOUTH)))
            {
                turn_right();
                turn_right();
                move_forward();
                m_y -= 1;
                m_direction = direction::SOUTH;
            }
            else if((path.at(i+1).at(0) == path.at(i).at(0) - 1) && !(m_maze.at(m_x).at(m_y).is_wall(direction::WEST)))
            {
                turn_left();
                move_forward();
                m_x -= 1;
                m_direction = direction::WEST;
            }
            else{
                break;
            }
        }
        else if(m_direction == direction::EAST)
        {
            // Case 2: Robot facing EAST

            // If next node is in NORTH and there is no wall encountered in the direction, 
            // turn the mouse left and move forward and update m_x, m_y accordingly
            
            // If next node is in EAST and there is no wall encountered in the direction, 
            // move the mouse forward and update m_x, m_y accordingly

            // If next node is in SOUTH and there is no wall encountered in the direction, 
            // turn the mouse right and move forward and update m_x, m_y accordingly

            // If next node is in WEST and there is no wall encountered in the direction, 
            // turn the mouse right twice (to face in opposite direction to current direction)
            // and move forward and update m_x, m_y accordingly

            // If there is a wall in the direction of next node, break the loop thus stopping the robot
            if((path.at(i+1).at(1) == path.at(i).at(1) + 1) && !(m_maze.at(m_x).at(m_y).is_wall(direction::NORTH)))
            {
                turn_left();
                move_forward();
                m_y += 1;
                m_direction = direction::NORTH;
            }
            else if((path.at(i+1).at(0) == path.at(i).at(0) + 1) && !(m_maze.at(m_x).at(m_y).is_wall(direction::EAST)))
            {
                move_forward();
                m_x += 1;
                m_direction = direction::EAST;
            }
            else if((path.at(i+1).at(1) == path.at(i).at(1) - 1) && !(m_maze.at(m_x).at(m_y).is_wall(direction::SOUTH)))
            {
                turn_right();
                move_forward();
                m_y -= 1;
                m_direction = direction::SOUTH;
            }
            else if((path.at(i+1).at(0) == path.at(i).at(0) - 1) && !(m_maze.at(m_x).at(m_y).is_wall(direction::WEST)))
            {
                turn_right();
                turn_right();
                move_forward();
                m_x -= 1;
                m_direction = direction::WEST;
            }
            else{
                break;
            }
        }
        else if (m_direction == direction::SOUTH)
        {
            // Case 3: Robot facing SOUTH

            // If next node is in NORTH and there is no wall encountered in the direction, 
            // turn the mouse right twice (to face in opposite direction to current direction)
            // and move forward and update m_x, m_y accordingly
            
            // If next node is in EAST and there is no wall encountered in the direction, 
            // turn the mouse left and move forward and update m_x, m_y accordingly
            
            // If next node is in SOUTH and there is no wall encountered in the direction, 
            // move the mouse forward and update m_x, m_y accordingly

            // If next node is in WEST and there is no wall encountered in the direction, 
            // turn the mouse right and move forward and update m_x, m_y accordingly

            // If there is a wall in the direction of next node, break the loop thus stopping the robot
            if((path.at(i+1).at(1) == path.at(i).at(1) + 1) && !(m_maze.at(m_x).at(m_y).is_wall(direction::NORTH)))
            {
                turn_right();
                turn_right();
                move_forward();
                m_y += 1;
                m_direction = direction::NORTH;
            }
            else if((path.at(i+1).at(0) == path.at(i).at(0) + 1) && !(m_maze.at(m_x).at(m_y).is_wall(direction::EAST)))
            {
                turn_left();
                move_forward();
                m_x += 1;
                m_direction = direction::EAST;
            }
            else if((path.at(i+1).at(1) == path.at(i).at(1) - 1) && !(m_maze.at(m_x).at(m_y).is_wall(direction::SOUTH)))
            {
                move_forward();
                m_y -= 1;
                m_direction = direction::SOUTH;
            }
            else if((path.at(i+1).at(0) == path.at(i).at(0) - 1) && !(m_maze.at(m_x).at(m_y).is_wall(direction::WEST)))
            {
                turn_right();
                move_forward();
                m_x -=1;
                m_direction = direction::WEST;
            }
            else{
                break;
            }
        }
        else if(m_direction == direction::WEST)
        {
            // Case 4: Robot facing WEST

            // If next node is in NORTH and there is no wall encountered in the direction, 
            // turn the mouse right and move forward and update m_x, m_y accordingly
            
            // If next node is in EAST and there is no wall encountered in the direction, 
            // turn the mouse right twice (to face in opposite direction to current direction)
            // and move forward and update m_x, m_y accordingly

            // If next node is in SOUTH and there is no wall encountered in the direction, 
            // turn the mouse left and move forward and update m_x, m_y accordingly

            // If next node is in WEST and there is no wall encountered in the direction, 
            // move the mouse forward and update m_x, m_y accordingly

            // If there is a wall in the direction of next node, break the loop thus stopping the robot
            if((path.at(i+1).at(1) == path.at(i).at(1) + 1) && !(m_maze.at(m_x).at(m_y).is_wall(direction::NORTH)))
            {
                turn_right();
                move_forward();
                m_y += 1;
                m_direction = direction::NORTH;
            }
            else if((path.at(i+1).at(0) == path.at(i).at(0) + 1) && !(m_maze.at(m_x).at(m_y).is_wall(direction::EAST)))
            {
                turn_right();
                turn_right();
                move_forward();
                m_x += 1;
                m_direction = direction::EAST;
            }
            else if((path.at(i+1).at(1) == path.at(i).at(1) - 1) && !(m_maze.at(m_x).at(m_y).is_wall(direction::SOUTH)))
            {
                turn_left();
                move_forward();
                m_y -= 1;
                m_direction = direction::SOUTH;
            }
            else if((path.at(i+1).at(0) == path.at(i).at(0) - 1) && !(m_maze.at(m_x).at(m_y).is_wall(direction::WEST)))
            {
                move_forward();
                m_x -= 1;
                m_direction = direction::WEST;
            }
            else{
                break;
            }
        }
        
    }
    
    
}