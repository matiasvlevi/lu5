counter = 0;

function setup()
    createWindow(400, 400); 
end

function draw()
    background(51);
    text('Text demo', 30, 10);
    text('Counter: ' .. counter, 30, 40);

    counter = (counter + 1) % 100;
end

