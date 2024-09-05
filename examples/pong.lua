local x = 350;
local y = 50;

local vx = 3;
local vy = 7;

local ball_size = 32;
local paddle_size;

local score = 0;

function setup()
    createWindow(800, 800);
    rectMode(CENTER);

    paddle_size = width // 5;
    paddle_height = height // 24;
end

function draw()
    background(51);

    local px = constrain(mouseX, paddle_size/2, width - paddle_size/2);
    local py = height - 100;

    rect(px, py, paddle_size, paddle_height);

    push();
    fill(255, 0, 0);
    circle(px, py, 12);
    pop()

    fill(255);
    circle(x, y, ball_size);

    x = x + vx;
    y = y + vy;

    if (x > width-ball_size/2 or x < ball_size/2) then
        vx = -vx;
    end

    if (y < ball_size/2) then
        vy = -vy;
        score = score + 1;
    end

    if (y > height + ball_size) then
        push();
        textAlign(CENTER);
        textSize(72);
        fill(255);
        text("GAME OVER", width / 2, height / 2);

        pop();
        noLoop();
    end

    if (
        x > px - paddle_size / 2 and 
        x < px + paddle_size / 2 and 
        y + ball_size / 2 + paddle_height / 2 > py and 
        y - ball_size / 2 - paddle_height / 2 < py) then
        vy = -vy;
    end
    text("Score: " .. score, 40, 40);
end
