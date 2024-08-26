local tick = 0;
function setup()
    createWindow(800, 800, GL3D);
    ship = loadModel('examples/models/ship.obj');
end

function draw() 
    background(51);

    orbitControl();

    stroke(200);
    fill(100);

    if (mouseIsPressed) then
        noFill();
        stroke(0, 255, 0);        
    end
    debugMode();

    translate(0, 0, 0);
    
    rotateX(180);
    rotateY(180);
    scale(30)
    model(ship);

end