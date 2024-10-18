local luax = require('site/lib/luax');

function icon_stop(scale)
    local scale = 1 / scale;
    return luax('svg', {width=100/scale, height=100/scale}, {
        luax('circle', { cx=50/scale, cy=50//scale, r=45//scale, fill="#d49af7"}),
        luax('polygon', { points=luax('', {
            30/scale, ',', 30/scale, ' ',
            70/scale, ',', 30/scale, ' ',
            70/scale, ',', 70/scale, ' ',
            30/scale, ',', 70/scale, ' ',
        }), fill="white"}),
    })
end

return icon_stop;