import processing.serial.*;
import cc.arduino.*;

int W = 800;
int H = 800; 

Serial port;
float Phi;
float Theta;
float Psi;

int cubeSize = 70; 
int numCubes = 3;
int spacing = 2; 

int[][][] cubeColors;

void setup() {
  size(800, 800, P3D);
  rectMode(CENTER);
  smooth();
  strokeCap(SQUARE); 

  background(255); 

  println(Serial.list());
  port = new Serial(this, Serial.list()[0], 115200);
  port.bufferUntil('\n');

  cubeColors = new int[numCubes][numCubes][numCubes];

  // Initialize the cube colors
  for (int x = 0; x < numCubes; x++) {
    for (int y = 0; y < numCubes; y++) {
      for (int z = 0; z < numCubes; z++) {
        cubeColors[x][y][z] = color(random(255), random(255), random(255));
      }
    }
  }
}

void draw() {
  background(255);
  translate(W / 2, H / 2);

  // Rotate the entire grid
  rotateX(radians(Theta));
  rotateY(radians(Phi));
  rotateZ(radians(Psi));

  // Draw the grid of cubes
  for (int x = 0; x < numCubes; x++) {
    for (int y = 0; y < numCubes; y++) {
      for (int z = 0; z < numCubes; z++) {
        pushMatrix();
        translate((x - numCubes / 2) * (cubeSize + spacing),
          (y - numCubes / 2) * (cubeSize + spacing),
          (z - numCubes / 2) * (cubeSize + spacing));
        fill(cubeColors[x][y][z]);
        box(cubeSize);
        popMatrix();
      }
    }
  }
}

void serialEvent(Serial port) 
{
  String input = port.readStringUntil('\n');
  if (input != null) {
    input = trim(input);
    String[] values = split(input, " ");
    if (values.length == 3) {
      float phi = float(values[0]);
      float theta = float(values[1]);
      float psi = float(values[2]);
      Phi = phi;
      Theta = theta;
      Psi = psi;
    }
  }
}