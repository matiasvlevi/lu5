
function setup()
    createWindow(400, 400); 

    size = width/#colors;
end

function draw()
    background(0);

    for i=1, #colors do
        fill(colors[i]);
        rect((i-1)*size - size, 0, size, height);
    end
end

