local Components = require("./tasks/lib/components");
local Parse      = require("./tasks/lib/parse");
local Handlebars = require("./tasks/lib/handlebars");
local fs         = require("./tasks/lib/file");

source_path = './src/bindings/';
doc_path    = './docs/';

source_files = fs.find_headers_in_dir(source_path);
print(source_files);

local nav = Components.Panel(source_files);

-- Read template
local page_template_file = io.open('./tasks/templates/page.handlebars', 'r');
local page_template = page_template_file:read('a*');  

-- Parse all headers and generate static pages
for i, filename in pairs(source_files) do
    -- Read header file source
    local source = io.open(source_path .. filename .. '.h', 'r'):read('*a');

    local methods = Parse.header(source);
    
    -- Formatting module page
    local static_docs = Handlebars.use_template(page_template, {
        filename = filename,
        body = Components.Module(methods),
        nav  = nav,
        exit = Components.ExitButton()
    });

    fs.write_file(doc_path .. filename .. '.html', static_docs);
end

-- Formatting homepage
local homepage_name = 'Reference'; 
local static_homepage = Handlebars.use_template(page_template, {
    filename = homepage_name,
    nav = nav 
});

fs.write_file(doc_path .. 'index.html', static_homepage);