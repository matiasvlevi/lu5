local x = 200;
local y = 200;
local vx = 1;
local vy = -1;

function setup()
    createWindow(400, 400);

    img = loadImage('examples/images/cat.jpg');
    img_a = img:crop(150, 150, 125, 200);
    img_b = Image.crop(img, 200, 228, 100, 100);

    print('Original size: ', img.width, img.height);
    print('Image A Cropped size: ', img_a.width, img_a.height);
    print('Image B Cropped size: ', img_b.width, img_b.height);
    
end

function draw() 
    background(51);

    image(img, 0, 0);
    image(img_a, x, y);
    image(img_b, 20, 20);

    fill(51);
    textSize(36);
    text('Crop images', 20, height-10);

    x = x + vx;
    y = y + vy;

    if (x > width-125 or x < 0) then
        vx = -vx;
    end

    if (y > height-200 or y < 0) then
        vy = -vy;
    end
end
