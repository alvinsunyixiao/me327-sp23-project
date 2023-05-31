/**
 * GUI for Haptic Orientation Display
 */

/* Initialize the variables here - start */

final float WINDOW_WIDTH = 800;
final float WINDOW_HEIGHT = 600;
final float OUTER_RADIUS = WINDOW_HEIGHT / 2 * 0.85;
final float INNER_RADIUS = WINDOW_HEIGHT / 2 * 0.60;
final float TICK_RADIUS = WINDOW_HEIGHT / 2 * 0.75;
final float USER_RADIUS = WINDOW_HEIGHT / 50;
final float OUTER_TICK_LENGTH = WINDOW_HEIGHT / 100;
final float INNER_TICK_LENGTH = WINDOW_HEIGHT / 120;
final float CENTER_X = OUTER_RADIUS + (WINDOW_HEIGHT / 2 - OUTER_RADIUS);
final float CENTER_Y = WINDOW_HEIGHT / 2;

float angle_target;
float angle_mouse;
float angle_user_inv = PI / 2;
boolean angle_is_set = false;

/* Initialize the variables here - end */

void drawAngledLine(float angle, float start_radius, float end_radius) {
  final float x_start = CENTER_X + cos(angle) * start_radius;
  final float x_end = CENTER_X + cos(angle) * end_radius;
  final float y_start = CENTER_Y + sin(angle) * start_radius;
  final float y_end = CENTER_Y + sin(angle) * end_radius;
  line(x_start, y_start, x_end, y_end);
}


void drawHint() {
  textSize(22);
  fill(134, 150, 254);
  textAlign(CENTER, BOTTOM);
  if (!angle_is_set) text("Click to set a target!\n", 0.82 * width, 0.82 * height); 
  else text("Press s to remove target!\n", 0.82 * width, 0.82 * height);
}

void drawBackground() {
  // draw outer circle
  fill(82, 109, 130);
  noStroke();
  circle(CENTER_X, CENTER_Y, OUTER_RADIUS * 2);
  
  // draw inner circle
  fill(174, 218, 211, 60);
  noStroke();
  circle(CENTER_X, CENTER_Y, INNER_RADIUS * 2);
  
  // draw outer ticks
  for (int a = 0; a < 360; a+=5) {
    stroke(221, 230, 237);
    strokeWeight(2);
    float tick_l = OUTER_TICK_LENGTH;
    if (a % 30 == 0) {
      stroke(234, 244, 254);
      strokeWeight(3);
      tick_l += 3;
    }
    drawAngledLine(radians(a), TICK_RADIUS - tick_l, TICK_RADIUS + tick_l);
  }
}

void drawText() {
  final float angle = angle_is_set ? angle_target : angle_mouse;
  textSize(25);
  fill(234, 244, 254);
  textAlign(CENTER, BOTTOM);
  text("The target angle is :" + "\n", 0.82 * width, 0.89 * height); 
  String def_a_str;
  textSize(50);
  def_a_str = str(round(degrees(angle) + 90)) + "\u00b0";
  if (round(degrees(angle) + 90) > 180 && round(degrees(angle) + 90) <= 270) {
    def_a_str = str(round(degrees(angle) - 270)) + "\u00b0";
  }
  text(def_a_str, 0.82 * width, 0.93 * height); 
}

void drawAndUpdateMouse() {
  // compute angle from mouse position
  angle_mouse = atan2(mouseY - CENTER_Y, mouseX -CENTER_X);
  
  // draw compass line
  strokeWeight(2);
  stroke(39, 55, 77);
  drawAngledLine(angle_mouse, 0, TICK_RADIUS);
  
  // draw compass tip
  strokeWeight(5);
  if (mousePressed) {
    stroke(205, 176, 255);
  } else {
    stroke(157, 178, 191);
  }
  drawAngledLine(angle_mouse, TICK_RADIUS - 12, TICK_RADIUS + 12);
}

void drawUser() {
  // draw the user circle
  float x_user = CENTER_X + cos(-angle_user_inv) * 0.92 * INNER_RADIUS;
  float y_user = CENTER_Y + sin(-angle_user_inv) * 0.92 * INNER_RADIUS;
  fill(250, 0, 0, 120);
  noStroke();
  circle(x_user, y_user, USER_RADIUS * 2);
  
  // draw inner ticks that align with user circle
  for (float a = 0; a < 360; a+=5) {
    stroke(221, 230, 237, 60);
    strokeWeight(2);
    float tick_l = INNER_TICK_LENGTH;
    if (a % 30 == 0) {
      stroke(234, 244, 254, 60);
      strokeWeight(3);
      tick_l += 3;
    }
    drawAngledLine(radians(a) - angle_user_inv, INNER_RADIUS - 2 * tick_l, INNER_RADIUS - 0.3 * tick_l);
  }
}

void drawTarget() {
  stroke(205, 176, 255);
  strokeWeight(8);
  drawAngledLine(angle_target, TICK_RADIUS - 12, TICK_RADIUS + 12);
}

void setup() {
  size(800, 600);
  noSmooth();
  fill(126);
}

void draw() {
  background(39, 55, 77);
  
  /* outer circle - define the orientation  -- start */
  
  // hint message
  drawHint();
  drawText();
  
  // draw background
  drawBackground();
  
  // draw mouse follower and update angle of mouse
  drawAndUpdateMouse();
  
  // draw target angle highlight
  if (angle_is_set) {
    drawTarget();
  }
  
  // draw user
  drawUser();
} //<>//

void mouseReleased() {
  angle_target = angle_mouse;
  angle_is_set = true;
}

void keyPressed() {
  if (key == CODED) {
    if (keyCode == RIGHT) {
      angle_user_inv -= radians(1);
    } else if (keyCode == LEFT) {
      angle_user_inv += radians(1);
    } 
  } else if (key == 's') {
    angle_is_set = false;
  }
}
