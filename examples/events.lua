function setup()
    createWindow(400, 400);
end

function draw()
    background(51);

    textSize(32);
    text("Events example", 20, 50);

    textSize(18);
    text("Press any key, or mouse button and", 20, 86);
    text("trigger logs in the console", 20, 105);
end

function mousePressed(button)
    print("Mouse was pressed", button);
end

function mouseReleased(button)
    print("Mouse was released", button);
end

function keyPressed(key, keyCode)
    print("Key pressed", key, keyCode);
end

function keyReleased(key, keyCode)
    print("Key released",  key, keyCode);
end

function keyHeld(key)
    print("Key held", key);
end

function mouseWheel(delta)
    print("Scroll", delta);
end