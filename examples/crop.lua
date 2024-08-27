function setup()
    createWindow(400, 400);

    img = loadImage('examples/images/cat.jpg');
    img_cropped = img:crop(0, 0, 200, 250);
end

function draw() 
    background(51);

    image(img, 0, 0);
    image(img_cropped, width-200, 0)
end