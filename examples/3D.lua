local tick = 0;
local speed = 20;

function setup()
    createWindow(800, 800, GL3D);
end

function draw() 
    background(51);

    orbitControl();
    debugMode();

    noFill();
    stroke(80, 255, 50);
    strokeWeight(4);

    box(60);
end