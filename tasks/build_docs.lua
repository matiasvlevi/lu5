local Components = require("./tasks/lib/components");
local Handlebars = require("./tasks/lib/handlebars");
local Parse      = require("./tasks/lib/parse");
local Minify     = require("./tasks/lib/minify")
local fs         = require("./tasks/lib/file");

doc_source_path = './src/bindings/';
template_path = './tasks/templates/';

assets_source_path = template_path .. 'assets/';

doc_path    = './docs/';
asset_path  = doc_path .. 'assets/';

-- Minify CSS
local css = Minify.css(fs.read_file(template_path .. 'css/style.css'));
fs.write_file(asset_path .. 'style.css', css);

local css_hljs = Minify.css(fs.read_file(template_path .. 'css/lu5-hljs-theme.css'));
fs.write_file(asset_path .. 'lu5-hljs-theme.css', css_hljs);


-- Minify JS
local js  = Minify.js(fs.read_file(template_path .. 'js/index.js'));
fs.write_file(asset_path .. 'index.js', js);

local js_hljs  = (fs.read_file(template_path .. 'js/hljs.min.js'));
fs.write_file(asset_path .. 'hljs.min.js', js_hljs);

function find_headers(str)
    return string.find(str, "%.h");
end

source_files = fs.find_files_in_dir(doc_source_path, find_headers);

local nav = Components.Panel(source_files, 'light');

-- Read template
local page_template_file = io.open('./tasks/templates/page.handlebars', 'r');
local page_template = page_template_file:read('a*');  

local Modules = {};

-- Parse all headers and generate static pages
for i, filename in pairs(source_files) do
    local module_name = split(filename, '.')[1];
    
    
    -- Read header file source
    local source = fs.read_file(doc_source_path .. filename);

    Modules[module_name] = Parse.header(source);

    -- Formatting module page
    local static_docs = Handlebars.use_template(page_template, {
        filename = module_name,
        body = Components.Module(Modules[module_name]),
        nav  = nav,
        version = VERSION
    });

    fs.write_file(doc_path .. module_name .. '.html', static_docs);
end

-- Formatting homepage
local homepage_name = 'Reference'; 
local static_homepage = Handlebars.use_template(page_template, {
    filename = homepage_name,
    nav = nav, 
    body = Components.Index(Modules, 'dark'),
    version = VERSION
});

fs.write_file(doc_path .. 'index.html', static_homepage);

-- Copy all assets (!!! as text)
local asset_files = fs.find_files_in_dir('./tasks/templates/assets/');
for i, filename in pairs(asset_files) do
    fs.write_file(asset_path .. filename, fs.read_file(assets_source_path .. filename));
end
