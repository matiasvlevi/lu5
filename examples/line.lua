
prevX = 0;
prevY = 0;

function setup()
    createWindow(600, 600); 
end

function draw()
    background(51);

    text('Click & Drag the mouse', 30, 30);


    strokeWeight(12);
    stroke(255);
    if (mouseIsPressed) then
        line(prevX, prevY, mouseX, mouseY);
    else
        circle(mouseX, mouseY, 6);
    end
end

function mousePressed()
    prevX = mouseX;
    prevY = mouseY;
end

