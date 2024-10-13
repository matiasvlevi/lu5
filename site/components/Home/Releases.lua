local luax = require('site/lib/luax');
local ver = require('site/lib/version');

function Release(props)
    if (props.class == nil) then
        props.class = ""
    end

    return luax('ul', {class="menu " .. props.class, style="margin: 0 1rem"}, {
        luax.map(luax.reverse(props.versions), function(version, i)
            local zipname = props.fmt(version);

            if (props.url == nil or zipname == nil) then
                return luax('li', {class="index"}, luax('span', {class="text"}, (zipname == nil) and 'unreleased' or zipname));
            end

            local link = props.url ..'/' .. 'v' .. version..'/' .. zipname;
            return luax('li', {class="index underline"}, {
                luax('a', {href=((zipname == nil) and '' or link)}, (zipname == nil) and 'unreleased' or zipname),
            })
        end)
    })
end

function Releases(props)
    return luax('div', {
        luax('h2', 'Releases'),
        luax('div', {class="builds", style="gap: 0.5rem;"}, {
            Release({
                class="tags",
                fmt=function(v)
                    return v
                end,
                versions=props.versions
            }),
            Release({
                url=props.meta.github_url .. '/releases/download',
                fmt=function(v)
                    local latest_version = ver.to_number(props.current_latest);
                    local nv = ver.to_number(v);
                    if (latest_version[3] < nv[3] or
                        latest_version[2] < nv[2] or
                        latest_version[1] < nv[1]) then
                        return nil
                    end

                    return "lu5-x86_64-linux-"..v..".zip"
                end,
                versions=props.versions
            }),
            Release({
                url=props.meta.github_url .. '/releases/download',
                fmt=function(v)
                    local latest_version = ver.to_number(props.current_latest);
                    local nv = ver.to_number(v);
                    if (latest_version[3] < nv[3] or
                        latest_version[2] < nv[2] or
                        latest_version[1] < nv[1]) then
                        return nil
                    end

                    if (ver.to_number(v)[2] < 1) then
                        return "lu5-x86_64-win-"..v..".zip"
                    else
                        return "lu5-x86_64-win-"..v..".exe"
                    end
                end,
                versions=props.versions
            })
        })
    })
end

return Releases;