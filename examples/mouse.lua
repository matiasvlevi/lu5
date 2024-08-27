time = 0;
MAX_SIZE = 25;

function setup()
    createWindow(600, 600);

    frameRate(60);
end

function draw()
    background(51);

    fill(255);
    
    textSize(24);
    text('mouseX, mouseY variables track the mouse pointer', 20, 20);

    textSize(20);
    text('pmouseY, pmouseY variables track the mouse position difference', 20, 60);

    fill(255, 0, 0);
    
    textSize(18);

    text('mouseX: ' .. mouseX, mouseX + MAX_SIZE * 2, mouseY - 85);
    text('mouseY: ' .. mouseY, mouseX + MAX_SIZE * 2, mouseY - 65);

    text('pmouseX: ' .. pmouseX, mouseX + MAX_SIZE * 2, mouseY - 25);
    text('pmouseY: ' .. pmouseY, mouseX + MAX_SIZE * 2, mouseY - 5);

    circle(mouseX, mouseY, MAX_SIZE * (sin(time)*0.5 + 1));
    time = time + 5*deltaTime;
end
