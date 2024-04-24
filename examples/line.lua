
prevX = 0;
prevY = 0;

function setup()
    createWindow(600, 600); 
end

function draw()
    background(51);

    strokeWeight(12);
    if (mouseIsPressed) then
        line(prevX, prevY, mouseX, mouseY);
    end
end

function mousePressed()
    prevX = mouseX;
    prevY = mouseY;
end

