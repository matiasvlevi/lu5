local luax       = require('./tasks/lib/luax');
local Parse      = require("./tasks/lib/parse");
local Minify     = require("./tasks/lib/minify");
local fs         = require("./tasks/lib/file");

local Config     = require('./tasks/siteconfig');

-- Components
local RootLayout = require('./tasks/lib/components/layout/RootLayout');
local Home       = require('./tasks/lib/components/Home');
local Reference  = require('./tasks/lib/components/Reference');
local Module     = require('./tasks/lib/components/Module');
local HeaderPanel= require('./tasks/lib/components/Navigation');

local ver = require('./tasks/lib/get_tags');

-- Find documentation header files
source_header_files = fs.find_files_in_dir(Config.build.source.headers, function (str)
    return string.find(str, "%.h");
end);

fs.mkdir(Config.build.dest .. '/' .. 'latest');

-- Parse all headers and generate static pages
local modules = {};
for i, filename in pairs(source_header_files) do
    -- Remove file extention and prefix
    local module_name = luax.split(filename, '.')[1];
    module_name = module_name:gsub('lu5%_', '');

    local source = fs.read_file(Config.build.source.headers .. '/' .. filename);


    local module_title = source:match("/%*%*.+%@module%s+(.-)%s*%*/")
    if (module_title == nil) then 
        module_title = module_name; 
    end



    local methods = Parse.header(source);
    
    if (#methods == 0) then
        print('Skipping: ', filename);
    else

        table.insert(modules, {
            name=module_title,
            source=module_name,
            methods=methods
        });
    end
end


-- Format into webpage for Each header file (module)
local documented_source_files = luax.map(modules, function(mod) return mod.name end)
for i, mod in pairs(modules) do

    local html = RootLayout({
        page_name=mod.name,
        page_source=mod.source,
        version=true,
        root="../../",
        media=Config.media,
        meta=Config.metadata,
        ga=Config.ga,
        nav=Navigation({
            root="../",
            class="light",
            modules=modules 
        }),
    }, luax('', {
        Module(mod)
    }));

    -- Formatting module page
    local page_dir   = Config.build.dest .. '/latest/' .. mod.source;
    fs.mkdir(page_dir)
    fs.write_file(page_dir .. '/index.html', html, false);

    -- Write in specific version
    local page_dir_v = Config.build.dest .. '/v'.. VERSION .. '/' .. mod.source;
    fs.mkdir(page_dir_v)
    fs.write_file(page_dir_v .. '/index.html', html, true);
end

local reference_html = RootLayout({
    page_name='Reference',
    version=true,
    root="../",
    media=Config.media,
    meta=Config.metadata,
    ga=Config.ga,
    nav=Navigation({ 
        class="light",
        root="./",
        modules=modules
    }),
}, Reference({ 
    modules=modules 
}));

local homepage_html = RootLayout({
    page_name='Interpreter for Creative Coding',
    title='lu5',
    version=false,
    root="./",
    media=Config.media,
    meta=Config.metadata,
    ga=Config.ga,
}, 
luax('div', {
    --luax('canvas', {id="lu5canvas"}),
    Home({
        versions=ver.get_tags(),
        root="./",
        media=Config.media,
        meta=Config.metadata,
    }),
    -- luax('script', {
    --     'lu5.createCanvas();',
    --     'lu5.background();',
    -- }),
})
)

-- Write reference page (Both in latest and version tag)
fs.write_file(Config.build.dest .. '/latest/index.html', reference_html, false);
fs.write_file(Config.build.dest .. '/v' .. VERSION .. '/index.html', reference_html, true);

-- Write homepage
fs.write_file(Config.build.dest .. '/index.html', homepage_html, true);

-- Copy & Minify source assets
Minify(Config.build.source.js, Minify.js, 
    Config.build.source.static .. '/' .. 'js', 
    Config.build.dest ..  '/' .. Config.media.assets
);
Minify(Config.build.source.css, Minify.css, 
    Config.build.source.static .. '/' .. 'css', 
    Config.build.dest .. '/' .. Config.media.assets
);

-- Copy all assets
local asset_files = fs.find_files_in_dir(Config.build.source.static .. '/' .. Config.media.assets);
for i, filename in pairs(asset_files) do
    fs.write_file(
        Config.build.dest .. '/' .. Config.media.assets .. '/' .. filename, 
        fs.read_file(
            Config.build.source.static .. '/' .. Config.media.assets .. '/' .. filename
        ),
        true
    );
end