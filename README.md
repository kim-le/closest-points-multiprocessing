# Closest Pair of Points Program with Multi-Processing
This is a program created in my Software Tools and Systems Programming class at the University of Toronto Mississauga. Its purpose is to solve the distance between the closest pair of points on a 2D plane. The program includes a naive brute-force solution, a single-process recursive solution, and a multi-process recursive solution that uses multiple CPU cores in parallel. Based on the [Closest Pair of Points Problem](https://en.wikipedia.org/wiki/Closest_pair_of_points_problem "Closest Pair of Points Problem").

## Recursive Divide-and-Conquer Approach
The problem can be solved in roughly O(nlogn) time using the following recursive divide and conquer approach:
1. Sort the points in ascending order by their x-coordinates.
2. Split the list of points into two equal-sized halves. This is like drawing a vertical line through the plane to divide the points into a left-hand-side and right-hand-side, each containing an equal number of points.
3. Solve the problem recursively on the left and right halves.
4. Find the distance between the closest pairs of points where one point lies on the left-hand-side, and the other point lies on the right-hand-side. This can be done in linear time.
5. The final answer is the minimum among the distance between the closest pair of points on the left-hand side, distance between the closest pair of points on the right-hand side, and distance between the closest pair of points where one point is on the left-hand-side and the other point is on the right-hand side.
