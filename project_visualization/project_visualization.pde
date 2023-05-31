/**
 * Mouse Press. 
 * 
 * Move the mouse to position the shape. 
 * Press the mouse button to invert the color. 
 */

/* Initialize the variables here - start */

float outer_r;
float inner_r;
float tick_r;
float cx, cy;
float def_x, def_y, def_angle;
float define_angle;
int flag = 0;

float user_a = 0;
boolean show_user_ori = true;
int counter;

/* Initialize the variables here - end */
 



void setup() {
  size(800, 600);
  noSmooth();
  fill(126);
  
  int radius = min(width, height) / 2;
  outer_r = radius * 0.85;
  inner_r = radius * 0.60;
  tick_r = radius * 0.75;
  
  // center position
  cx = outer_r + (height / 2 - outer_r);
  cy = height / 2;
  
}

void draw() {
  background(39, 55, 77);
  
  /* outer circle - define the orientation  -- start */
  
  // hint message
  textSize(20);
  fill(134, 150, 254);
  textAlign(CENTER, BOTTOM);
  if (flag == 0) text("Click to set!" + "\n", 0.82 * width, 0.82 * height); 
  else text("You're all set!" + "\n", 0.82 * width, 0.82 * height);
  
  fill(82, 109, 130);
  noStroke();
  ellipse(cx, cy, outer_r * 2, outer_r * 2);
  
  // draw the ticks  
  stroke(221, 230, 237);
  int tick_l = height/100;
  strokeWeight(2);
  for (int a = 0; a < 360; a+=5) {
    if (a % 30 == 0) {
      stroke(234, 244, 254);
      strokeWeight(3);
      tick_l = height/100 + 3;
    }
    float angle = radians(a);
    float x = cx + cos(angle) * tick_r;
    float y = cy + sin(angle) * tick_r;
    beginShape();
    vertex(x - cos(angle) * tick_l, y - sin(angle) * tick_l);
    vertex(x + cos(angle) * tick_l, y + sin(angle) * tick_l);
    endShape();
    stroke(221, 230, 237);
    tick_l = height/100;
    strokeWeight(2);
  }
  
  
  // define angle
  define_angle = atan2(mouseY - cy, mouseX -cx);
  strokeWeight(1);
  stroke(39, 55, 77);
  line(cx, cy, cx + tick_r * cos(define_angle), cy + tick_r * sin(define_angle));
  if (mousePressed) {
    stroke(205, 176, 255);
  } else {
    stroke(157, 178, 191);
  }
  
  HLine h1 = new HLine(cx + cos(define_angle) * tick_r, cy + sin(define_angle) * tick_r, define_angle);
  h1.update(); 
    
  if (flag == 0) {  
    textSize(25);
    fill(234, 244, 254);
    textAlign(CENTER, BOTTOM);
    text("The defined angle is :" + "\n", 0.82 * width, 0.89 * height); 
    String def_a_str;
    textSize(50);
    def_a_str = str(round(degrees(define_angle) + 90)) + "\u00b0";
    if (round(degrees(def_angle) + 90) > 180 && round(degrees(def_angle) + 90) <= 270) {
      def_a_str = str(round(degrees(def_angle) - 270)) + "\u00b0";
    }
    text(def_a_str, 0.82 * width, 0.93 * height); 
  }
  
  else {
    stroke(205, 176, 255);
    float h = height/100 * 2;
    strokeWeight(8);
    float x1, y1, x2, y2;
    x1 = cx + cos(def_angle) * tick_r - cos(def_angle) * h;
    y1 = cy + sin(def_angle) * tick_r - sin(def_angle) * h;
    x2 = cx + cos(def_angle) * tick_r + cos(def_angle) * h;
    y2 = cy + sin(def_angle) * tick_r + sin(def_angle) * h;
    line(x1, y1, x2, y2); 
    
    textSize(25);
    fill(234, 244, 254);
    textAlign(CENTER, BOTTOM);
    text("The defined angle is :" + "\n", 0.82 * width, 0.89 * height); 
    String def_a_str;
    textSize(50);
    def_a_str = str(round(degrees(def_angle) + 90)) + "\u00b0";
    if (round(degrees(def_angle) + 90) > 180 && round(degrees(def_angle) + 90) <= 270) {
      def_a_str = str(round(degrees(def_angle) - 270)) + "\u00b0";
    }
    text(def_a_str, 0.82 * width, 0.93 * height); 
  }
  
  /* outer circle - define the orientation -- end */
  
  
  /* inner circle - user's orientation  -- start */
  fill(174, 218, 211, 60);
  noStroke();
  ellipse(cx, cy, inner_r * 2, inner_r * 2);
  
  // draw the inner ticks 
  stroke(221, 230, 237, 60);
  int inner_tick_l = height/120;
  strokeWeight(2);
  for (float a = 0; a < 360; a+=5) {
    if (a % 30 == 0) {
      stroke(234, 244, 254, 60);
      strokeWeight(3);
      inner_tick_l = height/120 + 3;
    }
    float angle = radians(a + user_a);
    float x = cx + cos(angle) * inner_r;
    float y = cy + sin(angle) * inner_r;
    beginShape();
    vertex(x - cos(angle) * 2 * inner_tick_l, y - sin(angle) * 2 * inner_tick_l);
    vertex(x - cos(angle) * 0.3 * inner_tick_l, y - sin(angle) * 0.3 * inner_tick_l);
    endShape();
    stroke(221, 230, 237, 60);
    inner_tick_l = height/120;
    strokeWeight(2);
  }
  
  // draw the user ori
  if (counter % 40 == 0) show_user_ori = !show_user_ori;
  
  if (show_user_ori) {
    float x_user_a = cx + cos(radians(user_a - 90)) * 0.92 * inner_r;
    float y_user_a = cy + sin(radians(user_a - 90)) * 0.92 * inner_r;
    int user_ori_r = height/50;
    fill(250, 0, 0, 120);
    noStroke();
    ellipse(x_user_a, y_user_a, user_ori_r * 2, user_ori_r * 2);
  }
  
  counter ++;
  
  /* inner circle - user's orientation  -- end */
  
  
  
} //<>//

void mouseClicked() {
  def_x = cx;
  def_y = cy;
  def_angle = define_angle;
  if (flag == 0) {
    flag = 1;
  }
  else {
    flag = 0;
  }
}

void keyPressed() {
  if (key == CODED) {
    if (keyCode == RIGHT) {
      user_a += 1;
    } else if (keyCode == LEFT) {
      user_a -= 1;
    } 
  }
}

class HLine { 
  float xpos, ypos, h, a;
  HLine (float x, float y, float angle) {  
    ypos = y;
    xpos = x;
    a = angle;
  } 
  void update() {
    h = height/100 * 2;
    strokeWeight(5);
    line(xpos - cos(a) * h, ypos - sin(a) * h, xpos + cos(a) * h, ypos + sin(a) * h); 
  } 
} 
