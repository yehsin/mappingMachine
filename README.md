mappingMachine
==============
## 資料結構 project2 掃地機器人

- Project Objective
    - Apply the knowledge learned from the course of data structures and implement an efficient robot floor cleaning algorithm.
-  Project Description
    - You are to design an optimal floor cleaning algorithm to drive the robot. The floorplan is described as an 𝑚 ∗ 𝑛 matrix, in which each cell is marked with one the following status.
    1. “1” indicates an obstacle, which normally is a wall.
    2. “0” indicates a free space to be cleaned.
    3. “R” indicates where the robot is placed initially. This is also where the robot can be recharged.</br></br>
    - **The robot is to follow these rules**
    1. Always starts from the cell marked “R”.
    2. Needs to clean every free cell “0” on the floor.
    3. Cannot move into or cross any obstacle cell “1” or move outside the floor boundary.
    4. Can only move up, down, left and right.
    5. The robot is initially charged with a battery life “B”, which means the robot can move B steps before it runs out of power. Moving from one cell to next cell is counted as one step.</br>
    Note that the range of battery life “B” is 0～2147483647 
    6. Needs to return for recharge before running out battery. Each recharge fully restores the battery life “B”.
    7. After cleaning all free cells, needs to return to the cell “R” for recharge.

### Example
7 10 30</br>
1 1 1 1 1 1 1 1 1 1</br>
1 0 0 0 1 0 0 0 0 1</br>
1 0 0 0 1 0 0 0 0 1</br>
1 0 0 0 1 0 0 0 0 1</br>
1 0 1 1 1 1 1 1 0 1</br>
1 0 0 0 0 0 0 0 0 1</br>
1 1 1 1 R 1 1 1 1 1</br>
This case describes a floorplan with cells of 7 rows and 10 columns. The battery life allows the robot to move 30 steps for each fully charged run. We assume the row index and column index all starts from 0. Therefore, initially the robot is placed at cell (6, 4). Note that R can be at any, but only one, location.</br></br>
#### Result output file
Output your optimized final floor cleaning path into a file named “final.path”. The first line should be the number of steps your algorithm used to finish the cleaning task and for the following lines, each should have two numbers i an j, representing the cell (i, j) walked subsequently by the cleaning
robot.</br></br>

6</br>
5 4</br>
5 5</br>
5 6</br>
5 5</br>
5 4</br>
6 4</br>
This example shows that the robot moves 6 steps. TAs will verify whether your solution is valid according to the following rules. Any invalid solution receives no score.