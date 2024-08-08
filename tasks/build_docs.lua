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
local Panel      = require('./tasks/lib/components/Panel');
local HeaderPanel= require('./tasks/lib/components/HeaderPanel');

local get_version_tags = require('./tasks/lib/get_tags');

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
    
    -- Read header source documentation
    modules[i] = {
        name= module_name,
        methods= Parse.header(fs.read_file(Config.build.source.headers .. '/' .. filename))
    };

    local html = RootLayout({
        page_name=module_name,
        version=true,
        root="../../",
        media=Config.media,
        meta=Config.metadata,
        ga=Config.ga,
        nav=HeaderPanel({ 
            class="light", headers=source_header_files 
        }),
    }, Module(
        modules[i]
    ));

    -- Formatting module page
    local page_dir   = Config.build.dest .. '/latest/' .. module_name;
    fs.mkdir(page_dir)
    fs.write_file(page_dir .. '/index.html', html, false);

    -- Write in specific version
    local page_dir_v = Config.build.dest .. '/v'.. VERSION .. '/' .. module_name;
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
    nav=HeaderPanel({ 
        class="light", headers=source_header_files 
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
}, Home({
    versions=get_version_tags();
}))

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