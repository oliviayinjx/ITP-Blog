//https://editor.p5js.org/oliviayinjx/sketches/wHVhuS4bB

let size = 30;
function setup() {
  createCanvas(500, 500);
}

function draw() {
  background(0);
   
  colorMode(HSB);
  noStroke();
  translate (-size,-size);
  //space between rectangles is 35
  for (let i = 0; i < width; i +=35){
    for (let j = 0; j < height; j +=35){
      
      push();
      //to rotate around its own origin
      translate(i+size,j+size);
      //angle between extended lines between mouse position and each rect
      let a = atan2(mouseY - height / 2+i , mouseX - width / 2+j);
      //map color to make it work with the position
      let c = map(a,0,2,0,255);
      fill(c,50,80);
      //print(a);
      rotate(a);
      rect(0,0, size, size);

      pop();
      
    }
  }
}
