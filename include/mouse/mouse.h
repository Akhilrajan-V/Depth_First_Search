/**
 * @file mouse.h
 * @author Aditya Varadaraj, Saurabh Prakash Palande, Akhilrajan Vethirajan
 * @brief The file contains the Mouse class
 * @version 0.1
 * @date 2021-11-10
 *
 * @copyright Copyright (c) 2021
 *
 */

 /*! \mainpage Maze search algorithm
  *
  * This project consists of searching a path in a maze
  * and then task a mouse (robot) to follow the path.
  * - \subpage searchingPathPage "Searching a path"
  *
  * - \subpage followingPathPage "Following a path"
  *
  */

  /*! \page searchingPathPage Searching a path
   *
   * The search algorithm used for searching a path in a maze relies on
   * the depth-first search (DFS) approach. This algorithm is implemented in rwa2::Mouse::search_maze()
   *
   */

   /*! \page followingPathPage Following a path
    *
    * To follow a path generated by DFS, methods from the class API (api/api.h) must be used to interact
    * with the micromouse simulator.
    * - Methods of the API class are documented <a href="https://github.com/mackorone/mms#summary">here</a>.
    */


#ifndef MICROMOUSE_H
#define MICROMOUSE_H

#include "../node/node.h"
#include "../util/util.h"
#include <array>
#include <stack>
#include <vector>
#include <algorithm>

namespace rwa2 {
    /**
     * @brief This class is used to compute a path and execute the path.
     *
     */
    class Mouse {
        public:

        /**
         * @brief Construct a new MicroMouse object
         *
         * The robot is always at (0,0) and facing NORTH when the simulator starts
         */
        Mouse() :m_x{ 0 }, m_y{ 0 }, m_direction{ direction::NORTH } {
            //initialize the maze by placing around the perimeter of the maze
            for (int x = 0; x < m_maze_width; x += 1) {
                for (int y = 0; y < m_maze_height; y += 1) {
                    m_maze.at(x).at(y).set_wall(direction::NORTH, (y == m_maze_height - 1));
                    m_maze.at(x).at(y).set_wall(direction::EAST, (x == m_maze_width - 1));
                    m_maze.at(x).at(y).set_wall(direction::SOUTH, (y == 0));
                    m_maze.at(x).at(y).set_wall(direction::WEST, (x == 0));
                }
            }
        }
        // this method visually sets the walls in the simulator
        
        /**
         * @brief displays walls for m_maze in API
         * 
         */
        void display_walls();
        
        //IMPLEMENT THE METHODS BELOW
        //Note: Come up with your own parameters and implementations
        
        /**
         * @brief Implement DFS to compute a path between 2 nodes in a maze
         *
         * @return true A path is found
         * @return false A path is not found
         */
        bool search_maze(std::vector<int> n, std::vector<int> g);
        
        /**
         * @brief Make the mouse move forward in API
         *
         */
        void move_forward();
        
        /**
         * @brief Make the mouse rotate 90 deg CCW in API
         *
         */
        void turn_left();
        
        /**
         * @brief Make the mouse rotate 90 deg CW in API
         *
         */
        void turn_right();
        
        /**
         * @brief Checks whether walls exist in the API around the robot's current position
         *        and Updates walls in m_maze of mouse class
         * 
         */
        void check_walls();
        
        /**
         * @brief Updates walls in the API
         * 
         */
        void update_api_walls();
        
        /**
         * @brief empties the stack s
         * 
         */
        void empty_stack()
        {
            while(!s.empty())
            {
                s.pop();
            }
        }
        
        /**
         * @brief empties the visited vector v
         * 
         */
        void empty_visited()
        {
            v.clear();
        }
        
        /**
         * @brief Gets the dfs path by emptying the stack s into a vector and reversing the order.
         * 
         * @return std::vector<std::vector<int>> 
         */
        std::vector<std::vector<int>> get_path()
        {
            std::vector<std::vector<int>> path;
            while (!s.empty())
            {
                path.push_back(s.top());
                s.pop();
            }
            std::reverse(path.begin(), path.end());
            return path;

        }
        
        /**
         * @brief Moves the mouse along dfs_path while checking for and updating any walls
         * 
         * @param path 
         */
        void move_mouse(std::vector<std::vector<int>> path);

        // Getter Functions
        /**
         * @brief Getter for m_x
         * 
         * @return const int 
         */
        const int get_m_x()
        {
            return m_x;
        }

        /**
         * @brief Getter for m_y
         * 
         * @return const int 
         */
        const int get_m_y()
        {
            return m_y;
        }
        
        /**
         * @brief Getter for m_direction
         * 
         * @return const int 
         */
        const int get_direction()
        {
            return m_direction;
        }
        
        private:
        static const int m_maze_width{ 16 }; //width of the maze
        static const int m_maze_height{ 16 };//height of the maze
        int m_x; //x position of the robot in the maze
        int m_y; //y position of the robot in the maze
        int m_direction; //direction of the robot in the maze
        std::array<std::array<Node, m_maze_width>, m_maze_height> m_maze; //2D array maze object
        std::stack<std::vector<int>> s; // Stack of (x,y)
        std::vector<std::vector<int>> v; // Visited List (Vector) of (x,y)
        
    };
}
#endif