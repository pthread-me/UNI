- We know that simplex attempts to gradually increase the value of non-basic variables, one at a time, while 
    maintaining all the constarints until it can no longer push the objective function value any higher. By creating
    equivalent LPs through pivoting and applying row operations

- Given a tablue where at least one of the objective function coefficients 
    is positive, we can increase the value of the coefficient's corresponding variable (by moving it into the basis),
    which increases the objective function value (since z >= 0), and modifying the values of the basis to maintain the constarints.

- Notice however that increasing the value of a non-basic variable whos coefficient is negative decreases the objective function value.
- That is, once all objective function coefficients become non-positive, then increasing the value of the variables will either not change the 
    obj func value or reduce it.

- So we have it that the objective function value of the equivalent LP represented by the tablue can not be increased any further without 
    breaking any of the non-negativitey constarints.
- Now assume that there exists a feasible solution of the original LP  
- The differnce between a Basic feasible solution an a feasible solution is that BFS's are solutions in which only basic variables
    have non-zero coefficients. (all basic have 0 coefficients, all non basic have non-zero)


