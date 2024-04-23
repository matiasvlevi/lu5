
function setup()
    createWindow(600, 600);
end

function draw()
    background(51);

    fill(255, 0, 0);
    circle(mouseX, mouseY, 32);

    fill(255, 100, 0);
    circle(mouseX+32, mouseY, 32);


    --print(mouseX, mouseY);
end
