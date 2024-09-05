function setup() 
    createWindow(400, 400, GL3D);
end
  
  function draw() 
    background('#461164');
    orbitControl();
        
    fill('#d49af7');
    stroke('#AA36EF');
    strokeWeight(2);
    sphere(180);

  end