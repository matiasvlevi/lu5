

function setup()
    createWindow(800, 800, GL3D);
    frameRate(60);
end

function draw() 
    background(0);

    orbitControl();
    noFill();
    stroke(0, 255, 0);
    sphere(100, 50);

    push();
    rotateX(90);
    noFill();
    stroke(0, 255, 0)
    plane(400, 400)
    pop();
end