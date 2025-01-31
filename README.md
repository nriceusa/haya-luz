# Haya Luz

Compilation command: `g++ -std=c++11 Main.cpp -o haya-luz`\
Execution command: `./haya-luz SampleScenes/Test.scene`

Scene file format key:
```
SKY S R G B
CAMERA Ox Oy Oz Tx Ty Tz FOV
DIRECTIONAL_LIGHT X Y Z R G B S
POINT_LIGHT X Y Z R G B S
MATERIAL num KdR KdG KdB KsR KsG KsB KeR KeG KeB Kd Kt Kg Ke
SPHERE mat_num X Y Z R
TRIANGLE mat_num X Y Z X Y Z X Y Z
POLYGON mat_num num_verts X Y Z ... X Y Z 
```
