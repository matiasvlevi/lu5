
step = 40;

function setup()
    createWindow(400, 400);
end

function draw()
    background(51);

    for i=0, width, step do
        for j=0, height, step do
                
            if (
                mouseX > i      and 
                mouseX < i+step and 
                mouseY > j      and 
                mouseY < j+step
            ) then
                fill(255, 155, 50);
            else
                fill(155, 50, 255)
            end

            circle(i, j, step);
        end
    end
end
