local luax = require('site/lib/luax');
local Parse = require('site/lib/parse');
local Minify = require('site/lib/minify');
local fs = require('site/lib/file');
local json = require('site/lib/json');
local search = require('site/lib/search');
local ver = require('site/lib/version');

-- Config
local Config = require('site/config');

-- Components
local RootLayout = require('site/layout/RootLayout');
local Home = require('site/components/Home');
local Reference = require('site/components/Reference');
local Module = require('site/components/Module');
local Method = require('site/components/Method');
local HeaderPanel = require('site/components/Navigation');

-- Parse all headers
local modules = Parse.all(Config.build.source.headers);

print();
print('pages:');
for i, module in pairs(modules) do
    -- Generate module page
    local html = RootLayout({
        purpose = "module",
        slug = module.source,
        page_name = module.name,
        parent = '',
        version = true,
        root = "../../",
        media = Config.media,
        meta = luax.merge(Config.metadata, {
            description=module.name .. ' reference page. Originating from ' .. module.source .. '.h in lu5 source. ' ..
                Config.metadata.description
        }),
        ga = Config.ga,
        nav = Navigation({
            root = "../",
            class = "light",
            modules = modules
        })
    }, Module(module));

    -- Write module page
    fs.write_vc_file(Config.build.dest, module.source, 'index.html', html, Config.current_latest);

    -- Iterate over all methods
    for i, method in ipairs(module.methods) do
        if (method.doc._type == "constant") then goto skip_symbol end;
        
        -- Generate method page
        local method_html = RootLayout({
            purpose = "symbol",
            slug = method.doc.name,
            page_name = method.doc.name,
            parent = module.source,
            version = true,
            root = "../../../",
            media = Config.media,
            meta = luax.merge(Config.metadata, {
                keywords = {
                    "Lua", 
                    "Creative Coding", 
                    "Lua Interpreter", 
                    "programming", 
                    "coding", 
                    "learn code", 
                    "documentation",
                    "reference", 
                    "guide"
                },
                description = 'lu5 Reference page for '.. method.doc.name .. '. ' ..
                    ((method.doc.description ~= nil) and 
                        Parse.remove_html_tags(method.doc.description) or '') .. ' ' ..
                    Config.metadata.description
            }),
            ga = Config.ga,
            nav = Navigation({
                root = "../",
                class = "light",
                modules = modules
            })
        }, luax('', {
            Method(method)
        }));

        -- Write method page
        fs.write_vc_file(
            Config.build.dest, 
            module.source .. '/' .. method.doc.name, 
            'index.html',
            method_html, 
            Config.current_latest
        );
        
        ::skip_symbol::
    end

end

-- Generate reference page
local reference_html = RootLayout({
    purpose = "reference",
    page_name = 'Reference',
    slug = "reference",
    version = true,
    root = "../",
    media = Config.media,
    meta = luax.merge(Config.metadata, {
        keywords = {
            "Lua", 
            "Creative Coding", 
            "Lua Interpreter", 
            "programming", 
            "coding", 
            "learn code", 
            "documentation",
            "reference", 
            "guide"
        },
        description = 'Reference documentation for lu5, ' ..
            'This documentation provides descriptions and examples of functions and features. '..
            Config.metadata.description
    }),
    ga = Config.ga,
    nav = Navigation({
        class = "light",
        root = "./",
        modules = modules
    })
}, Reference({
    modules = modules
}));

-- Generate Homepage
local homepage_html = RootLayout({
    purpose = "homepage",
    slug = "homepage",
    page_name = 'Interpreter for Creative Coding',
    title = 'lu5',
    version = false,
    root = "./",
    media = Config.media,
    meta = Config.metadata,
    ga = Config.ga
}, luax('div', {
    Home({
        versions = ver.get_version_tags(Config.build.dest),
        root = "./",
        current_latest = Config.current_latest,
        media = Config.media,
        meta = Config.metadata
    })
}))

-- Write Reference page
fs.write_vc_file(
    Config.build.dest, '', 'index.html', reference_html,
    Config.current_latest
);

-- Write homepage
fs.write_file(Config.build.dest .. '/index.html', homepage_html, true);

print();
print('json:');
-- Write a data about every method
for i, module in pairs(modules) do
    for j, method in ipairs(module.methods) do
        if method.doc._type == "constant" then goto skip_symbol end;

        fs.write_vc_file(
            Config.build.dest, module.source .. '/' .. method.doc.name, 'meta.json', 
            json.stringify(method),
            Config.current_latest
        );
        
        ::skip_symbol::
    end
end

-- Write table of contents for dynamic search feature
fs.write_vc_file(
    Config.build.dest, '', 'modules.json', json.stringify({
        symbols = search.get_method_table_of_contents(modules)
    }),
    Config.current_latest
);

-- Create assets directory
fs.mkdir(Config.build.dest .. '/' .. Config.media.assets);

print();
print('js:');
-- Minify & Copy javascript files
Minify(
    Config.build.source.js,     -- Source file names
    Minify.js,                  -- Minify function
    Config.build.source.static .. '/' .. 'js',      -- Source path
    Config.build.dest .. '/' .. Config.media.assets -- Destination path
);

print();
print('css:');
-- Minify & Copy css files
Minify(
    Config.build.source.css, 
    Minify.css, 
    Config.build.source.static .. '/' .. 'css',
    Config.build.dest .. '/' .. Config.media.assets
);

print();
print('assets:');
-- Copy all static assets to build destination
fs.copy_dir(
    Config.build.source.static .. '/' .. Config.media.assets, 
    Config.build.dest .. '/' .. Config.media.assets
);

-- Print results
print();
print('version:', '\x1b[90m' .. VERSION .. '\x1b[0m');
print();
if (Config.current_latest == VERSION) then
    print('Built lu5 website as latest in', '\x1b[90m'..Config.build.dest..'/latest\x1b[0m');
end
print('Built \x1b[92mlu5\x1b[0m website in', '\x1b[90m'..Config.build.dest..'\x1b[0m');
print();
print('  Total \x1b[90mhtml\x1b[0m files:', fs.get_counters('html'));
print('  Total \x1b[90mcss \x1b[0m files:', fs.get_counters('css'));
print('  Total \x1b[90mjs  \x1b[0m files:', fs.get_counters('js'));
print('  Total \x1b[90mjson\x1b[0m files:', fs.get_counters('json'));
print();