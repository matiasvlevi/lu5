function setup() 
    createWindow(400, 400, GL3D);
end
  
  function draw() 
    background(51);
    orbitControl();
        
    sphere(100);

  end