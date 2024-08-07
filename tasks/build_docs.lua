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

    -- Formatting module page
    fs.write_file(Config.build.dest .. '/' .. 'latest' .. '/' .. module_name .. '.html', RootLayout({
        page_name=module_name,
        version=true,
        root="../",
        media=Config.media,
        meta=Config.metadata,
        nav=HeaderPanel({ 
            class="light", headers=source_header_files 
        }),
        children=Module(
            modules[i]
        )
    }), true);
end

-- Formatting homepage
fs.write_file(Config.build.dest .. '/' .. 'latest'.. '/' .. 'index.html', RootLayout({
    page_name='Reference',
    version=true,
    root="../",
    media=Config.media,
    meta=Config.metadata,
    nav=HeaderPanel({ 
        class="light", headers=source_header_files 
    }),
    children=Reference({ 
        modules=modules 
    })
}), true);


fs.write_file(Config.build.dest .. '/' .. 'index.html', RootLayout({
    page_name='Interpreter for Creative Coding',
    version=false,
    root="./",
    media=Config.media,
    meta=Config.metadata,
    children=Home({
        versions=get_version_tags()
    })
}), true);

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

-- Copy latest to its own corresponding version
fs.mkdir(Config.build.dest .. '/v' .. VERSION);
local html_latest_files = fs.find_files_in_dir(Config.build.dest .. '/' .. 'latest' .. '/');
for i, filename in pairs(html_latest_files) do
    fs.write_file(
        Config.build.dest .. '/v' .. VERSION .. '/' .. filename,
        fs.read_file(
            Config.build.dest .. '/' .. 'latest' .. '/' .. filename
        )
    );
end