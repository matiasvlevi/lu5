local tick = 0;
function setup()
    createWindow(800, 800, GL3D);
    ship = loadModel('examples/models/ship.obj');
    
    debugMode(true);
end

function draw() 
    background(51);

    orbitControl();

    push();

    stroke(200);
    fill(100);

    if (mouseIsPressed) then
        noFill();
        stroke(0, 255, 0);
    end

    rotateX(180);
    rotateY(180);
    
    scale(30);
    model(ship);
    
    pop();

end