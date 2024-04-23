function setup()
    createWindow(400, 400);
end

function draw()
    background(51);
    if (mouseIsPressed) then
        fill(255, 155, 50);
    else
        fill(155, 50, 255);
    end

    circle(mouseX, mouseY, 32);
end


