
local prevX = 0;
local prevY = 0;

local weight = 12;

function setup()
    createWindow(600, 600); 
end

function draw()
    background(51);

    textSize(32)
    text('Click & Drag the mouse', 30, 60);

    textSize(22)
    text('Use the mouse wheel to change the stroke weight', 30, 95);

    if (mouseIsPressed) then
        stroke(255);
        strokeWeight(weight);
        line(prevX, prevY, mouseX, mouseY);
    else
        noStroke();
        circle(mouseX, mouseY, weight);
    end
end

function mousePressed()
    prevX = mouseX;
    prevY = mouseY;
end

function mouseWheel(delta)
    weight = weight + delta * 3;

    weight = constrain(weight, 1, 100);
end

