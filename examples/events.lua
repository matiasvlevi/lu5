function setup()
    createWindow(400, 400);
end

function draw()
    background(51);
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
