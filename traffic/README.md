# Traffic Problem

Imagine you have a crossroad where two traffic lines intersect perpendicularly. There are traffic lights controlling vehicle and pedestrian flows. Also, each corner of the intersection has traffic lights. These lights regulate the flow of vehicles and pedestrians at the intersection.

Problem Conditions:

1) There are four traffic lights, one for each traffic direction (north, south, east, west).

2) Each traffic light has two states: green (allowing traffic flow) and red (stopping traffic).

3) Pedestrians can press a button at each corner to request to cross.

4) When a pedestrian presses the button, the vehicle traffic lights switch to red, and pedestrian traffic is allowed. Traffic in all directions stops to ensure the safe crossing of pedestrians.

5) After pedestrians cross, the traffic lights will switch back to their original state, allowing vehicle traffic to resume.

6) Traffic lights must coordinate their state changes to prevent conflicts and ensure the simultaneous activation of green lights does not lead to collisions.

Your task is to propose a solution using semaphores and monitors to manage the traffic lights and pedestrian crossings at the intersection. Ensure that your solution provides a correct and safe sequence of events for both pedestrians and vehicles, preventing potential conflicts between traffic light states.