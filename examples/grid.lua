
step = 40;

function setup()
    createWindow(400, 400, 0);
end

function draw()
    background(51);

    for i=0, width, step do
        for j=0, height, step do
                
            if (
                mouseX > i-step/2 and 
                mouseX < i+step/2 and 
                mouseY > j-step/2 and 
                mouseY < j+step/2
            ) then
                fill(255, 155, 50);
                print('Position', i, j)
            else
                fill(155, 50, 255);
            end

            circle(i, j, step);
        end
    end
end
