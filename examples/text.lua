
function setup()
    createWindow(600, 600); 

    -- Replace these with your font paths
    font_arial = loadFont("/usr/share/fonts/TTF/Arial.TTF");
    font_times = loadFont("/usr/share/fonts/TTF/Times.TTF");
    font_georgia = loadFont("/usr/share/fonts/TTF/Georgia.TTF");
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

    textFont(font_georgia);
    fill(255, 40, 190);

    textSize(32);
    text('This is Georgia', 30, 100);

    textSize(22);
    text('Same as above but smaller', 30, 120);

end

