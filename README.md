# Floor Cleaning Robot
[Toc]
## Project Objective: 
>> Apply the knowledge learned from the course of data structures and implement an efficient robot floor cleaning algorithm.

## Project Description 
>> You are to design an optimal floor cleaning algorithm to drive the robot. The floorplan is described
as an **m*n** matrix, in which each cell is marked with one the following status.
1. “**1**” indicates an obstacle, which normally is a wall.
2. “**0**” indicates a free space to be cleaned.
3. “**R**” indicates where the robot is placed initially. This is also where the robot can be recharged.

>> The robot is to follow these rules:
1. Always starts from the cell marked “R”.
2. Needs to clean every free cell “0” on the floor.
3. Cannot move into or cross any obstacle cell “1” or move outside the floor boundary.
4. Can only move up, down, left and right.
5. The robot is initially charged with a battery life “B”, which means the robot can move B steps efore it runs out of power. Moving from one cell to next cell is counted as one step. Note that the range of battery life “B” is 0～2147483647.
6. Needs to return for recharge before running out battery. Each recharge fully restores the battery life “**B**”.
7. After cleaning all free cells, needs to return to the cell “**R**” for recharge.

## Test Case
>> Every student has to design and submit a test case prepared as a text file, named “**floor.data**”. The first line of the file contains three numbers, describing the number of rows **(m)**, the number of columns **(n)** and the battery life **(B)**. Following the first line, there shall be m lines and each line shall have n numbers, each represents the corresponding cell status. 

![](https://i.imgur.com/oOYVRgF.png)

>> This case describes a floorplan with cells of 7 rows and 10 columns. The battery life allows the robot to move 30 steps for each fully charged run. We assume the row index and column index all starts from 0. Therefore, initially the robot is placed at cell (6, 4). Note that R can beat any, but only one, location.

* Valid Test Case
>> Make sure your test case is valid. A valid test case should have at least one solution to clean every free cell. Invalid test case gets no score. The size of the floorplan should be no more than 1000*1000. Invalid test cases are listed below.
>> 
>> The following types of test cases are invalid.
1.  The test case should not contain any unreachable free cells or recharge cell. If a cell is unreachable if it is surrounded by obstacle cells.
2.  The test case should not contain any invalid cell parameter. For example, “**A**” is an invalid parameter.
![](https://i.imgur.com/3ZnxUqx.png)

## Output file
>> Output your optimized final floor cleaning path into a file named “final.path”. The first line should be the number of steps your algorithm used to finish the cleaning task and for the following lines, each should have two numbers i an j, representing the cell (i, j) walked subsequently by the cleaning robot.
>> 
![](https://i.imgur.com/15VJ3tN.png)

>> This example shows that the robot moves 6 steps. 

## Programming description

1. *Program Flow Chart:*
![](https://i.imgur.com/ZaPE0lx.png)

2. *Detailed Description: *

>> (一) 地圖(map)處理
>> (1) 利用BFS做從R處路徑參訪根據BFS特性，會針對鄰邊每個節點做完再參訪下個 節點。根據這個特性，就能了解到任一點到R須走幾步。
![](https://i.imgur.com/Z4cvUpM.png)

>> 假設R放置在中間，其他點的步數就能清楚知道，我將利用此步數尋找最短路徑回R。
>> (2) 建立每一行的ID每一行都有自己的ID並往下衍生直到遇到牆壁或本身已有ID。如此一來，機器人能夠辨識每條路是否屬於正在走的同一條路。
![](https://i.imgur.com/uRWBZ7e.png) ![](https://i.imgur.com/CQHcWn1.png)

>> buildTravelTree()便是用來製作ID的function將會對不是牆壁的節點做做ID的的設置設置 buildLevel()。但是實作上會發現，會有部分沒被設ID的狀況原因在於第一次設ID時，是從最上方開始建，底下是屬於尚未設ID的狀態。因此我當我全部buildLevel()完後，我會再做一次。
>> 功能與buildLevel()相似，但是多了與下一行ID比較的功能，沒被設ID的路 其ID是無限大因此能用來找到未被設ID的路。
>> (二) Machine的路徑規劃：
1. 此 function為主要function用來判斷與分析接下來該如何走訪路徑。
>> (a) 來回走過一遍一整列。
>> (b) 會再做一次參訪，但同時分析當上面或下面為同ID的路也就是為同一群的 路時，優先對其參訪。反之，會先儲存在stack的buffer裡(自己寫的當參訪完會從buffer裡對上下不同ID的路做參訪。如此遞迴下去。
>> 
2. 為找尋回R處的路。在map已經對地圖設置cost此節點回R處所需的電量。此時只要一直往cost比自己小的路走，一定能到達R點。
3. 在回R處的同時，會交由一陣列儲存其路經。當回到R時，在一剛剛的來時路走 原路回去，因為剛剛的路是最短路徑。
4. 一開始時建立一個Queue(自己寫的)存取Machine的走過路徑，才能在算完步數並輸出後在印出所有路徑。
