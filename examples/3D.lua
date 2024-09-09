

function setup()
    createWindow(800, 800, GL3D);
    frameRate(60);
end

function draw() 
    background(0);

    orbitControl();

    fill(0, 255, 0);
    text('Drag the mouse around', 40, 40);

    push();
    noFill();
    stroke(0, 255, 0);
    translate(-90, 0, 0);
    sphere(30);
    pop();

    push();
    noFill();
    stroke(0, 255, 0);
    translate(0, 0, 0);
    cylinder(30, 60);
    pop(0);

    push();
    noFill();
    stroke(0, 255, 0);
    translate(90, 0, 0);
    box(50, 60);
    pop(0);

    push();
    translate(0, 32, 0);
    rotateX(90);
    fill(51)
    plane(400, 400);
    pop();

end
