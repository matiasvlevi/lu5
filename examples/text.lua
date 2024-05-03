x = 0;

function setup()
    createWindow(600, 600); 

    loadFont("/usr/share/fonts/TTF/Hack-Regular.ttf");
end

function draw()
    background(51);

    fill(255, 150, 50);
    textSize(48);
    text('Text demo', 30, 10);
    
    fill(190, 255, 40);
    textSize(32);
    text('Position: ' .. x, 30, 40);

    fill(67, 165, 210);
    square(x, 200, 32);

    if (x > width) then
        x = 0
    else
        x = x + 4;
    end
end

