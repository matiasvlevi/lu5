
function setup()
    createWindow(600, 600); 

    -- Replace these with your font paths
    font_arial = loadFont("./examples/fonts/Arial.ttf");
    font_times = loadFont("./examples/fonts/Times.ttf");
    font_hack = loadFont("./examples/fonts/Hack.ttf");
end

function draw()
    background(51);

    textFont(font_arial);
    fill(255, 150, 50);

    textSize(32);
    text('This is Arial', 30, 10);

    textSize(16);
    text('Same font but in tiny', 30, 42);

    textFont(font_times);
    fill(190, 255, 40);

    textSize(32);
    text('This is Times New Roman', 30, 80);

    textSize(22);
    text('And this is some smaller text', 30, 112);

    textFont(font_hack);
    fill(255, 40, 190);

    textSize(32);
    text('This is the Hack font', 30, 150);

    textSize(22);
    text('Same as above but smaller', 30, 192);
end

