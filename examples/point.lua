

function setup()
    createWindow(400, 400);
end

function draw()
    background(51);

    textSize(18);
    text('Point example, move the mouse around', 40, 40);

    strokeWeight(2);
    stroke('yellow');

    point(mouseX, mouseY);
end