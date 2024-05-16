function setup()
    createWindow(400, 400);
end

function draw()
    background(51);

    textSize(32);
    text("Events example", 20, 40);

    textSize(18);
    text("Press any key, or mouse button and", 20, 76);
    text("trigger logs in the console", 20, 95);
end

function mousePressed(button)
    print("Mouse was pressed", button);
end

function mouseReleased(button)
    print("Mouse was released", button);
end

function keyPressed(key)
    print("Key pressed", key);
end

function keyReleased(key)
    print("Key released", key);
end

function keyHeld(key)
    print("Key held", key);
end
