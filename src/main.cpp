#include <iostream>
#include <array>


#include "../include/mouse/mouse.h"
#include "../include/api/api.h"
#include <random>

int main() {
	// Create mouse object and display all walls
	rwa2::Mouse mouse;
	mouse.display_walls();
	// Initialize goal position and the bool reached.
	
	const std::vector<int> g{7,7};
	bool reached = false;
	while(!reached){
		
		// Clear color for all tiles
		// Paint and add text for goal location
		// Update n to the current position of the robot
		API::clearAllColor();
		API::setColor(7,7,'g');
		API::setText(7,7,"G1");
		std::vector<int> n{mouse.get_m_x(),mouse.get_m_y()};
		
		// Get direction in which robot is currently facing
		int m_direction = mouse.get_direction();

		// Check for walls in API and Update Walls in program
		mouse.check_walls();

		// Update walls in API based on walls in program (m_maze)
		mouse.update_api_walls();
		
		// Call the search_maze
		bool b = mouse.search_maze(n,g);

		// Path is extracted into a vector and Stack s is emptied
		std::vector<std::vector<int>> dfs_path = mouse.get_path(); 
		
		// Color Tiles for the nodes in the DFS Generated Path without changing color or text of goal tile
		for(std::vector<int> p: dfs_path)
		{
			if((p.at(0) != g.at(0)) || (p.at(1) != g.at(1)))
			{
				API::setColor(p.at(0), p.at(1), 'B');
			} 
		}
		
		// Move the robot along the DFS path until you hit a wall or reach the goal
		mouse.move_mouse(dfs_path);

		// If mouse has reached goal in the API, set reached to true
		if((mouse.get_m_x() == g.at(0)) && (mouse.get_m_y() == g.at(1)))
		{
			reached = true;
		}
		
		// If robot has reached the goal, 
		// clear color for all tiles while retaining the color and text of goal tile by resetting them 
		if(reached){
			API::clearAllColor();
			API::setColor(7,7,'g');
			API::setText(7,7,"G1");
		}
		
		// Empty the visited list
		mouse.empty_visited();
	}
}

