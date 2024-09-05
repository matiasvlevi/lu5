offset = 0;
side_margin = 50;

function setup()
    createWindow(400, 400); 

    size = width/(#colors-2);
    margin = size/4;
    
    textSize(26);
end

function draw()
    background(24);

    for i=1, #colors do
        fill(colors[i]);

        local ypos = ((i - 1) * size + offset) % (height + size) - size + margin;
        rect(
            side_margin,
            ypos,
            height - side_margin*2,
            size - margin
        );

        if (colors[i] == 'black') then
            fill(255, 155);
        else
            fill(0, 100);
        end
        text(colors[i], side_margin + 16, ypos + 28);
    end

    offset = offset + 2; 
end

