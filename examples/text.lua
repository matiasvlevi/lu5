counter = 0;

function setup()
    createWindow(400, 400); 
end

function draw()
    background(51);

    fill(255, 150, 50);
    textSize(32);
    text('Text demo', 30, 10);
    
    fill(190, 255, 40);
    textSize(18);
    text('Position: ' .. round(counter), 30, 40);

    fill(67, 165, 210);
    square(counter, 200, 32);

    counter = (counter + 4) % width;
end

