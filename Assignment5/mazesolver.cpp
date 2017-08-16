#include <iostream>
#include <fstream>
#include <string>

#define row_max 205
#define column_max 205

int main(int argc, char *argv[])
{
  unsigned int row_total = 0;
  unsigned int col_total = 0;
  
  /* Checking command line arguments */
  if (argc < 2)
  {
    std::cout << "Usage:" << std::endl;
    std::cout << " " << argv[0] << "<maze file> <solution file>" << std::endl;
    return 0;
  }

  std::string maze_file = argv[1];
  std::string solution_file = argv[2];
  std::ifstream mazefile(maze_file);
  std::ofstream solutionfile(solution_file);
  
  unsigned char maze[row_max][column_max];
  for (unsigned int i = 0; i < row_max; i++) 
    {
      for (unsigned int j = 0; j < column_max; j++) 
      {
        maze[i][j] = 0;
      }
    }
  

  /* Checking storage */
  if (mazefile.is_open()) 
  {
    unsigned int row_count, column_count;
    mazefile >> row_count >> column_count;
    if(row_count > row_max or column_count > column_max) 
    {
      std::cout << "Not enough storage available!" << std::endl;
      return 0;
    }
    else
      row_total = row_count;
      col_total = column_count;

    /* Initializing array of zeros */
    for (unsigned int i = 0; i < row_count; i++) 
    {
      for (unsigned int j = 0; j < column_count; j++) 
      {
        maze[i][j] = 0;
      }
    }
  }
    /* Populating wall locations in array */
    unsigned int row;
    unsigned int column;
    while (mazefile >> row >> column)
    {
      maze[row][column] = 1;
    }
    mazefile.close();

  unsigned int current_pos[2] = {0,0};
  unsigned int row_end = row_total - 1;
    for (unsigned int j = 0; j < col_total; j++)
    {
      if (maze[0][j] == 0)
      {
        current_pos[1] = j;
        break;
      }
  }
  solutionfile << current_pos[0] << " " << current_pos[1] << std::endl;

  /* Set up directions for going through maze */
  enum direction
  {
    north,
    south,
    east,
    west
  };

  /* Set initial direction */
  direction d = south;
  
  /* Entering maze */
  while (current_pos[0] < row_end)
  {
    unsigned int ahead_pos[2] = {current_pos[0], current_pos[1]};
    unsigned int right_pos[2] = {current_pos[0], current_pos[1]};
  /* Setting conditions for ahead position and right position */
  switch (d)
  {
    case north:
      ahead_pos[0]--;
      right_pos[1]++; break;
    case south:
      ahead_pos[0]++;
      right_pos[1]--; break;
    case east:
      ahead_pos[1]++;
      right_pos[0]++; break;
    case west:
      ahead_pos[1]--;
      right_pos[0]--; break;
  }
  /* Check if there is a wall to your right. If no, update direction and move to right position */
  if (maze[right_pos[0]][right_pos[1]] == 0)
  {
    switch (d)
    {
      case north:
        d = east; 
        current_pos[1]++; break;
      case south:
        d = west;
        current_pos[1]--; break;
      case east:
        d = south;
        current_pos[0]++; break;
      case west:
        d = north;
        current_pos[0]--; break;
    }
    solutionfile << current_pos[0] << " " << current_pos[1] << std::endl;
  }
  /* Check if there is a wall ahead. If no, then move ahead */
  else if (maze[ahead_pos[0]][ahead_pos[1]] == 0)
  {  
    current_pos[0] = ahead_pos[0];
    current_pos[1] = ahead_pos[1];
    solutionfile << current_pos[0] << " " << current_pos[1] << std::endl;
  }
  else  
  {
    switch (d)
    {
      case north: d = west; break;
      case south: d = east; break;
      case east: d = north; break;
      case west: d = south; break;
    }
  }
  }
  solutionfile.close();
  return 0;
}
