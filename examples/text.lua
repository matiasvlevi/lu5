
function setup()
    createWindow(800, 800); 

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
    text('This is Arial', 30, 50);

    textSize(16);
    text('Same font but in tiny', 30, 72);

    textFont(font_times);
    fill(190, 255, 40);

    textSize(32);
    text('This is Times New Roman', 30, 120);

    textSize(22);
    text('And this is some smaller text', 30, 152);

    textFont(font_hack);
    fill(255, 40, 190);

    textSize(32);
    text('This is the Hack font', 30, 190);
    circle(30, 190, 8);

    textSize(22);
    text('Same as above but smaller', 30, 232);

    for i=1, 3 do
        push();
        textAlign(LEFT);
        textSize(20 * i);
        fill(255);
        text("Left Text", width/2, i * i * 16 + 240);
        pop();
    end

    for i=1, 3 do
        push();
        textAlign(CENTER);
        textSize(20 * i);
        fill(255);
        text("Centered Text", width/2, i * i * 16 + 440);
        pop();
    end

    for i=1, 3 do
        push();
        textAlign(RIGHT);
        textSize(20 * i);
        fill(255);
        text("Right Text", width/2, i * i * 16 + 640);
        pop();
    end
end

