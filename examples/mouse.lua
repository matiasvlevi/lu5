
function setup()
    createWindow(600, 600);

    textSize(24);
end
time = 0;
function draw()
    background(51);

    fill(255);
    text('mouseX, mouseY variables track the mouse pointer', 20, 20);

    fill(255, 0, 0);
    circle(mouseX, mouseY, 80 * sin(time));
    time = time + 0.1;
end
