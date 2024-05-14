size = 48;

function setup()
    createWindow(400, 400);
    textSize(22);
end

function draw()
    background(51);

    fill(255);
    text('Click the mouse to', 10, 10);
    text('change the circle\'s size', 10, 32);

    if (mouseIsPressed) then
        size = 32
    else
        size = 48;
    end

    fill(255, 155, 50);
    circle(mouseX, mouseY, size);
end


