mappingMachine
==============
## 資料結構 project2 掃地機器人

- Project Objective
    - Apply the knowledge learned from the course of data structures and implement an efficient robot floor cleaning algorithm.
-  Project Description
    - You are to design an optimal floor cleaning algorithm to drive the robot. The floorplan is described as an 𝑚 ∗ 𝑛 matrix, in which each cell is marked with one the following status.
    1. “1” indicates an obstacle, which normally is a wall.
    2. “0” indicates a free space to be cleaned.
    3. “R” indicates where the robot is placed initially. This is also where the robot can be recharged.</br>
    - **string**The robot is to follow these rules
    1. Always starts from the cell marked “R”.
    2. Needs to clean every free cell “0” on the floor.
    3. Cannot move into or cross any obstacle cell “1” or move outside the floor boundary.
    4. Can only move up, down, left and right.
    5. The robot is initially charged with a battery life “B”, which means the robot can move B steps before it runs out of power. Moving from one cell to next cell is counted as one step.</br>
    Note that the range of battery life “B” is 0～2147483647 
    6. Needs to return for recharge before running out battery. Each recharge fully restores the battery life “B”.
    7. After cleaning all free cells, needs to return to the cell “R” for recharge.

