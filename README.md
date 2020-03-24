# fractol
This project is meant to create graphically fractals.
Project based on SDL2 2.0.8 library, check whether the library is available on your system.
This version uses the **GPU** available on your system **(OpenCL)**.  
The number of iterations is set in **header file (#define ITER)**, **more iterations - more calculations!**

## Control:
- ### Movement
   + #### left right up down
- ### Scale of actual mouse position
   + #### mouse wheel
- ### Change ITER count
   + #### + -
- ### Change color palette
   + #### PGUP PGDOWN
- ### Reset
   + #### enter
- ### Change fractals
   + #### 1, 2, 3, 4, 5, 6, 7, 0
- ### Show control
   + #### H

## Control for julia
  - ### Movement, change iter and change color unchanged.
  In mode "Julia" firsty you must select fractal using the rotation mouse, after you must press space\
  that you lock curently fractal. Now you can use the features described earlier.\
  If you press space again, you will return to the first step.
