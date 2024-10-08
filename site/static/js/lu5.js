

const lu5 = {
    canvas: null,
    gl: null,
    not_supported() {
      if (lu5.gl === null) {
        alert("Unable to initialize WebGL. Your browser or machine may not support it.");
        return true;
      }
      return false;
    },
    createCanvas(w=100, h=100, id="lu5canvas") {

        lu5.canvas = document.querySelector(`#${id}`);
        if (!lu5.canvas) {
          console.error(`Create a canvas element with an id of ${id}`);
          return;
        }

        // Initialize the GL context
        lu5.gl = lu5.canvas.getContext("webgl");
        if(lu5.not_supported()) return;

        lu5.canvas.width = w;
        lu5.canvas.height = h;

        lu5.gl.viewport(0, 0, w, h);
    },
    background(r=0, g=0, b=0) {
        if(lu5.not_supported()) return;

        lu5.gl.clearColor(r, g, b, 1.0);
        lu5.gl.clear(lu5.gl.COLOR_BUFFER_BIT);
    }
}