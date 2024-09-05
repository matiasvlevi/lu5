

function setup()
    createWindow(400, 400);
end

function draw()
    background(51);

    textSize(20);
    
    text('Move the mouse horizontally', 40, 40);


    strokeWeight(12);
    stroke(0);
    
    arc(200, 200, 120, 120, 0, map(mouseX, 0, 400, 0, TWO_PI));
end