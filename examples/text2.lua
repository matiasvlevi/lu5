
function setup()
    createWindow(400, 400);
end

function draw()
    background(51);

    for i=1, 3 do
        push();
        textAlign(CENTER);
        textSize(20 * i);
        fill(255);
        text("Left Text", width/2, i * i * 16 + 240);
        circle(width/2, i * i * 16 + 240, 3);
        pop();
    end
end

