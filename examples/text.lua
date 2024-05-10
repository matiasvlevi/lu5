
function setup()
    createWindow(600, 600); 

    -- Replace these with your font paths
    font_arial = loadFont("./examples/fonts/Arial.ttf");
    font_times = loadFont("./examples/fonts/Tims.ttf");
    font_hack = loadFont("./examples/fonts/Hack.ttf");

	print(font_arial, font_times, font_hack)
end

function draw()
    background(51);

    textFont(font_arial);
    fill(255, 150, 50);

    textSize(32);
    text('This is Arial', 30, 10);

    textSize(16);
    text('Same font but in tiny', 30, 30);
    
    textFont(font_times);
    fill(190, 255, 40);

    textSize(32);
    text('This is Times New Roman', 30, 50);

    textSize(22);
    text('And this is some smaller text', 30, 70);

    textFont(font_hack);
    fill(255, 40, 190);

    textSize(32);
    text('This is the Hack font', 30, 100);

    textSize(22);
    text('Same as above but smaller', 30, 120);

end

