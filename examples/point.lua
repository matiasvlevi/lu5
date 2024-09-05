

function setup()
    createWindow(800, 800);
end

function draw()
    background(51);
    text('Point example, move the mouse around', 40, 40);

    strokeWeight(2);
    stroke('yellow');

    point(mouseX, mouseY);
end